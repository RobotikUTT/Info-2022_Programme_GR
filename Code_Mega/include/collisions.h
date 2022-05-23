/**
 * \file collisions.h
 * \brief Class which holds a maximal speed value based on the proximity of obstacles.
**/

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "pins.h"
#include "parameters.h"

//typedef struct {float ahead, behind;} Obstacle;

class Collisions  {
public:
	/**
	 * Updates the maximal speed based on the distance to the nearest obstacle.
	**/
	void update();
	float readSensors(short triggerpin, short echopin );
	const float getMaxSpeed();

private:
	int maxSpeed; // mm/s
	//Obstacle obst = {0,0};
};

#endif // COLLISIONS_H
