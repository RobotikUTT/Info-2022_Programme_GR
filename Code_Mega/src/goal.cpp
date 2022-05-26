/**
 * \file goal.cpp
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#include "../include/goal.h"

#include <math.h>

extern RobotState robotState;
extern Control control;
extern Nano nano;

void Goto::process() {
	if (!stop) {
		float dx = x - robotState.getPosition().x;
		float dy = y - robotState.getPosition().y;
		/*Serial.print("dx: ");
		Serial.println(dx );
		Serial.print("dy: ");
		Serial.println(dy);*/

		float distanceError = sqrt(pow(dx, 2) + pow(dy, 2));
		float thetaError = atan2(dy, dx) - robotState.getPosition().theta;
		//thetaError = fmod(thetaError, 2*M_PI);

		if (distanceError < DIST_ERROR_TOLERANCE) { //&& abs(thetaError) < THETA_ERROR_TOLERANCE ) {
			stop = true;
			startTimeoutStop = millis();
			// control.resetPIDs();
			control.updateMotorsSpeeds(0, 0);
			#ifdef DEBUG_GOAL
			Serial.println("Goal: Goto Reached");
			#endif // DEBUG_GOAL
		}
		else {
			/*if (thetaError < THETA_ERROR_TOLERANCE  && type==0) {
				// rotate only
				distanceError = 0;
			}*/ 
			//Serial.println("Goto::process()");
			/*Serial.print("thetaError: ");
			Serial.println(thetaError);
			Serial.print("dError: ");
			//Serial.println(distanceError);*/
			control.updateSpeeds(distanceError, thetaError, maxSpeed);
		}
	}
	else {
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
		}
		control.updateMotorsSpeeds(0, 0);
	}
}

void Rot::process() {
	if (!stop) {
		float thetaError = theta - robotState.getPosition().theta;
		if (abs(thetaError) < THETA_ERROR_TOLERANCE) {
			stop = true;
			startTimeoutStop = millis();
			// control.resetPIDs();
			control.updateMotorsSpeeds(0, 0);
			#ifdef DEBUG_GOAL
			Serial.println("Goal: Rot Reached");
			#endif // DEBUG_GOAL
		}
		else {
			control.updateSpeeds(0, thetaError);
		}
	}
	else {
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
		}
		control.updateMotorsSpeeds(0, 0);
	}
}


void Jog::process() {
	if (!startTimeGoal) {
		startTimeGoal = millis();
	}
	else if (millis() - startTimeGoal >= duration) {
		if (!startTimeoutStop) {
			startTimeoutStop = millis();
			// control.resetPIDs();
		}
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
		}
		control.updateMotorsSpeeds(0, 0);
	}
	else {
		float filteredLinearSpeed = control.filterLinearSpeed(linearSpeed, 0);
		control.updateMotorsSpeeds(filteredLinearSpeed, angularSpeed);
	}
}

void InhibSonar::process() {
	uint8_t sonarInhib_ = nano.getSonarInhib();
	if (inhib) {
		sonarInhib_ |= sonarMask;
	}
	else {
		sonarInhib_ &= ~sonarMask;
	}
	nano.setSonarInhib(sonarInhib_);
	reached = true;
}
