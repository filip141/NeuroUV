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
#include <Gy80lib.h>
#include <BMP085.h>
#include <Robot_motors.h>

// Avr Libs
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

//Messages
#include <controlvehicle/joy_control_msg.h>
#include <controlvehicle/temperature.h>
#include <geometry_msgs/Quaternion.h>
#include <controlvehicle/Maxsonar.h>
#include <controlvehicle/ardu_imu.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int8.h>
#include <std_msgs/String.h>


//Time stamps
#define temstep 5000
#define debstep 600
#define batstep 166
#define errstep 120
#define sonstep 49
#define time_step 10
#define checkstep 250

//Define pw pins
#define pwPin 3
#define pwPin2 5
#define pwPin3 6
#define pwPin4 11

extern "C" void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs);

class NeuroUV
{

	public:
		// Gy-80 Sensor library
		Gy80lib imu;
		// Barometer
		BMP085 bmp;
		// Constructor
		NeuroUV(void);
		//ROS Subscriber initialization
		ros::Subscriber<controlvehicle::joy_control_msg> *rosTopic;
		//Function Declaration
		int freeRam();
		void sensorsVelocity();
		void tempsensorsVelocity();
		void sonarsensorsVelocity();
		void errorhandle();
		void UARThandle();
		// begin object to initialize build in objects
		void begin();
		// Calibrate imu
		void imuCalibration();
		// Initialize ROS
		void initROS();
		// main loop
		void ROSloop();
		void Debugloop();
		// Check imu connection
		void disableImu();
		void checkSensors();
		//Sort double array
		void sort( double* n, int q );
		//Check battery state
		void batteryState();
		// C driver handler
		friend void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs);

	private:
		// Ros initialization
		ros::NodeHandle  nh;
		// Robot control driver declaration
		RobotControl* rb;
		// Messages
		controlvehicle::temperature tem_msg;
		geometry_msgs::Quaternion quat_msg;
		controlvehicle::ardu_imu imu_msg;
		geometry_msgs::Vector3 euler_msg;
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
		unsigned long rcheckMillis;
		//Publishers
		ros::Publisher *pub_imu;
		ros::Publisher *pub_euler;
		ros::Publisher *pub_quat;
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
