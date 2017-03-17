#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#define PI 										3.14159265359
#define ACCEL_READY_SIGNAL 		1
#define TEMP_READY_SIGNAL			2
#define Avg_Slope 	          25
#define V_25									760

extern float temp_data;
extern float accel_data[3];
extern float roll_value, pitch_value;

#endif