/*
Neurouv.c is source file for Neuro Unmanned Vehicle driver 

NeuroUv library contains whole functions to control vehicle, get 
information from the sensors and send it to Robotic Operating System.

Project is supported by Neurosoft Co

*/

#include <Arduino.h>

#include "neurouv.h"

namespace NeuroSpace
 {
 	/* Object are build here because using Arduino IDE
 	 * we can't send argument to class friend function
 	 * like class object
 	 */
 	NeuroUV neuroObject;
 };


// Constructor initialize variables and build ROS objects
NeuroUV::NeuroUV(){
		//Sonar variables initialization
		sonnum = 1;
		periodnum = 1;
		//Driving subscriber variables init
		pspeed = 0;
		pPowerLR = 0;
		// batery state variables init
		voltage = 0;
		sensorValue = 0;
		voltagestep = 0;
		counter = 0;
		//Pseudo Arduino timer
		rangeMillis = 0;
		rtemMillis = 0;
		rsonMillis = 0;
		rerrMillis = 0;
		rbatMillis = 0;
		// Robot control driver declaration
		rb = new RobotControl(100);
		// global safety counter initialization value
		saftyCounter  = 0;
		saftyCounterOld = 0;
		// Sensor shutdown values
		sensorOneShutdown = 0;
		sensorTwoShutdown = 0;
		sensorThreeShutdown = 0;
		sensorFourShutdown = 0;
		imuShutdown = 0;
		//Publishers initialization
		pub_imu = new ros::Publisher("imu", &imu_msg);
		pub_tem = new ros::Publisher("temperature", &tem_msg);
		pub_son = new ros::Publisher("maxsonar", &son_msg);
		pub_err = new ros::Publisher("error", &err_msg);
		pub_bat = new ros::Publisher("battery", &bat_msg);

		//ROS Subscriber initialization
		rosTopic = new ros::Subscriber<controlvehicle::joy_control_msg>( "joyvehicle", &DrivingHandle );

}

// Starts calibration and other starting procedures
void NeuroUV::begin(){

	  Serial1.begin(9600);

	  //Initialize trigger pins and pw pins and wait for calibration
	  pinMode(12, OUTPUT);
	  pinMode(13, OUTPUT);
	  pinMode(16, OUTPUT);
	  pinMode(17, OUTPUT);
	  pinMode(pwPin, INPUT);
	  pinMode(pwPin2, INPUT);
	  pinMode(pwPin3, INPUT);
	  pinMode(pwPin4, INPUT);

	  digitalWrite(12, LOW);
	  digitalWrite(13, LOW);
	  digitalWrite(16, LOW);
	  digitalWrite(17, LOW);
	  delay(200);

	  //Begin sensor objects
	  Wire.begin();
	  accelerometer.begin();
	  compass.begin();

	  // Setup timer
	  setupTimer();

	  //Setting sensor objects
	  gyro.enableDefault();
	  gyro.writeReg(L3G4200D_CTRL_REG4, L3G4200D_2000DPS);
	  accelerometer.setRange(ADXL345_RANGE_2G);
	  compass.setRange(HMC5883L_RANGE_1_3GA);
	  compass.setMeasurementMode(HMC5883L_CONTINOUS);
	  compass.setDataRate(HMC5883L_DATARATE_30HZ);
	  compass.setSamples(HMC5883L_SAMPLES_8);
	  compass.setOffset(0, 0);
}

// ROS initialization
void NeuroUV::initROS(){

	  //Ros node initialization
	  nh.initNode();

	  //Ros settings
	  nh.advertise(*pub_imu);
	  nh.subscribe(*rosTopic);
	  nh.advertise(*pub_tem);
	  nh.advertise(*pub_son);
	  nh.advertise(*pub_err);
	  nh.advertise(*pub_bat);
	  nh.getHardware()->setBaud(57600);
}

