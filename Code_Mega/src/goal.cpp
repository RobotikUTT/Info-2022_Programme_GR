/**
 * \file goal.cpp
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#include "../include/goal.h"

#include <math.h>

extern RobotState robotState;
extern Control control;
extern Nano nano;

extern void theEnd();

void Goto::process() {
	if (doSubGoal) {
		if (subGoal->isReached()) {
			control.resetPIDs();
			doSubGoal = false;
		}
		else {
			subGoal->process();
		}
		return;
	}
	if (!stop) {
		float dx = x - robotState.getPosition().x;
		float dy = y - robotState.getPosition().y;
		/*Serial.print("dx: ");
		Serial.println(dx );
		Serial.print("dy: ");
		Serial.println(dy);*/

		float distanceError = sqrt(pow(dx, 2) + pow(dy, 2));
		float thetaError = atan2(dy, dx) - robotState.getPosition().theta;

		if (!init) {
			init = true;
			theta = atan2(dy, dx);
			// #ifdef DEBUG_GOAL
			// Serial.print("Theta Error: ");
			// Serial.println(thetaError);
			// Serial.print("atan2(dy, dx): ");
			// Serial.println(atan2(dy, dx));
			// Serial.print("RobotState.theta: ");
			// Serial.println(robotState.getPosition().theta);
			// #endif // DEBUG_GOAL
			if (thetaError) {
				subGoal = new Rot(atan2(dy, dx));
				doSubGoal = true;
				return;
			}
		}

		if (thetaError > M_PI / 2 || thetaError < -M_PI /2) {
			digitalWrite(LED_BLUE, LOW);
			digitalWrite(LED_RED, HIGH);
			theEnd();
		}

		if (abs(distanceError) < DIST_ERROR_TOLERANCE) { //&& abs(thetaError) < THETA_ERROR_TOLERANCE ) {
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
			rampCoeff = min(1.0, rampCoeff + 1.0 / RAMP_NB_STEPS);
			control.updateSpeeds(distanceError * rampCoeff, thetaError * rampCoeff, maxSpeed);
			// control.updateSpeeds(distanceError * rampCoeff, 0, maxSpeed);
		}
	}
	else {
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
			// Position pos = {x, y, theta};
			// Position pos = {0, 0, 0};
			// robotState.setPosition(pos);
			return;
		}
		control.updateMotorsSpeeds(0, 0);
	}
}

void Rot::process() {
	if (!init) {
		init = true;
		x = robotState.getPosition().x;
		y = robotState.getPosition().y;
	}
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
			rampCoeff = min(1.0, rampCoeff + 1.0 / RAMP_NB_STEPS);
			control.updateSpeeds(0, thetaError * rampCoeff);
		}
	}
	else {
		WheelSpeeds currSpeed = robotState.getWheelSpeeds();
		if (millis() - startTimeoutStop > STOP_TIMEOUT_MS
			|| abs(currSpeed.left) + abs(currSpeed.right) <= SPEED_STOP_TOLERANCE) {
			reached = true;
			// Position pos = robotState.getPosition();
			// pos.theta = theta;
			// Position pos = {x, y, theta};
			// robotState.setPosition(pos);
			return;
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
			return;
		}
		control.updateMotorsSpeeds(0, 0);
	}
	else {
		rampCoeff = min(1, rampCoeff + 2 * 1.0 / RAMP_NB_STEPS);
		float filteredLinearSpeed = control.filterLinearSpeed(linearSpeed * rampCoeff, 0);
		float filteredAngularSpeed = control.filterAngularSpeed(angularSpeed * rampCoeff);
		control.updateMotorsSpeeds(filteredLinearSpeed, filteredAngularSpeed);
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
