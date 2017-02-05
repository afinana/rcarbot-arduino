/* 
* Motor.h
*
* Created: 12/11/2016 10:07:25
* Author: Antonio
*/


#ifndef __MOTOR_H__
#define __MOTOR_H__

const int LED=13;

//This program is used to control a robot using a app that communicates with Arduino through a serial module.
// using a L298n Motor Driver.
// F:forward
// B:back
// R:right
// G:forward Left
// I:forward right
// H:back left
// J:back right
// speed:0..9
// q:max speed
//Error Code Chart:
// Code 01; Turnradius is higher than Speed; 
// Code 02; Speed is higher than 255;

class Motor
{
//variables
public:
protected:
private:

int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.

//L298n Motor Driver pins.
int dirPin1=5; 
int dirPin2=6;
int speedPin1=10;
int speedPin2=11;

//functions
public:
	Motor();
	~Motor();
	void setup();
	void loop();
	
	void forward();
	void left();
	void right();
	void back();
	void forwardleft();
	void forwardright();
	void backright();
	void backleft();
	void stop();
	void brakeOff();
	void brakeOn();
	void process_command(const char command);

protected:
private:
	Motor( const Motor &c );
	Motor& operator=( const Motor &c );

}; //Motor

#endif //__MOTOR_H__
