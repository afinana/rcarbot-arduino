/* 
* Sonar.cpp
*
* Created: 12/11/2016 10:08:47
* Author: Antonio
*/

#include "Arduino.h"
#include "Sonar.h"

// default constructor
Sonar::Sonar()
{
} //Sonar

// default destructor
Sonar::~Sonar()
{
} //~Sonar

// Setup pins trigger and Echo
void Sonar::setup(const int vpinTrig, const int vpingEcho) {
	
	pingTrig=vpinTrig;
	pingEcho=vpingEcho;
	
}

long Sonar::microsecondsToCentimeters(long microseconds) {
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29 / 2;
}

void Sonar::ping(){

	
	
	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(pingTrig, OUTPUT);
	digitalWrite(pingTrig, LOW);
	//delayMicroseconds(2);
	vTaskDelay( 2 / portTICK_PERIOD_MS ); // wait for 2ms
	digitalWrite(pingTrig, HIGH);
	//delayMicroseconds(5);
	vTaskDelay( 5 / portTICK_PERIOD_MS ); // wait for 5ms
	digitalWrite(pingTrig, LOW);

	// The same pin is used to read the signal from the PING))): a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(pingEcho, INPUT);
	duration = pulseIn(pingEcho, HIGH);

	// convert the time into a distance
	cm = microsecondsToCentimeters(duration);

	Serial.print(cm);
    Serial.println("cm");
	
	vTaskDelay( 2 / portTICK_PERIOD_MS ); // wait for 2ms

	
}
