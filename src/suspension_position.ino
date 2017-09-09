#include "suspension_position.h"
#include "FrontController.h"

void update_suspension_task(void *pvParameters __attribute__((unused)) ){
    pinMode(FRONT_LEFT_PIN, INPUT);
    pinMode(FRONT_RIGHT_PIN, INPUT);
    pinMode(REAR_LEFT_PIN, INPUT);
    pinMode(REAR_RIGHT_PIN, INPUT);
    while(1){
        // on the recieving side NORMAL_POS - value
        fl_sus_pos = (analogRead(FRONT_LEFT_PIN)*50/255);
        fr_sus_pos = (analogRead(FRONT_RIGHT_PIN)*50/255);
        rl_sus_pos = (analogRead(REAR_LEFT_PIN)*50/255);
        rr_sus_pos = (analogRead(REAR_RIGHT_PIN)*50/255);
        serial_buffer[12] = fl_sus_pos;
        serial_buffer[13] = fr_sus_pos;
        serial_buffer[14] = rl_sus_pos;
        serial_buffer[15] = rr_sus_pos;
        vTaskDelay( 5 / portTICK_PERIOD_MS );
    }
}
