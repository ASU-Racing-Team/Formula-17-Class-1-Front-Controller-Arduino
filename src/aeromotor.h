#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#define LEFT_PIN 3
#define RIGHT_PIN 4
#define REAR_PIN 5
#define SPEED_LIMIT 65
#define ON_ANGLE 55
#define ON_ANGLE_REAR 55
#define OFF_ANGLE_REAR 55
#define OFF_ANGLE 55
#define ACC_THERSHOLD 0
#define ROTATION_THRESHOLD 0
extern uint8_t velocity;
extern float Ax;
extern float Gz;
extern uint8_t serial_buffer[19];

void update_motors_task(void *pvParameters);
