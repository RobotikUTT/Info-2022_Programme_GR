//
// Created by thgir on 26/05/2022.
//

/**
 * @file nano_input.
 */


#ifndef GROS_ROBOT_NANO_INPUT_H
#define GROS_ROBOT_NANO_INPUT_H

#include <Arduino.h>

/**
 * Read the values sent by the software serial and use it to fill a buffer containing the values
 * of the measures made by the sonars of the nano.
 *
 * @return a pointer to the buffer containing the most recent measures made by the sonars.
 * The buffer is a static array of size 4 in which the index of each correspond to a sonar.
 * As an example, if the buffer contains values {15, 200, 255, 100} then it means
 * the sonar 1 is 15mm from the nearest obstacle, the sonar 2 200mm, the sonar 3 255mm and the
 * sonar 4 100mm.
 * Values are encoded on 8 bits, so a distance of 255 may be in fact a greater value that has been floored.
 */
uint8_t *get_sonar_buffer();

#endif //GROS_ROBOT_NANO_INPUT_H
