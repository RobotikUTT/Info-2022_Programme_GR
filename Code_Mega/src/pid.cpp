/**
 * \file pid.cpp
 * \brief Basic PID class.
**/

#include "../include/pid.h"


float PID::output(float newError) {
	updateErrors(newError);
	return P * error + I * errorSum + D * (error - lastError) * 1000 / TIMER_MS;
}

void PID::updateErrors(float newError) {
	lastError = error;
	error = newError;
	errorSum += error;
	if (errorSum > maxIError) {
		// errorSum = maxIError;
		errorSum = 0;
	} else if (errorSum < - maxIError) {
		errorSum = - maxIError;
	}
}

void PID::resetErrors() {
	error = 0;
	lastError = 0;
	errorSum = 0;
}
