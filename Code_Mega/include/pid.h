/**
 * \file pid.h
 * \brief Basic PID class.
**/

#ifndef PID_H
#define PID_H

#include "parameters.h"

class PID {
public:
	PID(float P, float I, float D, float maxIError) : P(P), I(I), D(D), maxIError(maxIError) {}

	/**
	 * \brief updates the errors and computes the result.
	 * \return PID output
	**/
	float output(float newError);
	void resetErrors();

private:
	float P, I, D;
	float maxIError;

	float error = 0;
	float errorSum = 0;
	float lastError = 0;

	void updateErrors(float error);
};

#endif // PID_H
