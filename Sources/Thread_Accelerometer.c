#include "Thread_Accelerometer.h"

float ACC11 = -2.3e-05;
float ACC21 = 0.001005;
float ACC31 = 6.03e-06;
float ACC12 = 0.001024;
float ACC22 = 2.51e-06;
float ACC32 = 2.34e-05;
float ACC13 = 3.29e-07;
float ACC23 = -3.8e-06;
float ACC33 = 0.000979;
float ACC10 = -0.01367;
float ACC20 = -0.00307;
float ACC30 = 0.002137;

//struct FIR_coeff coeff;

float accel_data[3];
float roll_value, pitch_value;

void Thread_Accelerometer(void const *argument); 
osThreadId tid_Thread_Accel;                            
osThreadDef(Thread_Accelerometer, osPriorityNormal, 1, 0);

//Create the thread for the accelerometer
int start_Thread_Accelerometer(void)
{
	tid_Thread_Accel = osThreadCreate(osThread(Thread_Accelerometer ), NULL); 
  if (!tid_Thread_Accel) return(-1); 
  return(0);
}

//Accelerometer thread that reads data whenever it is ready
void Thread_Accelerometer(void const *argument)
{
	while(1)
	{
		osSignalWait(ACCEL_READY_SIGNAL, osWaitForever);
		
		calibrate_accel_data(accel_data);
		pitch_value = calc_pitch(accel_data);
		roll_value = calc_roll(accel_data);
	}
}

//Initialize accelerometer parameters
void init_accel(void)
{
	LIS3DSH_InitTypeDef accel_init;
	LIS3DSH_DRYInterruptConfigTypeDef accel_it_config;
	
	//Initialize accelerometer parameters
	accel_init.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_25;
	accel_init.Axes_Enable = LIS3DSH_XYZ_ENABLE;
	accel_init.Continous_Update = LIS3DSH_ContinousUpdate_Enabled;
	accel_init.AA_Filter_BW = LIS3DSH_AA_BW_50;
	accel_init.Full_Scale = LIS3DSH_FULLSCALE_2;
	accel_init.Self_Test = LIS3DSH_SELFTEST_NORMAL;
	
	//Set accelerometer interrupt config
	accel_it_config.Dataready_Interrupt = LIS3DSH_DATA_READY_INTERRUPT_ENABLED;
	accel_it_config.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL;
	accel_it_config.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_PULSED;
	
	//Initialize function from drivers
	LIS3DSH_Init(&accel_init);
	LIS3DSH_DataReadyInterruptConfig(&accel_it_config);
	
	//Enable IRQ for accelerometer and set its priority
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	
	/*coeff.b0 = 0.1;
	coeff.b1 = 0.15;
	coeff.b2 = 0.5;
	coeff.b3 = 0.15;
	coeff.b4 = 0.1;*/
}

void calibrate_accel_data(float accelerometer_d[3])
{
	float tempX = 0, tempY = 0, tempZ = 0;
	
	tempX = accelerometer_d[0] * ACC11 + accelerometer_d[1] * ACC12 + accelerometer_d[3] * ACC13 + ACC10;
	tempY = accelerometer_d[0] * ACC21 + accelerometer_d[1] * ACC22 + accelerometer_d[3] * ACC23 + ACC20;
	tempZ = accelerometer_d[0] * ACC31 + accelerometer_d[1] * ACC32 + accelerometer_d[3] * ACC33 + ACC30;
	
	accelerometer_d[0] = tempX;
	accelerometer_d[1] = tempY;
	accelerometer_d[2] = tempZ;
}

float radToDegree(float rad)
{
	float degrees = rad * 180/PI;
	return degrees;
}

//Calculates the pitch of the board using the 3 axis.
float calc_pitch(float accelerometer_data[3]){
	float pitch = atanf(accelerometer_data[0]/(sqrtf(accelerometer_data[1]*accelerometer_data[1] + accelerometer_data[2]*accelerometer_data[2])));
	return radToDegree(pitch);
}

float calc_roll(float accelerometer_data[3]){
	float roll = atanf(accelerometer_data[1]/(sqrtf(accelerometer_data[0]*accelerometer_data[0] + accelerometer_data[2]*accelerometer_data[2])));
	return radToDegree(roll);
}