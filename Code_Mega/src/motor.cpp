/**
 * \file motor.cpp
 * \brief Class which represents and commands a motor.
**/

#include "../include/motor.h"

Motor rightMotor = Motor(MOT_RIGHT_FORWARD, MOT_RIGHT_BACKWARD, MOT_RIGHT_PWM, 'R');
Motor leftMotor = Motor(MOT_LEFT_FORWARD, MOT_LEFT_BACKWARD, MOT_LEFT_PWM, 'L');


Motor::Motor(uint8_t forwardPin, uint8_t backwardPin, uint8_t pwmPin, char dbg_id)
	: forwardPin(forwardPin), backwardPin(backwardPin), pwmPin(pwmPin), dbg_id(dbg_id) {
	// Place init code here if needed
}

void Motor::init(bool enableAfterInit) {
	pinMode(forwardPin, OUTPUT);
	pinMode(backwardPin, OUTPUT);
	pinMode(pwmPin, OUTPUT);
	enable(enableAfterInit);
}

void Motor::enable(bool enabled) {
	if (enabled != isEnabled) {
		isEnabled = enabled;
		if (isEnabled) {
			digitalWrite(forwardPin, currentDir);
			digitalWrite(backwardPin, !currentDir);
			analogWrite(pwmPin, currentPWM);
		} else {
			digitalWrite(forwardPin, LOW);
			digitalWrite(backwardPin, LOW);
			analogWrite(pwmPin, 0);
		}

		#ifdef DEBUG_MOTOR
		Serial.write(dbg_id);
		Serial.print(" motor: ");
		Serial.println(isEnabled ? "Enabled" : "Disabled");
		#endif // DEBUG_MOTOR
	}
}

void Motor::sendPWM(uint8_t pwm, bool dirForward, bool force) {
	if (dirForward != currentDir) {
		// Disable motors before changing PWM if changing direction
		digitalWrite(forwardPin, LOW);
		digitalWrite(backwardPin, LOW);
	}

	if (pwm != currentPWM) {
		if (!force || dirForward == currentDir) {
			if (pwm > currentPWM and pwm - currentPWM > MAX_PWM_DIFFERENCE) {
				pwm = min(255, pwm + MAX_PWM_DIFFERENCE);	
			} else if (currentPWM - pwm > MAX_PWM_DIFFERENCE) {
				pwm = max(0, pwm - MAX_PWM_DIFFERENCE);
			}
		}

		if (isEnabled)
			analogWrite(pwmPin, pwm);
		currentPWM = pwm;

		#ifdef DEBUG_MOTOR
		Serial.write(dbg_id);
		Serial.print(" motor: New PWM: ");
		Serial.println(pwm);
		#endif // DEBUG_MOTOR
	}

	if (dirForward != currentDir) {
		if (isEnabled) {
			digitalWrite(forwardPin, dirForward ? HIGH : LOW);
			digitalWrite(backwardPin, dirForward ? LOW : HIGH);
		}
		currentDir = dirForward;

		#ifdef DEBUG_MOTOR
		Serial.write(dbg_id);
		Serial.print(" motor: New DIR: ");
		Serial.println(dirForward ? "Forward" : "Backward");
		#endif // DEBUG_MOTOR
	}
}
