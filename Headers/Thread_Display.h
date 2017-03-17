#ifndef THREAD_DISPLAY_H
#define THREAD_DISPLAY_H

#include "global_var.h"
#include "cmsis_os.h"                
#include "stm32f4xx_hal.h"
#include <math.h>

/*GPIO_PIN_10 is segment A
GPIO_PIN_1 is segment B
GPIO_PIN_2 is segment C
GPIO_PIN_3 is segment D
GPIO_PIN_4 is segment E
GPIO_PIN_5 is segment F
GPIO_PIN_6 is segment G*/

#define TEMP_LIMIT 25

void displayTemp(float temp);
void set_LED(int segment);
void set_digit(int digit);
void reset_LED();

#endif