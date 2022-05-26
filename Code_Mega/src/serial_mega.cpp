//
// Created by thgir on 26/05/2022.
//

#include "Info-2022_Programme_GR/Code_Mega/include/serial_mega.h"
#include <SoftwareSerial.h>

#define BUF_SIZE 4

static SoftwareSerial serial(10, 11);


uint8_t *get_sonar_buffer() {
    static uint8_t cursor = 0;
    static uint8_t sonars_buf[BUF_SIZE] = {255};
    while (serial.available() > 0) {
        sonars_buf[cursor] = serial.read();
        if (++cursor == BUF_SIZE)
            cursor = 0;
    }
    return sonars_buf;
}