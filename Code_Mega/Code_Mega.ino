/*
 * \file Code_Mega.ino
 * \brief Holds the Arduino setup and loop functions, which make the robot run.
*/

// #include <SimpleTimer.h>

#include "include/pins.h"
#include "include/parameters.h"
#include "lib/Arduino-SimpleTimer/SimpleTimer/SimpleTimer.h"

SimpleTimer asserv_timer = SimpleTimer();

void waitForTirette();
void asservLoop();

void setup() {
	#ifdef DEBUG
	Serial.begin(115200);
	Serial.println(">>> Robot Startup - Robotik 2022 <<");
	#endif
	asserv_timer.setInterval(TIMER_MS, asservLoop);

	pinMode(TIRETTE, INPUT_PULLUP);
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);

	waitForTirette();
}

void loop() {
	asserv_timer.run();
}

void asservLoop() {
	// robotState.update();
	// collisions.update();
	// goalList.processCurrentGoal();  
}

void waitForTirette() {
	uint32_t last_millis = 0;
	bool led_state = false;

	// Wait for Tirette insertion
	if (!digitalRead(TIRETTE)) {
		#ifdef DEBUG
		Serial.println("/!\\ Tirette not in place ! Waiting..");
		#endif
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
	#ifdef DEBUG
	Serial.println("Waiting Tirette signal to start the match !");
	#endif
	while (digitalRead(TIRETTE)) {
		if (millis() - last_millis > 350) {
			last_millis = millis();
			digitalWrite(LED_BLUE, led_state ^= 1);
		}
		delay(1);
	}
	digitalWrite(LED_BLUE, HIGH);
	#ifdef DEBUG
	Serial.println("Gooo !");
	#endif
}