// Object main loop
void NeuroUV::ROSloop(){

	nh.spinOnce();

	if (millis() >= rangeMillis  && !imuShutdown) {

			rangeMillis = millis() + time_step;
			imu_msg.header.frame_id =  "imu";
			sensorsVelocity();
			pub_imu->publish(&imu_msg);
			nh.spinOnce();
	}

	if (millis() >= rtemMillis  && !imuShutdown) {

			rtemMillis = millis() + temstep;
			tempsensorsVelocity();
			pub_tem->publish(&tem_msg);
			nh.spinOnce();

	}
	if (millis() >= rsonMillis) {

			rsonMillis = millis() + sonstep;
			nh.spinOnce();
			sonarsensorsVelocity();
			if(!periodnum)
			  pub_son->publish(&son_msg);
			nh.spinOnce();
	}
	if (millis() >= rerrMillis) {

			rerrMillis = millis() + errstep;
			errorhandle();
	}
	if (millis() >= rbatMillis) {

			rbatMillis = millis() + batstep;
			batteryState();
			if(counter == 0){
				pub_bat->publish(&bat_msg);
				nh.spinOnce();
			}
	}
	if (millis() >= rdebMillis) {

			rdebMillis = millis() + debstep;
			UARThandle();
	}

	saftyCounter = saftyCounter + 1;

}

// Debug loop to check values without ros connection
void NeuroUV::Debugloop(){

	if (millis() >= rangeMillis && !imuShutdown) {

			rangeMillis = millis() + time_step;
			imu_msg.header.frame_id =  "imu";
			sensorsVelocity();
	}

	if (millis() >= rtemMillis  && !imuShutdown) {

			rtemMillis = millis() + temstep;
			tempsensorsVelocity();
	}
	if (millis() >= rsonMillis) {

			rsonMillis = millis() + sonstep;
			sonarsensorsVelocity();
	}
	if (millis() >= rbatMillis) {

			rbatMillis = millis() + batstep;
			batteryState();
			if(counter == 0){
				//Serial1.println("Main value");
				//Serial1.println(bat_msg.data);
			}
	}
	if (millis() >= rdebMillis) {

			rdebMillis = millis() + debstep;
			UARThandle();
	}

	saftyCounter = saftyCounter + 1;
}

// Setup timer5
void NeuroUV::setupTimer(){
  
  //Stop interrupts 
  cli();
  
  // Clear register 
  TCCR5A = 0;
  TCCR5B = 0;
  
  // Set timer compare value
  OCR5A = 25000;
  
   // turn on CTC mode
  TCCR5B |= (1 << WGM52);
  
   // Enable timer compare interrupt
  TIMSK5 |= (1 << OCIE5A);
  
  // Set initial value
  TCNT5H = 0x00;
  TCNT5L = 0x00;
  
  // Set timer presacaler
  TCCR5B |=  (1<<CS50) | (1<<CS51);
  
  // enable interrupts
  sei();
  
}

