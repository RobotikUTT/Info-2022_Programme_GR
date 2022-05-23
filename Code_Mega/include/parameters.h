/**
 * \file parameters.h
 * \brief All parameters used
**/

#ifndef PARAMETERS_H
#define PARAMETERS_H

/* Debug parameters */
// Uncomment/Comment to Enable/Disable Debug Prints
#define DEBUG
// #define BYPASS_TIRETTE

// Choose (by commenting lines or not) which parts you want prints for
#ifdef DEBUG
#define DEBUG_MATCH
#define DEBUG_GOAL
#define DEBUG_MOTOR
#define DEBUG_ROBOTSTATE
#endif // DEBUG

/* Main loop */
#define RATE_HZ 100 // Hz
#define TIMER_MS 1000.0 / (float)RATE_HZ // ms

/* Speed constants */
#define MAX_SPEED 1000 // mm/s
#define MAX_ACCEL 15000 // mm/s^2
#define MAX_ACCELERATION_DIFFERENCE 100	//MAX_ACCEL / RATE_HZ // mm/s
#define BRAKE_COEFF 0.3	// brakes BRAKE_COEFF times more than accelerates
#define MAX_BRAKE_DIFFERENCE MAX_ACCELERATION_DIFFERENCE * BRAKE_COEFF // mm/s
#define MAX_PWM_DIFFERENCE 30

/* Robot state */
#define WHEEL_DIAMETER 56 // mm
#define ENTRAXE 217 // mm
#define TICKS_PER_ROTATION (48 * 47)
#define DISTANCE_PER_TICK WHEEL_DIAMETER * 3.14159265358979323846 / TICKS_PER_ROTATION

/* Collisions */
#define COLLISIONS_SPEED_COEFF 0.5 
#define COLLISIONS_STOP_DISTANCE 150 // mm

/* Goals */
#define DIST_ERROR_TOLERANCE 10 // mm
#define THETA_ERROR_TOLERANCE 0.01 // rad
#define MAX_SIMULTANEOUS_GOALS 50


#endif // PARAMETERS_H
