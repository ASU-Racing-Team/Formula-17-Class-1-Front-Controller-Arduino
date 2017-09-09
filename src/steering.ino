#include "steering.h"
#include "FrontController.h"

void update_steering_task(void *pvParameters __attribute__((unused)) ){
    pinMode(STEERING_PIN, INPUT);
    while(1){
        // on the recieving side NORMAL_POS - value
        steering_offset = ((analogRead(STEERING_PIN)>>2)*(360/255));
        serial_buffer[18] = steering_offset;
        vTaskDelay( 10 / portTICK_PERIOD_MS );
    }
}

