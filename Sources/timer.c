#include "timer.h"

TIM_HandleTypeDef tim4_handle;
TIM_Base_InitTypeDef tim4_init;

void init_tim4(void)
{
	//Initialize the base init typedef of TIM
	//Desired Timer Frequency =  Timer Input Frequency / (Prescaler * Period) 
	//Desired = 2KHz
	//Timer Input Frequency = 84MHz
	//tim4_init.Prescaler = 21;
	tim4_init.Prescaler = 999;
	tim4_init.CounterMode = TIM_COUNTERMODE_UP;
	//tim4_init.Period = 2000;
	tim4_init.Period = 83;
	tim4_init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	tim4_handle.Instance = TIM4;
	tim4_handle.Init = tim4_init;
	tim4_handle.Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
	tim4_handle.Lock = HAL_UNLOCKED;
	tim4_handle.State = HAL_TIM_STATE_READY;
	
	//Initialize the time base unit
	HAL_TIM_Base_MspInit(&tim4_handle);
	HAL_TIM_Base_Init(&tim4_handle);
	
	// Start timer in interrupt mode
	HAL_TIM_Base_Start_IT(&tim4_handle);
	
	
	//Enable IRQ for TIM4 and set its priority
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
}

