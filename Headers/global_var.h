#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

#define PI 										3.14159265359
#define ACCEL_READY_SIGNAL 		1
#define TEMP_READY_SIGNAL			2
#define Avg_Slope 	          25
#define V_25									760

//Shared variables, needs mutual exclusion
extern float temp_data;
extern float accel_data[3];
extern float roll_value, pitch_value;

extern osMutexId temp_mutex;
extern osMutexId accel_mutex;

#endif