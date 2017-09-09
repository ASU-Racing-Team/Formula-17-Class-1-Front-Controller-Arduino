#include "aeromotor.h"
#include "FrontController.h"

void update_motors_task(void *pvParameters){
    Servo right;
    Servo left;
    Servo rear;
    right.attach(RIGHT_PIN);
    left.attach(LEFT_PIN);
    rear.attach(REAR_PIN);
    while(1){
        if(velocity > SPEED_LIMIT){
            right.write(OFF_ANGLE);
            left.write(OFF_ANGLE);
            rear.write(OFF_ANGLE);
        }else{
            if(Ax < ACC_THERSHOLD && Gz > ROTATION_THRESHOLD){
                // The car is most probably in a corner
                right.write(ON_ANGLE);
                left.write(ON_ANGLE);
                rear.write(ON_ANGLE_REAR);
            }else{
                // The car is most probably is in a straightline
                right.write(OFF_ANGLE);
                left.write(OFF_ANGLE);
                rear.write(OFF_ANGLE_REAR);

            }
        }
        if(right.read() == ON_ANGLE){
          //  ON 01
          wings_on |= 0b01;
          wings_on &= ~0b10;
        }else if(right.read() == OFF_ANGLE){
          //  OFF 00
          wings_on &= ~0b11;
        }else{
          // ERROR 11
          wings_on |= 0b11;
        }
        if(right.read() == ON_ANGLE){
          //  ON 01
          wings_on |= 0b0100;
          wings_on &= ~0b1000;
        }else if(right.read() == OFF_ANGLE){
          //  OFF 00
          wings_on &= ~0b1100;
        }else{
          // ERROR 11
          wings_on |= 0b1100;
        }
        if(right.read() == ON_ANGLE){
          //  ON 01
          wings_on |= 0b010000;
          wings_on &= ~0b100000;
        }else if(right.read() == OFF_ANGLE){
          //  OFF 00
          wings_on &= ~0b110000;
        }else{
          // ERROR 11
          wings_on |= 0b110000;
        }
        serial_buffer[17] = wings_on;
    }
    vTaskDelay( 200 / portTICK_PERIOD_MS );
}
