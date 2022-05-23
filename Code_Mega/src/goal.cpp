/**
 * \file goal.cpp
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#include "../include/goal.h"

#include <math.h>

extern RobotState robotState;
extern Control control;


void Goto::process() {

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
		reached = true;
		#ifdef DEBUG_GOAL
		Serial.println("Goal: Goto Reached");
		#endif // DEBUG_GOAL
	}

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

void Rot::process() {
	float thetaError = theta - robotState.getPosition().theta;
	if (abs(thetaError) < THETA_ERROR_TOLERANCE) {
		reached = true;
		#ifdef DEBUG_GOAL
		Serial.println("Goal: Rot Reached");
		#endif // DEBUG_GOAL
	}
	control.updateSpeeds(0, thetaError);
}