// Check ram capacity
 int NeuroUV::freeRam()
 {
   extern int __heap_start, *__brkval;
   int v;
   return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
 }

 // Function to handle debugging terminal
 void NeuroUV::UARThandle(){
	  String content = "";
	  char character;
	  char buff[20];

	  while(Serial1.available()) {
	      character = Serial1.read();
	      content.concat(character);
	  }


	  if (content != "") {
		  content.toCharArray(buff, 20);
		  if (content == "help"){
			  Serial1.println("List of commands: ");
			  Serial1.print(" - lssensor \n - enable <sensor> \n - disable <sensor> \n - show <data> \n 	-- sonar \n 	-- temperature \n 	-- pressure \n 	-- accelerometer \n 	-- magnetometer \n 	-- gyroscope");
		  }
		  else if (content == "lssensor"){
			  Serial1.println("Avalible sensors : ");
			  Serial1.println("");
			  if(!imuShutdown){
				  Serial1.println("Inertial measurement unit : ");
				  Serial1.println("Barometer BMP085");
				  Serial1.println("Magnetometer HMC5883L");
				  Serial1.println("Accelerometer ADXL345");
				  Serial1.println("Gyroscope L3G4200D");
				  Serial1.println("");
			  }
			  if(!sensorOneShutdown){
				  Serial1.println("LV-MaxSonar-EZ1 Num. 1");
			  }
			  if(!sensorTwoShutdown){
				  Serial1.println("LV-MaxSonar-EZ1 Num. 2");
			  }
			  if(!sensorThreeShutdown){
				  Serial1.println("LV-MaxSonar-EZ1 Num. 3");
			  }
			  if(!sensorFourShutdown){
				  Serial1.println("LV-MaxSonar-EZ1 Num. 4");
			  }
		  }
		  else if (strncmp(buff, "show", 4) == 0){
			  if (strstr(buff, "sonar") != NULL) {
				  Serial1.println("Last sonar values : ");
				  Serial1.println("");
				  Serial1.print("Sonar 1 : ");
				  Serial1.println(son_msg.sonar1);
				  Serial1.print("Sonar 2 : ");
				  Serial1.println(son_msg.sonar2);
				  Serial1.print("Sonar 3 : ");
				  Serial1.println(son_msg.sonar3);
				  Serial1.print("Sonar 4 : ");
				  Serial1.println(son_msg.sonar4);
			  }
			  else if (strstr(buff, "temperature") != NULL) {
				  Serial1.println("Last temperature value : ");
				  Serial1.println("");
				  Serial1.print(tem_msg.tem);;
			  }
			  else if (strstr(buff, "pressure") != NULL) {
				  Serial1.println("Last pressure value : ");
				  Serial1.println("");
				  Serial1.print(tem_msg.pressure);;
			  }
			  else if (strstr(buff, "accelerometer") != NULL) {
				  Serial1.println("Last accelerometer values : ");
				  Serial1.print("X Axis : ");
				  Serial1.println(imu_msg.accValues.x);
				  Serial1.print("Y Axis : ");
				  Serial1.println(imu_msg.accValues.y);
				  Serial1.print("Z Axis : ");
				  Serial1.println(imu_msg.accValues.z);
			  }
			  else if (strstr(buff, "magnetometer") != NULL) {
				  Serial1.println("Last magnetometer values : ");
				  Serial1.print("X Axis : ");
				  Serial1.println(imu_msg.magValues.x);
				  Serial1.print("Y Axis : ");
				  Serial1.println(imu_msg.magValues.y);
				  Serial1.print("Z Axis : ");
				  Serial1.println(imu_msg.magValues.z);
			  }
			  else if (strstr(buff, "gyroscope") != NULL) {
				  Serial1.println("Last gyroscope values : ");
				  Serial1.print("X Axis : ");
				  Serial1.println(imu_msg.gyroValues.x);
				  Serial1.print("Y Axis : ");
				  Serial1.println(imu_msg.gyroValues.y);
				  Serial1.print("Z Axis : ");
				  Serial1.println(imu_msg.gyroValues.z);
			  }
		  }
		  else if (strncmp(buff, "enable", 4) == 0){
			  if (strstr(buff, "sonar 1") != NULL) {
				  Serial1.println("Sonar Num. 1 Enabled ! ");
				  sensorOneShutdown = 0;
			  }
			  else if (strstr(buff, "sonar 2") != NULL) {
				  Serial1.println("Sonar Num. 2 Enabled ! ");
				  sensorTwoShutdown = 0;
			  }
			  else if (strstr(buff, "sonar 3") != NULL) {
				  Serial1.println("Sonar Num. 3 Enabled ! ");
				  sensorThreeShutdown = 0;
			  }
			  else if (strstr(buff, "sonar 4") != NULL) {
				  Serial1.println("Sonar Num. 4 Enabled ! ");
				  sensorFourShutdown = 0;
			  }
			  else if (strstr(buff, "imu") != NULL) {
				  Serial1.println("Imu Enabled ! ");
				  imuShutdown = 0;
			  }
		  }
		  else if (strncmp(buff, "disable", 4) == 0){
			  if (strstr(buff, "sonar 1") != NULL) {
				  Serial1.println("Sonar Num. 1 Disabled ! ");
				  sensorOneShutdown = 1;
			  }
			  else if (strstr(buff, "sonar 2") != NULL) {
				  Serial1.println("Sonar Num. 2 Disabled ! ");
				  sensorTwoShutdown = 1;
			  }
		  	  else if (strstr(buff, "sonar 3") != NULL) {
		  		  Serial1.println("Sonar Num. 3 Disabled ! ");
		  		  sensorThreeShutdown = 1;
		  	  }
		  	  else if (strstr(buff, "sonar 4") != NULL) {
		  		  Serial1.println("Sonar Num. 4 Disabled ! ");
		  		  sensorFourShutdown = 1;
		  	  }
		  	  else if (strstr(buff, "imu") != NULL) {
		  		  Serial1.println("Imu Disabled ! ");
		  		  imuShutdown = 1;
		  	  }
		  }

	  }
 }


 // Error Handling
 void NeuroUV::errorhandle(){
	 if(sensorOneShutdown){
		err_msg.data = "Sonar1 Broken";
		pub_err->publish(&err_msg);
		nh.spinOnce();
	 }
	 if(sensorTwoShutdown){
		err_msg.data = "Sonar2 Broken";
		pub_err->publish(&err_msg);
		nh.spinOnce();
	 }
	 if(sensorThreeShutdown){
		err_msg.data = "Sonar3 Broken";
		pub_err->publish(&err_msg);
		nh.spinOnce();
	 }
	 if(sensorFourShutdown){
		err_msg.data = "Sonar4 Broken";
		pub_err->publish(&err_msg);
		nh.spinOnce();
	 }
	 if(imuShutdown){
		err_msg.data = "Imu Broken";
		pub_err->publish(&err_msg);
		nh.spinOnce();
	 }
 }

 // Sort double array
 void NeuroUV::sort( double* n, int q ) {

    int a, b;
    double x;

    for( a = 1; a < q; a++ ) {
       for( b = 0; b < q - 1; b++ ) {
          if( n[b] > n[b + 1] ) {
             x = n[ b ];
             n[b] = n[b + 1];
             n[b + 1] = x;
          }
       }
    }
 }


 // Check battery state and send information to ROS
 void NeuroUV::batteryState(){
	 sensorValue = analogRead(A7);
	 voltageSet[counter] = sensorValue * (5.0 / 1023.0);
	 if(counter == 50){
		 sort( voltageSet, 51 );
		 voltage = voltageSet[25];
		 if(voltage >= 4.8){
			 voltagestep = voltage - 4.8;
			 bat_msg.data = voltagestep * (70.0/0.2);
			 bat_msg.data = bat_msg.data + 30;
		 }
		 else{
			 voltagestep = voltage - 4.4;
			 bat_msg.data = voltagestep * (30.0/0.4);
		 }
		 counter = 0;
	 }
	 else{
		 counter = counter + 1;
	 }
 }

