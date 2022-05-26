/**
 * \file parameters.h
 * \brief All parameters used
**/

#ifndef PARAMETERS_H
#define PARAMETERS_H

/* Debug parameters */
// Uncomment/Comment to Enable/Disable Debug Prints
// #define DEBUG
#define PLOT
// #define BYPASS_TIRETTE

#ifdef PLOT
#undef DEBUG
#define PLOT_MOTOR_SPD
#define PLOT_MOTOR_ERR
#define PLOT_MOTOR_TGT
#endif // PLOT

// Choose (by commenting lines or not) which parts you want prints for
#ifdef DEBUG
#define DEBUG_MATCH
#define DEBUG_GOAL
#define DEBUG_PID
#define DEBUG_MOTOR
#define DEBUG_ROBOTSTATE
#endif // DEBUG

/* Main loop */
#define RATE_HZ 50 // Hz
#define TIMER_MS (1000.0 / RATE_HZ) // ms
#define MATCH_LENGTH_MS 99000 // ms

/* Speed constants */
#define MAX_SPEED 400 // mm/s
#define MAX_ANGULAR_SPEED 250 // mm/s
#define MAX_ACCEL 15000 // mm/s^2
#define MAX_ACCELERATION_DIFFERENCE 100	//MAX_ACCEL / RATE_HZ // mm/s
#define BRAKE_COEFF 0.3	// brakes BRAKE_COEFF times more than accelerates
#define MAX_BRAKE_DIFFERENCE (MAX_ACCELERATION_DIFFERENCE * BRAKE_COEFF) // mm/s
#define MAX_PWM_DIFFERENCE_ACC 30
#define MAX_PWM_DIFFERENCE_BRK 30
#define STOP_TIMEOUT_MS 1000

/* Robot state */
#define WHEEL_DIAMETER_L 75.5 // mm
#define WHEEL_DIAMETER_R 76.1 // mm
#define ENTRAXE 162 // mm
#define TICKS_PER_ROTATION (48 * 47)
#define DISTANCE_PER_TICK_L (WHEEL_DIAMETER_L * 3.14159265358979323846 / TICKS_PER_ROTATION)
#define DISTANCE_PER_TICK_R (WHEEL_DIAMETER_R * 3.14159265358979323846 / TICKS_PER_ROTATION)

/* Collisions */
#define COLLISIONS_SPEED_COEFF 0.5 
#define COLLISIONS_STOP_DISTANCE 150 // mm

/* Goals */
#define DIST_ERROR_TOLERANCE 2 // mm
#define THETA_ERROR_TOLERANCE 0.01 // rad
#define SPEED_STOP_TOLERANCE 1 // mm/s
#define MAX_SIMULTANEOUS_GOALS 50

/* Sonar */
#define TRESHOLD_COUNT 4
#define SONAR_FRONT_RIGHT   0b0001
#define SONAR_FRONT_LEFT    0b0010
#define SONAR_BACK_RIGHT    0b0100
#define SONAR_BACK_LEFT     0b1000


#endif // PARAMETERS_H
