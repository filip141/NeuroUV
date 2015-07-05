#ifndef ROBOT_CONTROL_H 
#define ROBOT_CONTROL_H


#include "DualVNH5019MotorShield.h"

class RobotControl{

public:
 //Conctructor
   RobotControl(int _Min);
 
 //Error Function
   //void stopIfFault();
 //Function to drive vehicle forward
   void goStraight(int Speed);
 //Function to stop vehicle
   void stopDriving(void);
 //Turning Vehicle Around
   void turnAround(int turningPower);
 //Turning Left or Right max turning power equals 400
   void turnLeftRight(int Speed, int PowerLR);
  //Return Left wheel speed value
   int getLeftWheelSpeed(void);
  //Return Right wheel speed value
   int getRightWheelSpeed(void);
 private:
  //Shield library class
   DualVNH5019MotorShield md;
  //Class Variables Left and right wheel speed
   int minimumValue;
   int leftSpeed;
   int rightSpeed;
   
};

#endif
