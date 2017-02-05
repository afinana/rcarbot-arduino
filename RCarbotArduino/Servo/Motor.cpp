/*
* Motor.cpp
*
* Created: 12/11/2016 10:07:24
* Author: Antonio
*/

#include "Arduino.h"
#include "Motor.h"

// default constructor
Motor::Motor()
{
} //Motor


// default destructor
Motor::~Motor()
{
} //~Motor

// Setup input/output pins
void Motor::setup() {

	pinMode(dirPin1, OUTPUT);
	pinMode(dirPin2, OUTPUT);
	pinMode(speedPin1, OUTPUT);
	pinMode(speedPin2, OUTPUT);
	pinMode(LED, OUTPUT); //Set the LED pin.
	
}
// Loop method
void Motor::loop() {
	if (Serial.available() > 0) {
		command = Serial.read();
		stop(); //Initialize with motors stoped.
		process_command(command);
	}
}
// Process motor command
void Motor::process_command(const char command) {
	
	stop(); //Initialize with motors stoped.
	switch (command) {
		case 'F':
		forward();
		break;
		case 'B':
		back();
		break;
		case 'L':
		left();
		break;
		case 'R':
		right();
		break;
		case 'G':
		forwardleft();
		break;
		case 'I':
		forwardright();
		break;
		case 'H':
		backleft();
		break;
		case 'J':
		backright();
		break;
		case '0':
		Speed = 100;
		break;
		case '1':
		Speed = 140;
		break;
		case '2':
		Speed = 153;
		break;
		case '3':
		Speed = 165;
		break;
		case '4':
		Speed = 178;
		break;
		case '5':
		Speed = 191;
		break;
		case '6':
		Speed = 204;
		break;
		case '7':
		Speed = 216;
		break;
		case '8':
		Speed = 229;
		break;
		case '9':
		Speed = 242;
		break;
		case 'q':
		Speed = 255;
		break;
	}
	Speedsec = Turnradius;
	if (brkonoff == 1) {
		brakeOn();
		} else {
		brakeOff();
	}
	
}
void Motor::forward() {
	digitalWrite(dirPin1, LOW);
	digitalWrite(dirPin2, LOW);
	analogWrite(speedPin1, Speed);
	analogWrite(speedPin2, LOW);
}

void Motor::back() {
	digitalWrite(dirPin1, LOW);
	digitalWrite(dirPin2, LOW);
	analogWrite(speedPin1, LOW);
	analogWrite(speedPin2, Speed);
}

void Motor::left() {
	digitalWrite(dirPin1, HIGH);
	digitalWrite(dirPin2, LOW);
	analogWrite(speedPin1, Speed);
	analogWrite(speedPin2, LOW);
}

void Motor::right() {
	digitalWrite(dirPin1, LOW);
	digitalWrite(dirPin2, HIGH);
	analogWrite(speedPin1, Speed);
	analogWrite(speedPin2, LOW);
}
void Motor::backleft() {
	digitalWrite(dirPin1, HIGH);
	digitalWrite(dirPin2, LOW);
	analogWrite(speedPin1, LOW);
	analogWrite(speedPin2, Speed);
}
void Motor::backright() {
	digitalWrite(dirPin1, LOW);
	digitalWrite(dirPin2, HIGH);
	analogWrite(speedPin1, LOW);
	analogWrite(speedPin2, Speed);
}
void Motor::forwardright() {
	digitalWrite(dirPin1, HIGH);
	digitalWrite(dirPin2, LOW);
	analogWrite(speedPin1, Speed);
	analogWrite(speedPin2, LOW);
}
void Motor::forwardleft() {
	digitalWrite(dirPin1, LOW);
	digitalWrite(dirPin2, HIGH);
	analogWrite(speedPin1, Speed);
	analogWrite(speedPin2, LOW);
}

void Motor::stop() {
	digitalWrite(dirPin1, LOW);
	digitalWrite(dirPin2, LOW);
	analogWrite(speedPin1, LOW);
	analogWrite(speedPin2, LOW);
}

void Motor::brakeOn() {
	//Here's the future use: an electronic braking system!
	// read the pushbutton input pin:
	buttonState = command;
	// compare the buttonState to its previous state
	if (buttonState != lastButtonState) {
		// if the state has changed, increment the counter
		if (buttonState == 'S') {
			if (lastButtonState != buttonState) {
				digitalWrite(dirPin1, HIGH);
				digitalWrite(dirPin2, HIGH);
				digitalWrite(speedPin1, HIGH);
				digitalWrite(speedPin2, HIGH);
				delay(brakeTime);
				stop();
			}
		}
		// save the current state as the last state,
		//for next time through the loop
		lastButtonState = buttonState;
	}
}
void Motor::brakeOff() {

}