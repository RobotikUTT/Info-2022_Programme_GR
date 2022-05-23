/**
 * \file goalslist.cpp
 * \brief Class which holds a fifo of goals. @see goal.h
**/

#include "../include/goalsList.h"

extern Control control;

GoalsList goalsList;


void GoalsList::resetGoals() {
	currentGoalIndex = 0;
	lastGoalIndex = 0;
	goalsPtr[currentGoalIndex] = new Goal();
}

void end() {
	// digitalWrite(FORWARD_LEFT, 0);
	// digitalWrite(BACKWARDS_LEFT, LOW);
	// digitalWrite(FORWARD_RIGHT, LOW);
	// digitalWrite(BACKWARDS_RIGHT, 0);
	while (true) {

	}
}

void GoalsList::processCurrentGoal() {
	if (goalsPtr[currentGoalIndex]->isReached()){
		if (currentGoalIndex >= lastGoalIndex) {
			end();
		}
		else {
			currentGoalIndex++;
			control.resetPIDs();
		}
	}
	else {
		goalsPtr[currentGoalIndex]->process();
	}
	//Serial.print("currentGoalIndex : ");
	//Serial.println(currentGoalIndex);
}

void GoalsList::addGoal(Goal* pGoal) {
	lastGoalIndex++;
	if (lastGoalIndex >= MAX_SIMULTANEOUS_GOALS) {
		#ifdef DEBUG_GOAL
		Serial.println("GoalsList: ERROR : Too many Goals");
		#endif // DEBUG_GOAL

		lastGoalIndex = MAX_SIMULTANEOUS_GOALS - 1;
		return;
	}
	goalsPtr[lastGoalIndex] = pGoal;
}
