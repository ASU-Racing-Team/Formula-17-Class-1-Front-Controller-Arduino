#include "serial_comm.h"
#include "FrontController.h"


/*
 * on the recieving side 
 * suspension positon - 25
 * steering position - 180
 * (ax, ay, az - 32768) * 2 / 32768
 * (ax, ay, az - 32768) * 500 / 32768
 * ((((mx, my, mz - 32768) - 128)/256)+1) * 4912 / 32768
 */
void serial_comm_task(void *pvParameters){
    Serial.begin(115200);
    
    while(1){
            /*
            Serial.println("IMU");
            Serial.print(Ax); Serial.print('\t');
            Serial.print(Ay); Serial.print('\t'); 
            Serial.print(Az); Serial.print("\t"); 
            Serial.print(Gx); Serial.print('\t');
            Serial.print(Gy); Serial.print('\t'); 
            Serial.print(Gz); Serial.print("\t"); 
            //Serial.print(Mx); Serial.print('\t');
            //Serial.print(My); Serial.print('\t'); 
            //Serial.print(Mz); Serial.print("\t\n");
            Serial.println("\nSuspension");
            Serial.print(fl_sus_pos); Serial.print("\t");
            Serial.print(fr_sus_pos); Serial.print("\t");
            Serial.print(rl_sus_pos); Serial.print("\t");
            Serial.print(rr_sus_pos); Serial.print("\t\n");
            Serial.println("Speed");
            Serial.print(velocity); Serial.print("\n");
            Serial.println("Steering");
            Serial.print(steering_offset); Serial.print("\n");
            Serial.println("Motors");
            Serial.print(wings_on); Serial.print("\n");
            */
            if(Serial.available()){
              char a = Serial.read();
              if(a == 'A'){
                Serial.write(serial_buffer, 19);
             }            }
            vTaskDelay( 5/ portTICK_PERIOD_MS );

    }
}
