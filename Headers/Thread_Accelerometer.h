#ifndef THREAD_ACCELEROMETER_H
#define THREAD_ACCELEROMETER_H

#include "global_var.h"
#include "cmsis_os.h"                
#include "stm32f4xx_hal.h"
#include "lis3dsh.h"
#include <math.h>

void init_accel(void);
void calibrate_accel_data(float accelerometer_d[3]);
float calc_pitch(float accelerometer_data[3]);
float calc_roll(float accelerometer_data[3]);

#endif