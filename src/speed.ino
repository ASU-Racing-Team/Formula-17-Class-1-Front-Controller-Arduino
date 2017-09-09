#include "speed.h"
#include "FrontController.h"

void update_speed_task(void *pvParameters __attribute__((unused)) ){
    attachInterrupt(digitalPinToInterrupt(speed_pin), speed_sensor_interrupt, FALLING);
    int old_time = 0;
    uint16_t period = 0;
    float v = 0;
    while(1){
        if(n_pulses > pulses_per_revolution){
            cli();
            n_pulses = 0;
            period = (old_time - millis());
            old_time = millis();
            v = 1000 * 
            tire_circ_m / (period);
            velocity = velocity * 3.6;
            serial_buffer[16] = velocity;
            sei();
        }
         vTaskDelay( 4 / portTICK_PERIOD_MS );
    }
}
void speed_sensor_interrupt(){
    cli();
    n_pulses++;
    sei();
}
