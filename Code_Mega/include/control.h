/**
 * \file control.h
 * \brief Class which sends PWM values to motors to regulate them at given speeds.
**/

#ifndef CONTROL_H
#define CONTROL_H

#include <arduino.h>

#include "pid.h"
#include "motor.h"
#include "robotstate.h"
#include "collisions.h"
#include "pins.h"
#include "parameters.h"

class Control {
public:
	/**
	 * \brief updates the motor speeds according to the given errors.
	 * \param distanceError distance from the goal in mm
	 * \param thetaError angle difference in rad
	 * \param maxSpeed maximum speed constraint, 0 for default.
	**/
	void updateSpeeds(float distanceError, float thetaError, float maxSpeed = 0);
	void resetPIDs();

private:
	PID linearPID = PID(.7, 0.5, 0.7, 200);
	PID angularPID = PID(80, 0.3, 60.0, 360);
	PID leftWheelPID = PID(.54, 0.0, 0.7, 1000);
	PID rightWheelPID = PID(.7, 0.0, 0.7, 1000);

	float currentSpeed = 0;
	float targetLinearSpeed = 0;
	float targetAngularSpeed = 0;

	void updateMotorsSpeeds();
	void updateMotor(Motor motor, PID pid, float error);
	float filterLinearSpeed(float speed, float maxSpeed=0);
};

#endif // CONTROL_H
