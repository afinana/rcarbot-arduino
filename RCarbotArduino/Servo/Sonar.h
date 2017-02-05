/* 
* Sonar.h
*
* Created: 12/11/2016 10:08:47
* Author: Antonio
*/
#include <Arduino_FreeRTOS.h>

#ifndef __SONAR_H__
#define __SONAR_H__


class Sonar
{
//variables
public:
protected:
private:
// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, cm;
int pingTrig,pingEcho;

//functions
public:
	Sonar();
	~Sonar();
	// Setup pins trigger and Echo
	void setup(const int vpinTrig, const int vpingEcho);
	// Send echo signal and read return echo value
	void ping();
protected:
private:
	Sonar( const Sonar &c );
	Sonar& operator=( const Sonar &c );
	long microsecondsToCentimeters(long microseconds);

}; //Sonar

#endif //__SONAR_H__
