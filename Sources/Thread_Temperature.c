#include "Thread_Temperature.h"

ADC_HandleTypeDef ADC1_Handle;
ADC_InitTypeDef ADC1_Init;
ADC_ChannelConfTypeDef ADC1_Channel;

//struct FIR_coeff coeff;

float temp_data;

void Thread_Temperature(void const *argument); 
osThreadId tid_Thread_Temp;                            
osThreadDef(Thread_Temperature, osPriorityNormal, 1, 0);

osMutexId temp_mutex;
osMutexDef(temp_mutex);

int start_Thread_Temperature(void)
{
	tid_Thread_Temp = osThreadCreate(osThread(Thread_Temperature ), NULL); 
  if (!tid_Thread_Temp) return(-1); 
  return(0);
}

//Accelerometer thread that reads data whenever it is ready
void Thread_Temperature(void const *argument)
{
	while(1)
	{
		osSignalWait(TEMP_READY_SIGNAL, osWaitForever);
		
		read_temp();
	}
}

void init_temp(void)
{
	//Initialize ADC_InitTypeDef instance
	ADC1_Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	ADC1_Init.Resolution = ADC_RESOLUTION_12B;
	ADC1_Init.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC1_Init.ScanConvMode = DISABLE;
	ADC1_Init.EOCSelection = DISABLE;
	ADC1_Init.ContinuousConvMode = ENABLE;
	ADC1_Init.DMAContinuousRequests = DISABLE;
	ADC1_Init.NbrOfConversion = 1;
	ADC1_Init.DiscontinuousConvMode = DISABLE;
	ADC1_Init.NbrOfDiscConversion = 0;
	ADC1_Init.ExternalTrigConv = ADC_SOFTWARE_START;
	ADC1_Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	
	//Initialize ADC_HandleTypeDef instance
	ADC1_Handle.Instance = ADC1;
	ADC1_Handle.Init = ADC1_Init;
	
	//Initialize ADC_ChannelConfTypeDef instance
	//Sets up the temperature sensor to work (located channel 16).
	ADC1_Channel.Channel = ADC_CHANNEL_16;
	ADC1_Channel.Rank = 1; 
	ADC1_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES; 
	ADC1_Channel.Offset = 0;
	
	__HAL_RCC_ADC1_CLK_ENABLE();
	
	HAL_ADC_Init(&ADC1_Handle);
	HAL_ADC_ConfigChannel(&ADC1_Handle, &ADC1_Channel);
	HAL_ADC_Start(&ADC1_Handle);
	
	temp_mutex = osMutexCreate(osMutex(temp_mutex));
	
	/*coeff.b0 = 0.1;
	coeff.b1 = 0.15;
	coeff.b2 = 0.5;
	coeff.b3 = 0.15;
	coeff.b4 = 0.1;*/
}

float convertToTemp(uint32_t adc_data) 
{
	float temp;
	
	temp = (((float)adc_data - V_25)/Avg_Slope) + 13;
	
	return temp;
}

void read_temp(void)
{
	float adc_data;
	
	adc_data = HAL_ADC_GetValue(&ADC1_Handle);
	
	osMutexWait(temp_mutex, osWaitForever);
	temp_data = convertToTemp(adc_data);
	osMutexRelease(temp_mutex);
}
