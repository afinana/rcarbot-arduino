/* 
* Camera.cpp
*
* Created: 12/11/2016 10:09:30
* Author: middleland
*/


#include "Camera.h"


// default constructor
Camera::Camera()
{
	myServo = new Servo();
} //Camera

// default destructor
Camera::~Camera()
{
} //~Camera



void Camera::setup(const int pinServo) {
	
	myServo->attach(pinServo);  // attaches the servo on pin 2 to the servo object
}

void Camera::loop()
{
	myServo->write(0);              // tell servo to go to position in variable 'pos'
	//delay(15);
	vTaskDelay( 5 / portTICK_PERIOD_MS );  // waits 15ms for the servo to reach the position
		
	
	
	//for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
	for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
	{                                  // in steps of 1 degree
		myServo->write(pos);              // tell servo to go to position in variable 'pos'
		//delay(15);    // waits 15ms for the servo to reach the position
		vTaskDelay( 15 / portTICK_PERIOD_MS );  // waits 15ms for the servo to reach the position
		
		//ping();
	}
	for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees
	{
		myServo->write(pos);              // tell servo to go to position in variable 'pos'
		//delay(15);                       // waits 15ms for the servo to reach the position
		vTaskDelay( 15 / portTICK_PERIOD_MS );  // waits 15ms for the servo to reach the position
			
		//ping();
	}
}

void Camera::setPosition(const int pos){
	myServo->write(pos);
	//delay(15);
	vTaskDelay( 5 / portTICK_PERIOD_MS );  // waits 15ms for the servo to reach the position

}
