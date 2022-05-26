/**
 * \file calibatrion.h
 * \brief Manual controls of the six Servos through the Serial Monitor.
**/

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
    // goalsList.addGoal(new Jog(250, 0, 1500));
    // goalsList.addGoal(new Goto(100, 0));
    goalsList.addGoal(new Rot(0.5 * 3.14159265358979323846));
    // goalsList.addGoal(new Blank());
}
