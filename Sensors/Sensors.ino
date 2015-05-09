#include <Wire.h>
#include <ros.h>
#include <HMC5883L.h>
#include <L3G4200D.h>
#include <ADXL345.h>
#include <BMP085.h>
#include <Robot_motors.h>
#include <avr/pgmspace.h>
#include <controlvehicle/ardu_imu.h>
#include <controlvehicle/joy_control_msg.h>
#include <controlvehicle/temperature.h>
#include <controlvehicle/Maxsonar.h>

//Settings gyro defined
#define L3G4200D_2000DPS 0x20
#define dpsPerDigit .07f
#define time_step 10
#define temstep 5000
#define sonstep 49

//Define pw pins
#define pwPin 7
#define pwPin2 4
#define pwPin3 8
#define pwPin4 2
//#define DEBUG_DATA
//#define DEBUG_Serial

ros::NodeHandle  nh;

//Messages
controlvehicle::ardu_imu imu_msg;
controlvehicle::temperature tem_msg;
controlvehicle::Maxsonar son_msg;


// Declare topic name in PROGMEM
const char imu_topic[]  PROGMEM  = { "imu" };
const char con_topic[]  PROGMEM  = { "joyvehicle" };

//Publishers
ros::Publisher pub_imu(FCAST(imu_topic), &imu_msg);
ros::Publisher pub_tem("temperature", &tem_msg);
ros::Publisher pub_son("maxsonar", &son_msg);

////////Gyroscope
L3G4200D gyro;

////Accelerometer
ADXL345 accelerometer;
//
//Magnetometer
HMC5883L compass;


//Robot control driver declaration
RobotControl rb(220);

#ifdef DEBUG_DATA

int freeRam() 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
#endif

//Subscriber callback function
void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs){
  
    int var = drivingArgs.sequence;
    int speed = 4*drivingArgs.speed;
    int PowerLR = 4*drivingArgs.powerLR;
    switch (var) {
      case 1:
        rb.stopDriving();
        break;
      case 2:
        rb.goStraight(speed);
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

//ROS Subscriber
ros::Subscriber<controlvehicle::joy_control_msg> rosTopic( FCAST(con_topic), &DrivingHandle );


//Fill sensor message
void sensorsVelocity(){
  //Read Accelerometer
   Vector scaledAcc = accelerometer.readScaled();
   //Read Magnetometer
   Vector mag = compass.readNormalize();
   //Read Gyroscope
   gyro.read();
   imu_msg.gyroValues.x = gyro.g.x * dpsPerDigit;
   imu_msg.gyroValues.y = gyro.g.y * dpsPerDigit;
   imu_msg.gyroValues.z = gyro.g.z * dpsPerDigit;
   imu_msg.accValues.x = scaledAcc.XAxis;
   imu_msg.accValues.y = scaledAcc.YAxis;
   imu_msg.accValues.z = scaledAcc.ZAxis;
   imu_msg.magValues.x = mag.XAxis;
   imu_msg.magValues.y = mag.YAxis;
   imu_msg.magValues.z = mag.ZAxis;
}

//Fill temperature.msg
void tempsensorsVelocity(){
  
   //Barometer 
   BMP085 bmp;
   bmp.begin(); 
   
   tem_msg.tem = bmp.readTemperature();
   tem_msg.pressure = bmp.readPressure();
  
}

//Sonar counter
byte sonnum = 1;
byte periodnum = 1;


//Fill sonar msg
void sonarsensorsVelocity(){
  
  if(sonnum == 1){
 
    if(periodnum){
      digitalWrite(5, HIGH);
      periodnum = 0;
    }
    else
    {
       son_msg.sonar1 = pulseIn(pwPin, HIGH)/57.874015748031496;
       digitalWrite(5, LOW);
       periodnum = 1;
       sonnum = 2 ;
    }
   } 
    if(sonnum == 2) {
    
    if(periodnum){
      digitalWrite(6, HIGH);
      periodnum = 0;
    }
    else
    {
       son_msg.sonar2 = pulseIn(pwPin2, HIGH)/57.874015748031496;
       digitalWrite(6, LOW);
       periodnum = 1;
       sonnum = 3;
    }
  }
  if(sonnum == 3){
    
    if(periodnum){
      digitalWrite(9, HIGH);
      periodnum = 0;
    }
    else
    {
       son_msg.sonar3 = pulseIn(pwPin3, HIGH)/57.874015748031496;
       digitalWrite(9, LOW);
       periodnum = 1;
       sonnum = 4;
    }
  } 
  if(sonnum == 4){
    
    if(periodnum){
      digitalWrite(3, HIGH);
      periodnum = 0;
    }
    else
    {

       son_msg.sonar4 = pulseIn(pwPin4, HIGH)/58;
       digitalWrite(3, LOW);
       periodnum = 1;
       sonnum = 1;
       

    }
  }

}



void setup()
{ 
  #ifdef DEBUG_Serial
  Serial.begin(9600);
  
  Serial.println(F("Arduino in debugging mode"));
  Serial.println("Free RAM Space : " + String(freeRam()) + " bytes");
  #endif
  
  //Initialize trigger pins and pw pins and wait for calibration
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(pwPin, INPUT);
  pinMode(pwPin2, INPUT);
  pinMode(pwPin3, INPUT);
  pinMode(pwPin4, INPUT);
     
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(3, LOW);
  delay(200);
  
  //Begin sensor objects
  Wire.begin();  
  accelerometer.begin();
  compass.begin();
   
  
  //Setting sensor objects
  gyro.enableDefault();
  gyro.writeReg(L3G4200D_CTRL_REG4, L3G4200D_2000DPS);
  accelerometer.setRange(ADXL345_RANGE_2G);
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(0, 0); 
  
  #ifndef DEBUG_Serial
  //Ros node initialization
  nh.initNode();
  
  #endif
  
  
  //Ros settings
  nh.advertise(pub_imu);
  nh.subscribe(rosTopic);
  nh.advertise(pub_tem); 
  nh.advertise(pub_son); 
  nh.getHardware()->setBaud(57600);
  
}

//Pseudo Arduino timer
long rangeMillis;
long rtemMillis;
long rsonMillis;

void loop() {

#ifndef DEBUG_Serial  
nh.spinOnce();
#endif

if (millis() >= rangeMillis) {  
        
        rangeMillis = millis() + time_step;
        imu_msg.header.frame_id =  "imu";
        sensorsVelocity();
        pub_imu.publish(&imu_msg);           
}


if (millis() >= rtemMillis) {
 
        rtemMillis = millis() + temstep;
        tempsensorsVelocity();
        pub_tem.publish(&tem_msg);
           
}


if (millis() >= rsonMillis) {
 
        rsonMillis = millis() + sonstep;
        nh.spinOnce();
        sonarsensorsVelocity();
        if(!periodnum) 
          pub_son.publish(&son_msg);
        nh.spinOnce();
    
           
}



#ifdef DEBUG_DATA
#ifndef DEBUG_Serial

char aaa[10];
itoa(freeRam(), aaa, 10);
nh.loginfo(F("Free RAM space : "));
nh.loginfo(aaa);

#endif
#endif

//delay(3);

}

