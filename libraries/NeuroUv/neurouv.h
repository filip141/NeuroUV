/*
Neurouv.h is header file for Neuro Unmanned Vehicle driver 

NeuroUv library contains whole functions to control vehicle, get 
information from the sensors and send it to Robotic Operating System.

Project is supported by Neurosoft Co

Created by Filip Bachura, June 29, 2015.

*/

#ifndef NEUROUV_H
#define NEUROUV_H

#include <Arduino.h>

#include <ros.h>
#include <Wire.h>

//Sensor Libraries
#include <HMC5883L.h>
#include <L3G4200D.h>
#include <ADXL345.h>
#include <BMP085.h>
#include <Robot_motors.h>

// Avr Libs
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

//Messages
#include <controlvehicle/joy_control_msg.h>
#include <controlvehicle/temperature.h>
#include <controlvehicle/Maxsonar.h>
#include <controlvehicle/ardu_imu.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>

//Settings gyroscope defined
#define L3G4200D_2000DPS 0x20
#define L 0.95
#define dpsPerDigit .07f
#define temstep 5000
#define debstep 600
#define batstep 166
#define errstep 120
#define sonstep 49
#define time_step 10

//Define pw pins
#define pwPin 3
#define pwPin2 5
#define pwPin3 6
#define pwPin4 11

extern "C" void TIMER5_COMPA_vect(void) __attribute__ ((signal));
extern "C" void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs);

class NeuroUV
{

	public:
		// Gyroscope
		L3G4200D gyro;
		// Accelerometer
		ADXL345 accelerometer;
		// Magnetometer
		HMC5883L compass;
		// Barometer
		BMP085 bmp;
		// Constructor
		NeuroUV(void);
		//ROS Subscriber initialization
		ros::Subscriber<controlvehicle::joy_control_msg> *rosTopic;
		//Function Declaration
		void setupTimer();
		int freeRam();
		void sensorsVelocity();
		void tempsensorsVelocity();
		void sonarsensorsVelocity();
		void errorhandle();
		void UARThandle();
		// begin object to initialize build in objects
		void begin();
		// Initialize ROS
		void initROS();
		// main loop
		void ROSloop();
		void Debugloop();
		// Check imu connection
		void imuCheck();
		//Sort double array
		void sort( double* n, int q );
		//Check battery state
		void batteryState();
		// C driver handler
		friend void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs);
		// ISR friendly function
		friend void TIMER5_COMPA_vect(void);

	private:
		// Ros initialization
		ros::NodeHandle  nh;
		// Robot control driver declaration
		RobotControl* rb;
		// Messages
		controlvehicle::ardu_imu imu_msg;
		controlvehicle::temperature tem_msg;
		controlvehicle::Maxsonar son_msg;
		std_msgs::String err_msg;
		std_msgs::Int8 bat_msg;
		//Sonar counter
		byte sonnum;
		byte periodnum;
		//Driving subscriber variables
		int pspeed;
		int pPowerLR;
		// Battery state auxiliary variables
		int counter;
		double voltageSet[50];
		float voltagestep;
		double voltage;
		int sensorValue;
		// global safety counter
		uint16_t saftyCounter;
		// old counter value
		uint16_t saftyCounterOld;
		// Sensor shutdown
		volatile uint8_t sensorOneShutdown;
		volatile uint8_t sensorTwoShutdown;
		volatile uint8_t sensorThreeShutdown;
		volatile uint8_t sensorFourShutdown;
		// imu shutdown
		volatile uint8_t imuShutdown;
		//Pseudo Arduino timer
		unsigned long rangeMillis;
		unsigned long rtemMillis;
		unsigned long rsonMillis;
		unsigned long rerrMillis;
		unsigned long rbatMillis;
		unsigned long rdebMillis;
		//Publishers
		ros::Publisher *pub_imu;
		ros::Publisher *pub_tem;
		ros::Publisher *pub_son;
		ros::Publisher *pub_err;
		ros::Publisher *pub_bat;

};

namespace NeuroSpace
{
	/* Object are build here because using Arduino IDE
	 * we can't send argument to class friend function
	 * like class object
	 */

	extern NeuroUV neuroObject;
};

#endif
