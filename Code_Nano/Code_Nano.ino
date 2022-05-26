#include <Arduino.h>

#include "sensors.h"
#include "pins.h"
#include "displayer.h"
#include "serial.h"



void setup() {
    init_software_serial();
    Serial.begin(9600);
    init_sonars();
    init_lcd();
}


void loop() {
    static uint8_t message = 0x00;

    serial_in();

    for (int i = 0; i < NB_CAPTORS; ++i) {
        const double distance = get_distance(i);
        const uint8_t message = distance > 255 ? 255 : (uint8_t) distance;
        serial_out(message);
    }
}


