/*
 * \file Code_Mega.ino
 * \brief Holds the Arduino setup and loop functions, which make the robot run.
*/
 
#include <SimpleTimer.h>

#include "include/pins.h"
#include "include/parameters.h"
#include "include/motor.h"
#include "include/control.h"
#include "include/collisions.h"
#include "include/robotstate.h"
#include "include/goal.h"
#include "include/goalslist.h"

/************************/
/* ACTION SET SELECTION */
/************************/
#include "actionsets/manualServos.h"
/************************/

extern Motor rightMotor;
extern Motor leftMotor;
extern RobotState robotState;
extern Collisions collisions;
extern GoalsList goalsList;

SimpleTimer asserv_timer = SimpleTimer();

void waitForTirette();
void asservLoop();

void setup() {
	#ifdef DEBUG
	Serial.begin(115200);
	Serial.println(">>> Robot Startup - Robotik 2022 <<");
	#endif // DEBUG

	asserv_timer.setInterval(TIMER_MS, asservLoop);

	pinMode(TIRETTE, INPUT_PULLUP);
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);

	rightMotor.init(true);
	leftMotor.init(true);

	#ifndef BYPASS_TIRETTE
	waitForTirette();
	#endif // NOT BYPASS_TIRETTE

	fillGoals();
}

void loop() {
	asserv_timer.run();
}

void asservLoop() {
	robotState.update();
	collisions.update();
	goalsList.processCurrentGoal();
}

void waitForTirette() {
	uint32_t last_millis = 0;
	bool led_state = false;

	// Wait for Tirette insertion
	if (!digitalRead(TIRETTE)) {
		#ifdef DEBUG_MATCH
		Serial.println("/!\\ Tirette not in place ! Waiting..");
		#endif // DEBUG_MATCH
		while (!digitalRead(TIRETTE)) {
			if (millis() - last_millis > 150) {
				last_millis = millis();
				digitalWrite(LED_RED, led_state ^= 1);
			}
		delay(1);
		}
		digitalWrite(LED_RED, led_state = false);
		delay(300);
	}

	// Wait for Tirette withdrawal
	#ifdef DEBUG_MATCH
	Serial.println("Waiting Tirette signal to start the match !");
	#endif // DEBUG_MATCH
	while (digitalRead(TIRETTE)) {
		if (millis() - last_millis > 350) {
			last_millis = millis();
			digitalWrite(LED_BLUE, led_state ^= 1);
		}
		delay(1);
	}
	digitalWrite(LED_BLUE, HIGH);
	#ifdef DEBUG_MATCH
	Serial.println("Gooo !");
	#endif // DEBUG_MATCH
}
