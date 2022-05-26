/**
 * \file goal.h
 * \brief Multiple position goal classes which send position errors to @see control.h.
**/

#ifndef GOAL_H
#define GOAL_H

#include "nano.h"
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
	Goto(float x, float y, float maxSpeed = 0) : Goal(), x(x), y(y), maxSpeed(maxSpeed) {}

	virtual void process();

private:
	float x, y, maxSpeed; // mm, mm, mm/s
	unsigned long startTimeoutStop = 0;
	bool stop = false;
};

/**
 * \brief Rotates to a given angle in radians.
**/
class Rot : public Goal {
public:
	Rot(float theta) : Goal(), theta(theta) {}

	virtual void process();

private:
	float theta; // rad
	bool stop = false;
	unsigned long startTimeoutStop = 0;
};

/**
 * \brief Set a target speed for specified duration
**/
class Jog : public Goal {
public:
	/**
	 * \brief constructor of Jog order.
	 * \param linearSpeed Target linear Speed
	 * \param angularSpeed Target angular Speed
	 * \param duration Duration of the jog movement in ms
	**/
	Jog(float linearSpeed, float angularSpeed, unsigned long duration)
	: Goal(), linearSpeed(linearSpeed), angularSpeed(angularSpeed), duration(duration) {}

	virtual void process();

private:
	float linearSpeed, angularSpeed; // mm/s, mm/s
	unsigned long duration, // ms
	startTimeGoal = 0, startTimeoutStop = 0; // ms, ms
};

/**
 * \brief Enable/Disable specified Sonar sensors
**/
class InhibSonar : public Goal {
public:
	/**
	 * \brief constructor of InhibSonar order.
	 * \param sonarMask Bit mask of the sonars to modify
	 * \param inhib if true: inhib selected sonars, else reactivate them
	**/
	InhibSonar(uint8_t sonarMask, bool inhib)
	: Goal(), sonarMask(sonarMask), inhib(inhib) {}

	virtual void process();

private:
	uint8_t sonarMask;
	bool inhib;
};


// add new goals here and override process()

#endif // GOAL_H
