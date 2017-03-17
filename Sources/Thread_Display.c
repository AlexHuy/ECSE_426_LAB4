#include "Thread_Display.h"

void Thread_Display(void const *argument); 
osThreadId tid_Thread_Display;                            
osThreadDef(Thread_Display, osPriorityNormal, 1, 0);

//Create the thread for the display
int start_Thread_Display(void)
{
	tid_Thread_Display = osThreadCreate(osThread(Thread_Display ), NULL); 
  if (!tid_Thread_Display) return(-1); 
  return(0);
}

void Thread_Display(void const *argument)
{
	float temp2display = 0;
	float pitch2display = 0;
	float roll2display = 0;
	
	while(1)
	{
		osDelay(10);
		
		/*osMutexWait(temp_mutex, osWaitForever);
		temp2display = temp_data;
		osMutexRelease(temp_mutex);*/
		
		osMutexWait(accel_mutex, osWaitForever);
		roll2display = roll_value;
		osMutexRelease(accel_mutex);
		
		/*if(temp2display >= TEMP_LIMIT)
		{
			osDelay(20);
			displayTemp(temp2display);
			reset_LED();
		}
		else
		{
			displayTemp(temp2display);
		}*/
		
		displayTemp(roll2display);
	}
}

void init_display(void)
{
	GPIO_InitTypeDef GPIOA_init;
	GPIO_InitTypeDef GPIOC_init;
	
	GPIOA_init.Pin = GPIO_PIN_10 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIOA_init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOA_init.Pull = GPIO_NOPULL;
	GPIOA_init.Speed = GPIO_SPEED_FREQ_HIGH;
     
	GPIOC_init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIOC_init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOC_init.Pull = GPIO_NOPULL;
	GPIOC_init.Speed = GPIO_SPEED_FREQ_HIGH;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	HAL_GPIO_Init(GPIOA, &GPIOA_init);
	HAL_GPIO_Init(GPIOC, &GPIOC_init);
}

void displayTemp(float temp)
{
	int display[4];
	int i;
	
	display[3] = 10;
	display[2] = (int) (temp/10);
	display[1] = (int) (temp - display[2]*10);
	display[0] = (int) ((temp*10) - display[2]*100 - display[1]*10);
	
	/*if(temp == 0)
	{
		display[3] = 10;
		display[2] = 10;
		display[1] = 10;
		display[0] = 10;
	}*/
	
	for(i = 0; i < 4 ; i++)
	{
		set_digit(i);
		set_LED(display[i]);
		osDelay(2);
	}
}

void set_digit(int digit)
{
	switch(digit)
	{
		case(3):
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); 				
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
			break;
		
		case(2):
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); 				
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); 
			break;
		
		case(1):
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); 				
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);  
			break;
		
		case(0):
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); 				
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
			break;
		
		default:
			break;
	}
}

void set_LED(int segment) 
{       
	switch(segment) 
	{
		//Sets the LCD to be equal to zero.
		case(0):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c				
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //Pin g
      break;
		
		//Sets the LCD to be equa to one
		case(1):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c				
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //Pin g
      break;	
		
		//Sets the LCD to be equal to two.					
		case(2):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;	
		
		//Sets the LCD to be equal to three.
		case(3):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;	
				
		//Sets the LCD to be equal to four.					
		case(4):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;	
				
		//Sets the LCD to be equal to five.					
		case(5):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;
				
		//Sets the LCD to be equal to six.					
		case(6):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;
				
		//Sets the LCD to be equal to seven.					
		case(7):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //Pin g
      break;
				
		//Sets the LCD to be equal to eight.					
		case(8):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;
				
		//Sets the LCD to be equal to nine.					
		case(9):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //Pin g
      break;	
				
		//Sets the LCD to be equal to NUL.				
		case(10):
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); //Pin a
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); //Pin b
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //Pin c
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //Pin d
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //Pin e
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //Pin f
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //Pin g
      break;			

		default:
			break;
	}		
}

void reset_LED()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); 
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); 				
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
}



