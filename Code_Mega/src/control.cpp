/**
 * \file control.cpp
 * \brief Class which sends PWM values to motors to regulate them at given speeds.
**/

#include "../include/control.h"

extern Motor rightMotor;
extern Motor leftMotor;
extern RobotState robotState;
extern Collisions collisions;

Control control;


void Control::resetPIDs() {
	linearPID.resetErrors();
	angularPID.resetErrors();
	leftWheelPID.resetErrors();
	rightWheelPID.resetErrors();
}

void Control::updateSpeeds(float distanceError, float thetaError, float maxLinearSpeed) {
	targetLinearSpeed = filterLinearSpeed(linearPID.output(distanceError), maxLinearSpeed);
	targetAngularSpeed = angularPID.output(thetaError); // no collisions or speed check on angular speed
	updateMotorsSpeeds();
}

void Control::updateMotorsSpeeds() {
	float targetLeftSpeed = targetLinearSpeed - targetAngularSpeed;
	float targetRightSpeed = targetLinearSpeed + targetAngularSpeed;
	float leftError = 0;
	float rightError = 0;

	if (abs(robotState.getWheelSpeeds().left) > abs(targetLeftSpeed)){
		leftError = 0;
	}
	else {
		leftError = targetLeftSpeed - robotState.getWheelSpeeds().left;
	}
	if (abs(robotState.getWheelSpeeds().right) > abs(targetRightSpeed)){
		rightError = 0;
	}
	else {
		rightError = targetRightSpeed - robotState.getWheelSpeeds().right;
	}

	updateMotor(leftMotor, leftWheelPID, leftError);
	updateMotor(rightMotor, rightWheelPID, rightError);
}

void Control::updateMotor(Motor motor, PID pid, float error) {
	int pwm = pid.output(error);
	bool dirForward = (pwm > 0);

	if (!dirForward) pwm = -pwm;
	if (pwm > 255) pwm = 255;
 
	motor.sendPWM(pwm, dirForward);
}

float Control::filterLinearSpeed(float speed, float maxSpeed) {
	if (!maxSpeed) {
		maxSpeed = MAX_SPEED;
	}

	if (speed >= 0) {
		if (speed > collisions.getMaxSpeed()) {
			speed = collisions.getMaxSpeed();
		}

		if (speed - currentSpeed > MAX_ACCELERATION_DIFFERENCE) {
			speed = currentSpeed + MAX_ACCELERATION_DIFFERENCE;
		} else if (speed - currentSpeed < - MAX_BRAKE_DIFFERENCE) {
			speed = currentSpeed - MAX_BRAKE_DIFFERENCE;
		}

		if (speed > maxSpeed) {
			speed = maxSpeed;
		}
	}
	else { // speed < 0 : going backwards
		if (speed < - collisions.getMaxSpeed()) {
			speed = - collisions.getMaxSpeed();
		}

		if (speed - currentSpeed < - MAX_ACCELERATION_DIFFERENCE) {
			speed = currentSpeed - MAX_ACCELERATION_DIFFERENCE;
		} else if (speed - currentSpeed > MAX_BRAKE_DIFFERENCE) {
			speed = currentSpeed + MAX_BRAKE_DIFFERENCE;
		}

		if (speed < - maxSpeed) {
			speed = - maxSpeed;
		}
	}

	currentSpeed = speed;
	return speed;
}
