#include "Robot_motors.h"

//#define DIAGCON

//Constructor accept minimal value of speed when wheels still moving 
//it depends on frictions and could be usefull to keep your tires in good condition
RobotControl::RobotControl(int _Min){
   md.init();
   leftSpeed = 0;
   rightSpeed = 0;
   minimumValue = _Min;
}

//Error Function if motors fault it sends error message via 
//Serial interface.

#ifdef DIAGCON
void RobotControl::stopIfFault()
{
	
  if (md.getM1Fault())
  {
    while(1);
  }
  if (md.getM2Fault())
  {
    while(1);
  }
}
#endif

//Function to drive vehicle forward. It accepts values between
//400 and - 400 correspond to forward and backward move 
int RobotControl::goStraight(int Speed)
{
  if(leftSpeed == rightSpeed){
    if(leftSpeed < Speed){
      for(leftSpeed; leftSpeed <= Speed; ++leftSpeed){
        rightSpeed = leftSpeed;
        md.setSpeeds(leftSpeed,rightSpeed);
	#ifdef DIAGCON
        stopIfFault();
	#endif
      }
      leftSpeed--;
    }
    else{
      for(leftSpeed; leftSpeed >= Speed; leftSpeed--){
        rightSpeed = leftSpeed;
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
       }
       leftSpeed++;
   }
  }
  else{
     if(leftSpeed < rightSpeed){
       for(leftSpeed; leftSpeed <= rightSpeed; leftSpeed++){
           md.setSpeeds(leftSpeed,rightSpeed);
       	   #ifdef DIAGCON
           stopIfFault();
	   #endif
       }
     leftSpeed--;
     goStraight(Speed);
     }
     else{
         for(rightSpeed; rightSpeed <= leftSpeed; rightSpeed++){
            md.setSpeeds(leftSpeed,rightSpeed);
            #ifdef DIAGCON
            stopIfFault();
	    #endif
         }
     rightSpeed--;
     goStraight(Speed);
     }
   }
}


//Function to stop vehicle
void RobotControl::stopDriving(void)
{
  //left wheel speed and right speed below zero
  if(leftSpeed > 0 && rightSpeed > 0 )
  {
    while(leftSpeed !=0 || rightSpeed != 0)
    {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(leftSpeed !=0)
        {
        leftSpeed--;
        }     
        if(rightSpeed !=0)
        {
        rightSpeed--;
        }  
    }
  }
  //left wheel speed below zero
  else if(leftSpeed >= 0 && rightSpeed <= 0)
  {
    while(leftSpeed !=0 || rightSpeed != 0)
    {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(leftSpeed !=0)
        {
        leftSpeed--;
        }     
        if(rightSpeed !=0)
        {
        rightSpeed++;
        }  
    }
  }   
  //right wheel speed below zero
  else if (leftSpeed <= 0 && rightSpeed >=0)
  {
    while(leftSpeed !=0 || rightSpeed != 0)
    {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(leftSpeed !=0)
        {
        leftSpeed++;
        }     
        if(rightSpeed !=0)
        {
        rightSpeed--;
        }  
    }
  }
  //left wheel speed and right speed over zero
  else{
    
    while(leftSpeed !=0 || rightSpeed != 0)
    {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(leftSpeed !=0)
        {
        leftSpeed++;
        }     
        if(rightSpeed !=0)
        {
        rightSpeed++;
        }  
    }
  }
}

//Turning Around left or right. Before calling this function vehicle speed vector should be 
//equal zero. In other case vehicle stops and start turning around . To turn left/right in motion
//you can use TurnLeftRight function
void RobotControl::turnAround(int turningPower){
  stopDriving();
  //Turning left
  if(turningPower > 0){
    for (leftSpeed; leftSpeed <= turningPower; leftSpeed++)
    {
      md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
      rightSpeed--;
    }
  }
  //Turning Right
  else{
    for (leftSpeed; leftSpeed >= turningPower; leftSpeed--)
    {
      md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
      rightSpeed++;
    }
  } 
}

//Turning Left or Right max turning power equals 400 
void RobotControl::turnLeftRight(int Speed, int PowerLR)
{
  int BreakPWR;
  //Go forward and left turn
  if(Speed > 0 && PowerLR > 0)
  {
    if(Speed >= rightSpeed){
      BreakPWR = 400 - PowerLR;
      if(BreakPWR < minimumValue)
      {
        BreakPWR = minimumValue;
      }
      while(leftSpeed != BreakPWR || rightSpeed != Speed)
      {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(leftSpeed !=BreakPWR)
        {
          if(leftSpeed < BreakPWR)
          {        
            leftSpeed++;
          }
          else{
            leftSpeed--;
          }
        
        }     
        if(rightSpeed != Speed)
        {
          if(rightSpeed < Speed)
          {        
            rightSpeed++;
          }
          else{
            rightSpeed--;
          }
          
        }  
      }
    }
  }
  //Go forward and right turn
  else if(Speed > 0 && PowerLR < 0)
  {
    if(Speed >= leftSpeed){
      BreakPWR = 400 + PowerLR;
      if(BreakPWR < minimumValue)
      {
        BreakPWR = minimumValue;
      }
      while(rightSpeed != BreakPWR || leftSpeed != Speed)
      {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(rightSpeed !=BreakPWR)
        {
          if(rightSpeed < BreakPWR)
          {        
            rightSpeed++;
          }
          else{
            rightSpeed--;
          }
        }     
        if(leftSpeed !=Speed)
        {
          if(leftSpeed < Speed)
          {        
            leftSpeed++;
          }
          else{
            leftSpeed--;
          }
        }
      }
    }
  }
  //Go backward and left turn
  else if(Speed < 0 && PowerLR < 0)
  {
    if(Speed <= leftSpeed){
      BreakPWR = -400 - PowerLR;
      if(BreakPWR > -minimumValue)
      {
        BreakPWR = -minimumValue;
      }
      while(rightSpeed != BreakPWR || leftSpeed != Speed)
      {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(rightSpeed != BreakPWR)
        {
          if(rightSpeed < BreakPWR)
          {        
            rightSpeed++;
          }
          else{
            rightSpeed--;
          }
        }     
        if(leftSpeed != Speed)
        {
          if(leftSpeed < Speed)
          {        
            leftSpeed++;
          }
          else{
            leftSpeed--;
          }
        }
      }
    }
  }
  //Go backward and right turn
  else if(Speed < 0 && PowerLR > 0)
  {
    if(Speed <= rightSpeed){
      BreakPWR = 400 - PowerLR;
      if(BreakPWR < minimumValue)
      {
        BreakPWR = -minimumValue;
      }
      while(leftSpeed != BreakPWR || rightSpeed != Speed)
      {
        md.setSpeeds(leftSpeed,rightSpeed);
        #ifdef DIAGCON
        stopIfFault();
	#endif
        if(leftSpeed != BreakPWR)
        {
          if(leftSpeed < BreakPWR)
          {        
            leftSpeed++;
          }
          else{
            leftSpeed--;
          }
        }     
        if(rightSpeed != Speed)
        {
          if(rightSpeed < Speed)
          {        
            rightSpeed++;
          }
          else{
            rightSpeed--;
          }
        }
      }      
    }         
  }
}
//Return Left wheel speed value
int RobotControl::getLeftWheelSpeed(void)
{
  return leftSpeed;
}
//Return Right wheel speed value
int RobotControl::getRightWheelSpeed(void)
{
  return rightSpeed;
}


