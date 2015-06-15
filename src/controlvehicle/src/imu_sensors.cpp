#include "ros/ros.h"
#include <math.h>
#include "MadgwickAHRS.h"
#include "controlvehicle/ardu_imu.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
#include "boost/ref.hpp"

#define GRAVITY_ACCEL 9.80665
#define PI 3.14159265359
#define G_Scale 0.0001


void sensorsCallback(const controlvehicle::ardu_imu::ConstPtr& imuValues, geometry_msgs::Quaternion& quat, geometry_msgs::Vector3& euler,  ros::Publisher& pub_quater, ros::Publisher& pub_euler)
{

	//Magdwick compensate and change to quaterions
	MadgwickAHRSupdate(imuValues->gyroValues.x * (PI/180), imuValues->gyroValues.y * (PI/180), imuValues->gyroValues.z * (PI/180), imuValues->accValues.x, imuValues->accValues.y, imuValues->accValues.z, imuValues->magValues.x * G_Scale, imuValues->magValues.y * G_Scale, imuValues->magValues.z * G_Scale);

	//Set Quaternion message values
	quat.x = q0;
	quat.y = q1;
	quat.z = q2;
	quat.w = q3;

	euler.x = atan2f(2.f *(q0*q1+q2*q3),(q0*q0 - q1*q1 - q2*q2 + q3*q3)) * (180/PI);
	euler.y = asinf(2.f *(q0*q2 - q3*q1)) * (180/PI);
	euler.z = atan2f(2.f *(q0*q3+q1*q2), ( q0*q0 -q1*q1 - q2*q2 - q3*q3)) * (180/PI);

	ROS_INFO("Publishing Frame full of Quaternions ... Yummy");
	ROS_INFO("Publishing Frame full of Euler Angles ... So Common");

	//Publish message
	pub_quater.publish(quat);
	pub_euler.publish(euler);

}


int main(int argc, char **argv)
{
   //Ros node initialization
   ros::init(argc, argv, "imu_sensors");
   ros::NodeHandle n;

   //Publisher message initialization
   geometry_msgs::Quaternion quat;
   geometry_msgs::Vector3 euler;

   //Ros Subscriber and Publisher initialization
   ros::Publisher pub_quater = n.advertise<geometry_msgs::Quaternion>("mgquat", 1);
   ros::Publisher pub_euler = n.advertise<geometry_msgs::Vector3>("mgeuler", 1);
   ros::Subscriber sub = n.subscribe<controlvehicle::ardu_imu>("imu", 1, boost::bind(sensorsCallback, _1, quat, euler,  pub_quater, pub_euler));


   ROS_INFO("Start Magdwick Conversion ... ");

   ros::spin();
   return 0;

}
