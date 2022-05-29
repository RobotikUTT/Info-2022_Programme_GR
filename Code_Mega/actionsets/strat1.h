/*
But de ce programme: Marquer des points en poussant des hexagones dans la base
*/

#include <math.h>

#include "../include/goal.h"
#include "../include/goalslist.h"
#include "../include/robotstate.h"

extern GoalsList goalsList;
extern RobotState robotState;
extern bool isSideYellow;

void fillGoals() {
	float x = 51; // yellow side north
	float y = 508; // yellow side north
	Position startPosition = {x, y, 0};
	robotState.setPosition(startPosition);
	x = 520;
	goalsList.addGoal(new DisplayScore(4));
	goalsList.addGoal(new Goto(x, y, FORWARD)); // pour  forcer en avant
	
	if (isSideYellow) {
		y += 180; // y inversé
	}
	else {
		y -= 180;
	}
	goalsList.addGoal(new InhibSonar(SONAR_FRONT_RIGHT | SONAR_FRONT_LEFT, true));
	goalsList.addGoal(new Goto(x, y, FORWARD));
	goalsList.addGoal(new Rot(0)); // tj absolu
	goalsList.addGoal(new InhibSonar(SONAR_FRONT_RIGHT | SONAR_FRONT_LEFT, false));

	x += 685;
	goalsList.addGoal(new Goto(x, y, FORWARD));


	
	if (isSideYellow) {
		y -= 180; // y inversé
	}
	else {
		y += 180;
	}
	goalsList.addGoal(new Goto(x, y, FORWARD));
	x = 300;
	if (isSideYellow) {
		y -= 50; // y inversé
	}
	else {
		y += 50;
	}
	goalsList.addGoal(new Goto(x, y, FORWARD));
	goalsList.addGoal(new DisplayScore(25));
	/*x += 1160;
	goalsList.addGoal(new Goto(x, y, BACKWARD));
	y -= 220;
	goalsList.addGoal(new Goto(x, y, FORWARD));
	x -= 1160;
	goalsList.addGoal(new Goto(x, y, FORWARD));*/
}