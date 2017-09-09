#pragma once

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>


#define FRONT_LEFT_PIN A0
#define FRONT_RIGHT_PIN A1
#define REAR_LEFT_PIN A2
#define REAR_RIGHT_PIN A3
#define NORMAL_POS 25;

extern int8_t fl_sus_pos;
extern int8_t fr_sus_pos;
extern int8_t rl_sus_pos;
extern int8_t rr_sus_pos;
extern uint8_t serial_buffer[19];
void update_suspension_task(void *pvParameters);
