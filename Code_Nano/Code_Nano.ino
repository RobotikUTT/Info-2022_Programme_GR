#include <Arduino.h>
#include <SoftwareSerial.h>

#include "sensors.h"
#include "pins.h"
#include "displayer.h"

#define MSG_PERIOD 5  /* 20 Hz => 5 milliseconds */

SoftwareSerial serial(SW_RX, SW_TX);

inline void serial_out(uint8_t message);
inline void serial_in();

void setup() {
    serial.begin(9600);
    serial.listen();
    Serial.begin(9600);
    init_sonars();
    init_lcd();
}


void loop() {
    static uint8_t message = 0x00;

    serial_in();

    for (int i = 0; i < NB_CAPTORS; ++i) {
        const double distance = get_distance(i);
        if (distance < 150)
            message |= 0b1 << i;  // set the i-th bit to 1
        else
            message &= ~(0b1 << i);  // set the i-th bit to 0
        serial_out(message);
    }
}

inline void serial_out(const uint8_t message) {
    static unsigned long elapsed = 0;
    const unsigned long current = millis();
    if (current - elapsed >= MSG_PERIOD) {
        elapsed = current;
        serial.write(message);
    }
}

inline void serial_in() {
    static int msg_in = 0;
    if (serial.available() > 0) {
        const int new_message = serial.read();
        if (new_message != msg_in) {
            msg_in = new_message;
            display_score(msg_in);
        }
    }
}