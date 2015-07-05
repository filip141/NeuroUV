#include <DualVNH5019MotorShield.h>
#include <Robot_motors.h>



void setup() {
  // put your setup code here, to run once:
  RobotControl rb(220);
  rb.goStraight(400);
  delay(500);
  rb.stopDriving();

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
