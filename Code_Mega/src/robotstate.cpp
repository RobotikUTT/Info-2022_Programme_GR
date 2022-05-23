/**
 * \file robotstate.cpp
 * \brief Class which holds position and speed data and updates with coders.
**/

#include "../include/robotstate.h"
#include <math.h>

RobotState robotState;
Encoder rightEnc = Encoder(ENCODER_RIGHT_A, ENCODER_RIGHT_B);
Encoder leftEnc = Encoder(ENCODER_LEFT_A, ENCODER_LEFT_B);


void RobotState::update() {
    static unsigned long lastMillis = 0;
    static long leftLastTicks = 0, rightLastTicks = 0;
    static float lastAngle = 0;

    int leftTicks = leftEnc.read();
    int rightTicks = -rightEnc.read();

    unsigned long
    t = millis(),
    dt = t - lastMillis;

    float dLeft = (float)(leftTicks - leftLastTicks) * DISTANCE_PER_TICK;    // mm
    float dRight = (float)(rightTicks - rightLastTicks) * DISTANCE_PER_TICK; // mm
    wheelSpeeds.left = (1000 * dLeft) / dt;   // mm/s
    wheelSpeeds.right = (1000 * dRight) / dt; // mm/s

    float dAngle = atan2((dRight - dLeft), ENTRAXE);
    position.theta += dAngle;
    position.theta = fmod(position.theta, 2 * M_PI);

    float dDistance = (dRight + dLeft) / 2.0;

    float meanTrajAngle = (position.theta + lastAngle) / 2.0;

    position.x += dDistance * cos(meanTrajAngle); 
    position.y += dDistance * sin(meanTrajAngle);

    #ifdef DEBUG_ROBOTSTATE
    Serial.print("LeftEnc : ");
    Serial.println(leftTicks);
    Serial.print("RightEnc : ");
    Serial.println(rightTicks);
    Serial.print("WheelSpeeds: Left=");
    Serial.print(wheelSpeeds.left);
    Serial.print("; Right=");
    Serial.println(wheelSpeeds.right);
    Serial.print("Position: X=");
    Serial.print(position.x);
    Serial.print("; Y=");
    Serial.print(position.y);
    Serial.print("; theta=");
    Serial.println(position.theta, 3);  // X.XXX
    #endif // DEBUG_ROBOTSTATE

    lastMillis = t;
    lastAngle = position.theta;
    rightLastTicks = rightTicks;
    leftLastTicks = leftTicks;
}
