#ifndef THREAD_TEMPERATURE_H
#define THREAD_TEMPERATURE_H

#include "global_var.h"
#include "cmsis_os.h"                
#include "stm32f4xx_hal.h"

void init_temp(void);
void read_temp(void);

#endif