
#include "../include/goal.h"
#include "../include/goalslist.h"

void fillGoals() {
	// if side is yellow
		int x = 51, y = 508;
		// set initial position at x : 51, y : 508
		x = 400;
		goalsList.addGoal(new Goto(0, x, y));
		y = 200;
		goalsList.addGoal(new Goto(0, x, y));
		x = 1350;
		goalsList.addGoal(new Goto(0, x, y));
		y = 675;
		goalsList.addGoal(new Goto(0, x, y));
		x = 400;
		goalsList.addGoal(new Goto(0, x, y));
	// else
		int x = 3000 - 51, y = 508;
		// set inital position at x : 3000-51, y : 508
		x = 3000 - 400;
		goalsList.addGoal(new Goto(0, x, y));
		y = 200;
		goalsList.addGoal(new Goto(0, x, y));
		x = 3000 - 1350;
		goalsList.addGoal(new Goto(0, x, y));
		y = 675;
		goalsList.addGoal(new Goto(0, x, y));
		x = 3000 - 400;
		goalsList.addGoal(new Goto(0, x, y));
}
