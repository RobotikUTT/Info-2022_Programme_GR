/**
 * \file calibatrion.h
 * \brief Manual controls of the six Servos through the Serial Monitor.
**/

#include <math.h>
#include "../include/goal.h"
#include "../include/goalslist.h"

extern GoalsList goalsList;


class Blank : public Goal {
public:
    Blank() : Goal() {}

    void process() {}
};


void fillGoals() {
    goalsList.addGoal(new InhibSonar(SONAR_FRONT_RIGHT | SONAR_FRONT_LEFT | SONAR_BACK_RIGHT | SONAR_BACK_LEFT, true));
    // goalsList.addGoal(new Blank());
    // Jog(linearSpeed, angularSpeed, duration) mm/s, mm/s, ms
    // goalsList.addGoal(new Jog(300, 0, 1200));
    goalsList.addGoal(new Goto(200, 0));
    goalsList.addGoal(new Rot(M_PI / 2));

    goalsList.addGoal(new Goto(200, 200));
    // goalsList.addGoal(new Rot(1 * M_PI));
    // goalsList.addGoal(new Blank());
}
