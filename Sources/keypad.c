#include <stdio.h>
#include "keypad.h"
#include "main.h"
GPIO_InitTypeDef GPIOD_init;
int key_stage;
int8_t TDelay;
#define DELAY 1
//Initializes used pins rows: D5, D6, D7, D8 and columns: D9, D10, D11.
//This method is used to read rows (not columns).
void init_rows(void) {
		  __HAL_RCC_GPIOD_CLK_ENABLE();
      //Initialize the rows of the keypad.
			GPIOD_init.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
			GPIOD_init.Mode = GPIO_MODE_INPUT;
			GPIOD_init.Pull = GPIO_PULLUP;
			GPIOD_init.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIOD_init);
  
      //Initiialize the columns of the keypad.
			GPIOD_init.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
			GPIOD_init.Mode = GPIO_MODE_OUTPUT_PP;
			GPIOD_init.Pull = GPIO_PULLUP;
			GPIOD_init.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIOD_init);
	
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
}

//Initializes used pins rows: D5, D6, D7, D8 and columns: D9, D10, D11.
//This method is used to read columns (not rows).
void init_columns(void) {
		  __HAL_RCC_GPIOD_CLK_ENABLE();	
      //Initialize the rows of the keypad.
			GPIOD_init.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
			GPIOD_init.Mode = GPIO_MODE_OUTPUT_PP;
			GPIOD_init.Pull = GPIO_PULLUP;
			GPIOD_init.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIOD_init);
  
      //Initiialize the columns of the keypad.
			GPIOD_init.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
			GPIOD_init.Mode = GPIO_MODE_INPUT;
			GPIOD_init.Pull = GPIO_PULLUP;
			GPIOD_init.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(GPIOD, &GPIOD_init);
	
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
}

//Checks if a row has been pressed and returns a value of the row pressed (otherwise 0).
uint8_t read_rows(void){
	init_rows();
	//If a row button has been pressed return that number if not return 0.
	if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)){
		osDelay(DELAY);
		if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))return 1;
		else return 0;
	}
	else if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)){
		osDelay(DELAY);
		if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))return 2;
		else return 0;
	}
	else if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)){ 
	osDelay(DELAY);
	if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)) return 3;
	else return 0;	
	}
	else if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)){
	osDelay(DELAY);
	if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)) return 4;
	else return 0;
	}
	else return 0;

}
void delay(uint32_t time){
	TDelay = time;
	while(TDelay != 0);
}

//Checks if a column has been pressed and returns a value of the column pressed (otherwise 0).
uint8_t read_columns(void){
	init_columns();
	//If a column button has been pressed return that number if not return 0.
	if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9)){
	osDelay(DELAY);
		if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9)) return 1;
		else return 0;
	}
	else if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)){
		osDelay(DELAY);
		if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)) return 2;
		else return 0;
	}
	else if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)){
		osDelay(DELAY);
		if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)) return 3;
		else return 0;
	}
	else return 0;

}
int8_t determine_key(uint8_t row, uint8_t column){
	uint8_t key = row*10 + column;
	//Assigns the proper value of the key pressed.
	switch(key){
		case 11:
			return 1;
		case 12:
			return 2;
		case 13:
			return 3;
		case 21:
			return 4;
		case 22:
			return 5;
		case 23:
			return 6;
		case 31:
			return 7;
		case 32:
			return 8;
		case 33:
			return 9;
		case 41:
			return 11; //* key
		case 42:
			return 0; 
		case 43:
			return 12; //# key 
		default:
			return -1;			
	}
}
//Filters out noise and returns value of key pressed.
int return_key(void) {
	
	
	//int j = 0;
	uint8_t row, column = 0;
	uint8_t key;
	row = read_rows();
	osDelay(10);
	column = read_columns();
	osDelay(10);
	if(row && column > 0){
		return determine_key( row, column);
	}
	else{
		return 0;
	}
	//Handles the interupt.
	/*if((column = read_columns()) == 0) return -1;
	if((row = read_rows()) == 0) return -1;
	key = determine_key(row, column);
	while(1){
		while(determine_key(read_rows(),read_columns()) == key){
			j++;
			//delay(25);
		}
		if(j > 2) break;
		else return return_key();
	}
	printf("%d was pressed.\n", key);
	return key;*/
}
//Converts the user's presses into a 3 digit number. Key stage set to 4 when input is taken.
void order_key(int* output) {
	int key;
	switch(key_stage){
	case(0):
		//If the first key pressed isn't a number effectively ignore it.
		if((key = return_key()) == -1 || key == 11 || key == 12){
			output[0] = -1;
		}
		else{
			output[0] = key;
			output[1] = 0;
			key_stage++;
		}
		return;
	case(1):
		if((key = return_key()) == -1){
			printf("Error: no value given for key \n");			
			return;
		}
		//If enter is pressed signals the end of the input.
		else if((key = return_key()) == 12){
			output[2] = 0;
			output[3] = 0;
			key_stage = 4;
		}
		//If delete is pressed delete prior key (hold is checked elsewhere).
		else if((key = return_key()) == 11){
			output[0] = 0;
			key_stage--;
		}
		else{
			output[1] = key;
			output[2] = 0;
			key_stage++;			
		}
		return;
	case(2):
		if((key = return_key()) == -1){
			printf("Error: no value given for key \n");	
			return;
		}
		//If enter is pressed signals the end of the input.
		else if((key = return_key()) == 12){
			output[3] = 0;
			key_stage = 4;
		}
		//If delete is pressed delete prior key (hold is checked elsewhere).
		else if((key = return_key()) == 11){
			output[1] = 0;
			key_stage--;
		}
		else{
			output[2] = key;
			output[3] = 0;
			key_stage++;			
		}
		return;
	case(3):
		if((key = return_key()) == -1){
			printf("Error: no value given for key \n");	
			return;
		}
		//If enter is pressed signals the end of the input.
		else if((key = return_key()) == 12){
			key_stage = 4;
		}
		//If delete is pressed delete prior key (hold is checked elsewhere).
		else if((key = return_key()) == 11){
			output[2] = 0;
			key_stage--;
		}
		else{
			output[3] = key;
			key_stage++;			
		}
		return;
	default:
				printf("Error: default case reached key_stage value too high/low. \n");	
		return;
	
	}
}
