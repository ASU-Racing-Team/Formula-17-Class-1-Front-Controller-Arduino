#pragma once

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>


#define speed_pin 2
#define pulses_per_revolution 12
#define tire_circ_m 0.8854
extern uint8_t velocity;
extern uint8_t serial_buffer[19];
int n_pulses = 0;
void update_speed_task(void *pvParameters);
void speed_sensor_interrupt();
