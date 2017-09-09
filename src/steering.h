#pragma once

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>


#define STEERING_NORMAL 180
#define STEERING_PIN A6
extern int8_t steering_offset;
extern uint8_t serial_buffer[19];
void update_speed_task(void *pvParameters);
