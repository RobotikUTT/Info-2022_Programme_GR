/**
 * \file goal.h
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#ifndef GOAL_H
#define GOAL_H

#include "control.h"
#include "robotstate.h"
#include "parameters.h"

/**
 * \brief Mother goal class. Represents an empty goal.
**/


class Goal {
public:
	/**
	 * \brief Sends the position error to @see control.h.
	 * subclasses must override this function.
	**/
	virtual void process() {
		reached = true;
		#ifdef DEBUG_GOAL
		Serial.println("Goal::process()");
		#endif // DEBUG_GOAL
	}

	inline bool isReached() const { return reached; }

protected:
	bool reached = false;
};

/**
 * \brief Goes to a given (x,y) absolute position in mm
**/
class Goto : public Goal {
public:
	/**
	 * \brief constructor of Goto order.
	 * \param x x coordinate in mm
	 * \param y y coordinate in mm
	 * \param maxSpeed max speed at which we want to go in mm/s. Cannot exceed MAX_SPEED. 0 for default.
	**/
	Goto(char type, float x, float y, float maxSpeed = 0) : Goal(), x(x), y(y), maxSpeed(maxSpeed), type(type) {}

	virtual void process();

private:
	float x, y, maxSpeed; // mm, mm, mm/s
	char type;
};

/**
 * \brief Rotates to a given angle in radians.
**/
class Rot : public Goal {
public:
	Rot(char type, float theta) : Goal(), theta(theta), type(type) {}

	virtual void process();

private:
	float theta; // rad
	char type;
};

// add new goals here and override process()

#endif // GOAL_H
