/**
 * \file control.h
 * \brief Class which sends PWM values to motors to regulate them at given speeds.
**/

#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>

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
	void updateMotorsSpeeds(float targetLinearSpeed, float targetAngularSpeed);
	float filterLinearSpeed(float speed, float maxSpeed=0);
	float filterAngularSpeed(float speed);
	void resetPIDs();

	PID getLinearPID() { return linearPID; }
	PID getAngularPID() { return angularPID; }
	PID getLeftWheelPID() { return leftWheelPID; }
	PID getRightWheelPID() { return rightWheelPID; }

	float getTargetLeftSpeed() { return targetLeftSpeed; }
	float getTargetRightSpeed() { return targetRightSpeed; }

private:
	PID linearPID = PID(0.4, 0.002, 0, 400 / 0.002);
	PID angularPID = PID(24, 0.2, 0, 200 / 0.2);
	PID leftWheelPID = PID(0.9, 0.02, 0, 255.0 / 0.02);
	PID rightWheelPID = PID(0.9, 0.02, 0, 255.0 / 0.02);

	float currentLinearSpeed = 0;
	float currentAngularSpeed = 0;
	float targetLeftSpeed = 0;
	float targetRightSpeed = 0;

	void updateMotor(Motor &motor, PID &pid, float error);
};

#endif // CONTROL_H
