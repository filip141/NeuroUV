
#include <ros.h>
#include <Wire.h>

//Sensor Libraries
#include <HMC5883L.h>
#include <L3G4200D.h>
#include <ADXL345.h>
#include <BMP085.h>
#include <Robot_motors.h>


// Neuro Lib
#include <neurouv.h>


void setup()
{ 
//  Serial1.begin(9600);
//  Serial.begin(9600);
//  
//  //Serial1.println(F("Arduino in debugging mode"));
//  //Serial1.println("Free RAM Space : " + String(freeRam()) + " bytes");
//  
//  //Initialize trigger pins and pw pins and wait for calibration
//  pinMode(12, OUTPUT);
//  pinMode(13, OUTPUT);
//  pinMode(16, OUTPUT);
//  pinMode(17, OUTPUT);
//  pinMode(pwPin, INPUT);
//  pinMode(pwPin2, INPUT);
//  pinMode(pwPin3, INPUT);
//  pinMode(pwPin4, INPUT);
//     
//  digitalWrite(12, LOW);
//  digitalWrite(13, LOW);
//  digitalWrite(16, LOW);
//  digitalWrite(17, LOW);
//  delay(200);
//  
//  //Begin sensor objects
//  Wire.begin();  
//  accelerometer.begin();
//  compass.begin();
//   
//  // Setup timer
//  setupTimer();
//  
//  //Setting sensor objects
//  gyro.enableDefault();
//  gyro.writeReg(L3G4200D_CTRL_REG4, L3G4200D_2000DPS);
//  accelerometer.setRange(ADXL345_RANGE_2G);
//  compass.setRange(HMC5883L_RANGE_1_3GA);
//  compass.setMeasurementMode(HMC5883L_CONTINOUS);
//  compass.setDataRate(HMC5883L_DATARATE_30HZ);
//  compass.setSamples(HMC5883L_SAMPLES_8);
//  compass.setOffset(0, 0); 
//  
////  //Ros node initialization
////  nh.initNode();
////  
////  //Ros settings
////  nh.advertise(pub_imu);
////  nh.subscribe(rosTopic);
////  nh.advertise(pub_tem); 
////  nh.advertise(pub_son); 
////  nh.getHardware()->setBaud(57600);
//  
}


void loop() {
//
////nh.spinOnce();
//
//  Serial.println(son_msg.sonar3) ;
//  if(sensorOneShutdown){
//    Serial.println("Sensor one broken ! ") ;
//  }
//  
//  if(sensorTwoShutdown){
//    Serial.println("Sensor two broken ! ") ;
//  }
//  
//  if(sensorThreeShutdown){
//    Serial.println("Sensor three broken ! ") ;
//  }
//  
//  if(sensorFourShutdown){
//    Serial.println("Sensor four broken ! ") ;
//  }
//
//  if (millis() >= rangeMillis) {  
//        
//          rangeMillis = millis() + time_step;
//          imu_msg.header.frame_id =  "imu";
//          sensorsVelocity();
//          //pub_imu.publish(&imu_msg);   
//          //nh.spinOnce(); 
//  }
//
//
//  if (millis() >= rtemMillis) {
// 
//          rtemMillis = millis() + temstep;
//          tempsensorsVelocity();
//          //pub_tem.publish(&tem_msg);
//          //nh.spinOnce();
//           
//  }
//
//
//  if (millis() >= rsonMillis) {
// 
//          rsonMillis = millis() + sonstep;
//          //nh.spinOnce();
//          sonarsensorsVelocity();
//          //if(!periodnum) 
//          //pub_son.publish(&son_msg);
//          //nh.spinOnce();
//    
//           
//  }
//
//  // Delays protection
//  saftyCounter = saftyCounter + 1;
//  
////#ifdef DEBUG_DATA
////#ifndef DEBUG_Serial
////
////char aaa[10];
////itoa(freeRam(), aaa, 10);
////nh.loginfo(F("Free RAM space : "));
////nh.loginfo(aaa);
////
////#endif
////#endif
//
////delay(2);

}

