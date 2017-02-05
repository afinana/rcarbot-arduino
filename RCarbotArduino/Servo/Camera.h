/* 
* Camera.h
*
* Created: 12/11/2016 10:09:30
* Author: Antonio
*/
#include <Arduino_FreeRTOS.h>

#include "Servo.h"
#include "Arduino.h"


#ifndef __CAMERA_H__
#define __CAMERA_H__



class Camera
{
//variables
public:
protected:
private:

Servo *myServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
// Global serial handle
int pos = 0;    // variable to store the servo position


//functions
public:
	Camera();
	~Camera();
	void setup(const int pingServo);
	void loop();
	void setPosition(const int pos);


protected:
private:
	Camera( const Camera &c );
	Camera& operator=( const Camera &c );

}; //Camera

#endif //__CAMERA_H__
