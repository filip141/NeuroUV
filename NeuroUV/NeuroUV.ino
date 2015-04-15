#include <Robot_motors.h>
#include <ros.h>
#include <controlvehicle/joy_control_msg.h>

DualVNH5019MotorShield md;
RobotControl rb(220,md);
ros::NodeHandle  nh;

void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs){
  
    int var = drivingArgs.sequence;
    int speed = 4*drivingArgs.speed;
    int PowerLR = 4*drivingArgs.powerLR;
    switch (var) {
      case 1:
        rb.stopDriving();
        break;
      case 2:
        rb.goStreight(speed);
        break;
      case 3:
        rb.turnAround(PowerLR);
        break;
      case 4:
        rb.turnLeftRight(speed, PowerLR);
        break;
      default: 
        break;
  }
}


ros::Subscriber<controlvehicle::joy_control_msg> rosTopic("joyvehicle", &DrivingHandle );

void setup() {
  nh.initNode();
  md.init();
  nh.subscribe(rosTopic); 
}

// the loop routine runs over and over again forever:
void loop() {
  nh.loginfo("message");
  nh.spinOnce();
  delay(1);
}
