#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

void init_rows(void);

void init_columns(void);

void delay(uint32_t time);

uint8_t read_rows(void);

uint8_t read_columns(void);

int8_t determine_key(uint8_t row, uint8_t column);

int return_key(void);

void order_key(int* values);

#endif
