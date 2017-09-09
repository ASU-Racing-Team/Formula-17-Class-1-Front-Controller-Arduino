#pragma once

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>



#ifdef DEBUGGING
extern float Ax, Ay, Az;
extern float Gx, Gy, Gz;
extern float Mx, My, Mz;
extern uint8_t velocity;
extern int8_t fl_sus_pos;
extern int8_t fr_sus_pos;
extern int8_t rl_sus_pos;
extern int8_t rr_sus_pos;
extern int8_t steering_offset;
extern uint8_t wings_on;
#endif
extern uint8_t serial_buffer[19];

void serial_comm_task(void *pvParameters);