//Fill sensor message
 void NeuroUV::sensorsVelocity(){
    //Read Accelerometer
    Vector scaledAcc = accelerometer.readScaled();
    //Read Magnetometer
    Vector mag = compass.readNormalize();
    //Read Gyroscope
    gyro.read();
   
    //Send Gyro to ROS and print on serial1
    imu_msg.gyroValues.x = gyro.g.x * dpsPerDigit;
    imu_msg.gyroValues.y = gyro.g.y * dpsPerDigit;
    imu_msg.gyroValues.z = gyro.g.z * dpsPerDigit;

   
    //Send Acc to ROS and print on serial1
    imu_msg.accValues.x = scaledAcc.XAxis;
    imu_msg.accValues.y = scaledAcc.YAxis;
    imu_msg.accValues.z = scaledAcc.ZAxis;
   
    //Send Mag to ROS and print on serial1
    imu_msg.magValues.x = mag.XAxis;
    imu_msg.magValues.y = mag.YAxis;
    imu_msg.magValues.z = mag.ZAxis;
 }

 //Fill temperature.msg
 void NeuroUV::tempsensorsVelocity(){
  
    bmp.begin();
    tem_msg.tem = bmp.readTemperature();
    tem_msg.pressure = bmp.readPressure();
 }

// //Fill sonar msg
 void NeuroUV::sonarsensorsVelocity(){
  
   if(sonnum == 1 && !sensorOneShutdown){
 
		 if(periodnum){
		   digitalWrite(12, HIGH);
		   periodnum = 0;
		 }
		 else
		 {
			son_msg.sonar1 = pulseIn(pwPin, HIGH)/58;
			digitalWrite(12, LOW);
			periodnum = 1;
			sonnum = 2 ;
		 }
    }
    if(sonnum == 1 && sensorOneShutdown){
    	 periodnum = 1;
    	 sonnum = 2 ;
     }

     if(sonnum == 2 && !sensorTwoShutdown) {
    
		 if(periodnum){
		   digitalWrite(13, HIGH);
		   periodnum = 0;
		 }
		 else
		 {
			son_msg.sonar2 = pulseIn(pwPin2, HIGH)/58;
			digitalWrite(13, LOW);
			periodnum = 1;
			sonnum = 3;
		 }
     }
     if(sonnum == 2 && sensorTwoShutdown){
 		periodnum = 1;
 		sonnum = 3;
     }

   if(sonnum == 3 && !sensorThreeShutdown){
    
		 if(periodnum){
		   digitalWrite(16, HIGH);
		   periodnum = 0;
		 }
		 else
		 {
			son_msg.sonar3 = pulseIn(pwPin3, HIGH)/58;
			digitalWrite(16, LOW);
			periodnum = 1;
			sonnum = 4;
		 }
   }
   if(sonnum == 3 && sensorThreeShutdown){
	   periodnum = 1;
	   sonnum = 4;
   }

   if(sonnum == 4 && !sensorFourShutdown){
    
		 if(periodnum){
		   digitalWrite(17, HIGH);
		   periodnum = 0;
		 }
		 else
		 {
			son_msg.sonar4 = pulseIn(pwPin4, HIGH)/58;
			digitalWrite(17, LOW);
			periodnum = 1;
			sonnum = 1;
		 }
   }

	if(sonnum == 4 && sensorFourShutdown){
		periodnum = 1;
		sonnum = 1;
	}
 }

 void NeuroUV::imuCheck(){
	 if(saftyCounter == saftyCounterOld && millis() > 2000){
		 imuShutdown = 1;
		 gyro.L3G4200DShutdown = 1;
		 accelerometer.ADXL345Shutdown = 1;
		 compass.HMC5883LShutdown = 1;
	 }
	 saftyCounterOld = saftyCounter;
 }


 // Timer5 interrupt
  ISR(TIMER5_COMPA_vect){

     cli();

     //Disable sensor One
     if(NeuroSpace::neuroObject.son_msg.sonar1 == 0 && millis() > 1000){
    	 NeuroSpace::neuroObject.sensorOneShutdown = 1;
     }

     // Disable Sensor Two
     if(NeuroSpace::neuroObject.son_msg.sonar2 == 0 && millis() > 1000){
    	 NeuroSpace::neuroObject.sensorTwoShutdown = 1;
     }

     //Disable Sensor Three
     if(NeuroSpace::neuroObject.son_msg.sonar3 == 0 && millis() > 1000){
    	 NeuroSpace::neuroObject.sensorThreeShutdown = 1;
     }

     //Disable Sensor Four
     if(NeuroSpace::neuroObject.son_msg.sonar4 == 0 && millis() > 1000){
    	 NeuroSpace::neuroObject.sensorFourShutdown = 1;
     }
     // Check imu connection
     NeuroSpace::neuroObject.imuCheck();

     sei();
   };


 // //Subscriber callback function
  void DrivingHandle( const controlvehicle::joy_control_msg& drivingArgs){

      int var = drivingArgs.sequence;
      int speed = 4*drivingArgs.speed;
      int PowerLR = 4*drivingArgs.powerLR;

      //Send Debug values
      //Serial1.println("Send information to driver board");
      //Serial1.println(speed);
      //Serial1.println(PowerLR);
      if((abs(speed-NeuroSpace::neuroObject.pspeed)>60) || (abs(PowerLR-NeuroSpace::neuroObject.pPowerLR)>60)){
        switch (var) {
          case 1:
        	NeuroSpace::neuroObject.rb->stopDriving();
            break;
          case 2:
        	NeuroSpace::neuroObject.rb->goStraight(speed);
        	NeuroSpace::neuroObject.nh.loginfo("GO!");
            break;
          case 3:
        	NeuroSpace::neuroObject.rb->turnAround(PowerLR);
            break;
          case 4:
        	NeuroSpace::neuroObject.rb->turnLeftRight(speed, PowerLR);
            break;
          default:
            break;
        }
        NeuroSpace::neuroObject.pspeed = speed ;
        NeuroSpace::neuroObject.pPowerLR = PowerLR;
    }
  }

