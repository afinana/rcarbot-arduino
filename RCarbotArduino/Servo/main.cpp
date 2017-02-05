#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include "Camera.h"
#include "Motor.h"
#include "Sonar.h"


// Ping Servo
// this constant won't change.  It's the pin number
// of the sensor's output:
#define  pingServo  2

// Ping module pins
// this constant won't change.  It's the pin number
// of the sensor's output:
#define  pingTrig  4
#define  pingEcho  5

//L298n Motor Driver pins.
#define   in1 5
#define   in2 6
#define   in3 10
#define   in4 11

Camera myCamera;
Sonar mySonar;

// define two tasks Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

// define two tasks for Pin Camera & Read ping value
void TaskCamera(void *pvParameters );
void TaskPingRead( void *pvParameters );



// the setup function runs once when you press reset or power the board
void setup() {
	
	// initialize serial communication at 9600 bits per second:
	Serial.begin(57600);
	
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
	}

	// Now set up three tasks to run independently.
	 xTaskCreate(
	 TaskBlink
	 ,  (const portCHAR *)"Blink"   // A name just for humans
	 ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
	 ,  NULL
	 ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	 ,  NULL );

	xTaskCreate(
	TaskCamera
	,  (const portCHAR *) "Camera"   // A name just for humans
	,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
	
	xTaskCreate(
	TaskPingRead
	,  (const portCHAR *) "AnalogRead"
	,  128  // Stack size
	,  NULL
	,  3  // Priority
	,  NULL );

	// Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
	// Empty. Things are done in Tasks.
}


/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
	(void) pvParameters;

	/*
	Blink
	Turns on an LED on for one second, then off for one second, repeatedly.

	Most Arduinos have an on-board LED you can control. On the UNO, LEONARDO, MEGA, and ZERO
	it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care
	of use the correct LED pin whatever is the board used.
	
	The MICRO does not have a LED_BUILTIN available. For the MICRO board please substitute
	the LED_BUILTIN definition with either LED_BUILTIN_RX or LED_BUILTIN_TX.
	e.g. pinMode(LED_BUILTIN_RX, OUTPUT); etc.
	
	If you want to know what pin the on-board LED is connected to on your Arduino model, check
	the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
	
	This example code is in the public domain.

	modified 8 May 2014
	by Scott Fitzgerald
	
	modified 2 Sep 2016
	by Arturo Guadalupi
	*/

	// initialize digital LED_BUILTIN on pin 13 as an output.
	pinMode(LED_BUILTIN, OUTPUT);

	for (;;) // A Task shall never return or exit.
	{
		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
	}
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
	(void) pvParameters;
	
	/*
	AnalogReadSerial
	Reads an analog input on pin 0, prints the result to the serial monitor.
	Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
	Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

	This example code is in the public domain.
	*/

	for (;;)
	{
		// read the input on analog pin 0:
		int sensorValue = analogRead(A0);
		// print out the value you read:
		Serial.println(sensorValue);
		vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
	}
}

void TaskCamera(void *pvParameters) // Camera Task
{
	(void) pvParameters;
	// Start loop of camera
	myCamera.setup(pingServo);
	Serial.println("Starting camera");

	for(;;){
		
		myCamera.loop();
		vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
	}

}

void TaskPingRead(void *pvParameters) // Read ping Task
{
	(void) pvParameters;

	// Setup ping trigger & Echo
	mySonar.setup(pingTrig, pingEcho);
	Serial.println("Starting ping");


	// Start loop of read ping
	for(;;){
			
		mySonar.ping();
		vTaskDelay( 15 / portTICK_PERIOD_MS );  // waits 15ms for the servo to reach the position
		
	}
}