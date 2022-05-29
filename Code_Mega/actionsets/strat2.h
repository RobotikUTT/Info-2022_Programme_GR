/*
But de ce programme: Marquer des points en poussant des hexagones à droite avec bras droite coté jaune
*/

#include <math.h>

#include "../include/goal.h"
#include "../include/goalslist.h"
#include "../include/robotstate.h"
#include "../include/servos.h"

extern Servos servos;

extern GoalsList goalsList;
extern RobotState robotState;
extern bool isSideYellow;


class BrasExt : public Goal {
public:
	BrasExt() : Goal() {}

	virtual void process();

};

void BrasExt::process() {
	servos.setPosXL320(1, 750);
	delay(2000);
	servos.setPosXL320(2, 300);
	delay(2000);
	servos.setPosXL320(3, 500);
	delay(2000);
	servos.setPosXL320(4, 500);
	delay(2000);
	reached = true;
};

class BrasInt : public Goal {
public:
	BrasInt(char arm) : Goal(), arm(arm) {}

	virtual void process();

private:
	char arm;
};

void BrasInt::process() {
	if (arm == 'R') {
		servos.setPosXL320(1, 200);
	}
	else {
		servos.setPosXL320(2, 810);
	}
	reached = true;
};

void fillGoals() {
	float x = 830; // yellow side north
	float y = 90; // yellow side north
	Position startPosition = {x, y, 0};
	robotState.setPosition(startPosition);
	x += 190;//19
	
	
	goalsList.addGoal(new BrasExt());

	goalsList.addGoal(new Goto(x, y, FORWARD)); // pour  forcer en avant

	// goalsList.addGoal(new Delay(2000));
	goalsList.addGoal(new BrasInt(isSideYellow ? 'R' : 'L'));
	goalsList.addGoal(new Delay(2000));



	x -= 950;
	goalsList.addGoal(new Goto(x, y, BACKWARD));
	x += 600;
	goalsList.addGoal(new Goto(x, y, FORWARD));


}