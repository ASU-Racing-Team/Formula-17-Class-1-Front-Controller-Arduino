#include "FrontController.h"

uint16_t ax, ay, az;
uint16_t gx, gy, gz;
//uint16_t mx, my, mz;
float Ax = 0, Ay = 0, Az = 0;
float Gx = 0, Gy = 0, Gz = 0;
//float Mx = 0, My = 0, Mz = 0;
uint8_t velocity;
int8_t fl_sus_pos;
int8_t fr_sus_pos;
int8_t rl_sus_pos;
int8_t rr_sus_pos;
int8_t steering_offset;
// wings on is 8 bit where 
// [0:1] right wing state
// [2:3] left wing state
// [4:5] rear wing state
// where possible states are 00 OFF, 01 ON, 11 ERROR
uint8_t wings_on;
uint8_t serial_buffer[19];

void setup(){
    //xTaskCreate(update_speed_task, (const portCHAR *)"speed", 40, NULL, 2, NULL);
    //xTaskCreate(update_steering_task, (const portCHAR *)"steering", 64, NULL, 2, NULL);
    // xTaskCreate(update_suspension_task, (const portCHAR *)"suspension", 64, NULL, 2, NULL);
    xTaskCreate(update_imu_task, (const portCHAR *)"imu", 132, NULL, 2, NULL);
    //xTaskCreate(update_motors_task, (const portCHAR *)"motors", 128, NULL, 2, NULL);
    xTaskCreate(serial_comm_task, (const portCHAR *)"serial", 128, NULL, 2, NULL);
}
void loop(){
    
}
