

/*
Gy80lib.cpp is source file for Gy80 Inertial measurement unit Library

Gy80lib library contains whole functions to handle Gy80 imu, get
information from the sensors and calculate vehicle position.

Project is supported by Neurosoft Co

Created by Filip Bachura, September 12, 2015.

*/



// -----------------------------Includes -------------------------------------------------------------------


#include "Gy80lib.h"
#include <Arduino.h>


// -----------------------------Methods -------------------------------------------------------------------

Gy80lib::Gy80lib(){
	Wire.begin();
	AccelScale = AFS_2G;
	MagRes = 0.73;
	GyroScale = GFS_250DPS;
	Magtilt[0] = 0;
	Magtilt[1] = 0;
	Magtilt[2] = 0;

	fi = 0;
	scaleFactor = 1;


}


// ----------------------------------------------- I2C Commands  --------------------------------------------

// Read byte from I2C bus

uint8_t Gy80lib::readByte(uint8_t address, uint8_t subAddress)
{
	uint8_t data; // `data` will store the register data
	Wire.beginTransmission(address);         // Initialize the Tx buffer
	Wire.write(subAddress);	                 // Put slave register address in Tx buffer
	Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
	Wire.requestFrom(address, (uint8_t) 1);  // Read one byte from slave register address
	data = Wire.read();                      // Fill Rx buffer with result
	return data;                             // Return data read from slave register
}

// Read few bytes from I2C bus

void Gy80lib::readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{
	Wire.beginTransmission(address);   // Initialize the Tx buffer
	Wire.write(subAddress);            // Put slave register address in Tx buffer
	Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
	uint8_t i = 0;
      Wire.requestFrom(address, count);  // Read bytes from slave register address
	while (Wire.available()) {
      dest[i++] = Wire.read(); }         // Put read results in the Rx buffer
}


// Send byte to device

void Gy80lib::writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
	Wire.beginTransmission(address);  // Initialize the Tx buffer
	Wire.write(subAddress);           // Put slave register address in Tx buffer
	Wire.write(data);                 // Put data in Tx buffer
	Wire.endTransmission();           // Send the Tx buffer
}


//----------------------------------------------Math functions---------------------------------------------------

// 2x2 matrix det

double Gy80lib::det(double matrix[2][2])
{

	return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];


}


// 3x3 matrix det

double Gy80lib::det(double a[3][3])
{

	return a[0][0]*a[1][1]*a[2][2] + a[0][1]*a[1][2]*a[2][0] + a[0][2]*a[1][0]*a[2][1] - a[0][0]*a[1][2]*a[2][1] - a[0][1]*a[1][0]*a[2][2] - a[0][2]*a[1][1]*a[2][0];

}

// Multiply by scalar

void Gy80lib::scalarMultiply(double matrix[2][2], double scalar)
{
	matrix[0][0] = scalar * matrix[0][0];
	matrix[0][1] = scalar * matrix[0][1];
	matrix[1][0] = scalar * matrix[1][0];
	matrix[1][1] = scalar * matrix[1][1];

}


void Gy80lib::scalarMultiply(double matrix[3][3], double scalar)
{
	matrix[0][0] = scalar * matrix[0][0];
	matrix[0][1] = scalar * matrix[0][1];
	matrix[0][2] = scalar * matrix[0][2];
	matrix[1][0] = scalar * matrix[1][0];
	matrix[1][1] = scalar * matrix[1][1];
	matrix[1][2] = scalar * matrix[1][2];
	matrix[2][0] = scalar * matrix[2][0];
	matrix[2][1] = scalar * matrix[2][1];
	matrix[2][2] = scalar * matrix[2][2];


}


// Inverse Matrix 2x2

void Gy80lib::inv(double matrix[2][2])
{
	double temp[2][2];
	int i,j;

	temp[0][0] = matrix[1][1];
	temp[0][1] = -matrix[0][1];
	temp[1][0] = -matrix[1][0];
	temp[1][1] = matrix[0][0];

	scalarMultiply(temp, 1/det(matrix));

	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			matrix[i][j] = temp[i][j];
		}
	}

}

// Init array
void Gy80lib::initArr(double array[2][2], double a, double b, double c, double d){
	array[0][0] = a;
	array[0][1] = b;
	array[1][0] = c;
	array[1][1] = d;
}


// Multiply Matrix with vector
void Gy80lib::multiplyWithVector(double array[3][3], double vec[3], double buff[3]){

	buff[0] = array[0][0]*vec[0] + array[0][1]*vec[1] + array[0][2]*vec[2];
	buff[1] = array[1][0]*vec[0] + array[1][1]*vec[1] + array[1][2]*vec[2];
	buff[2] = array[2][0]*vec[0] + array[2][1]*vec[1] + array[2][2]*vec[2];


}


// Inverse Matrix 3x3

void Gy80lib::inv(double a[3][3])
{
	double temp[2][2];
	double mat[3][3];
	int i,j;

	initArr(temp, a[1][1], a[1][2], a[2][1], a[2][2]);
	mat[0][0] = det(temp);
	initArr(temp, a[0][2], a[0][1], a[2][2], a[2][1]);
	mat[0][1] = det(temp);
	initArr(temp, a[0][1], a[0][2], a[1][1], a[1][2]);
	mat[0][2] = det(temp);
	initArr(temp, a[1][2], a[1][0], a[2][2], a[2][0]);
	mat[1][0] = det(temp);
	initArr(temp, a[0][0], a[0][2], a[2][0], a[2][2]);
	mat[1][1] = det(temp);
	initArr(temp, a[0][2], a[0][0], a[1][2], a[1][0]);
	mat[1][2] = det(temp);
	initArr(temp, a[1][0], a[1][1], a[2][0], a[2][1]);
	mat[2][0] = det(temp);
	initArr(temp, a[0][1], a[0][0], a[2][1], a[2][0]);
	mat[2][1] = det(temp);
	initArr(temp, a[0][0], a[0][1], a[1][0], a[1][1]);
	mat[2][2] = det(temp);

	scalarMultiply(mat, 1/det(a));

	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			a[i][j] = mat[i][j];
		}
	}

}




// ----------------------------------------------- Device Calibration  --------------------------------------------

/*
 Magnetometer Callibration , function should be used only in case
 Soft - metal disortion and tilt effect compensation
 In good environment it's not necessary. This function should be integrated with circular
 movement of your device .


*/

void Gy80lib::HMC5883LCal(){


	int16_t HMC5883LOldBuff[3];
	int16_t HMC5883LBuff[3];
	float maxes[3][3] =  {{ -2000, -2000, -2000 }, { -2000, -2000, -2000 }, { -2000, -2000, -2000 }} ;
	float mins[3][3] = {{ 2000, 2000, 2000 }, { 2000, 2000, 2000 }, { 2000, 2000, 2000 }} ;
	double vec[3] = { 1, 1, 1 };
	double A;
	double B;
	uint16_t counter = 0;
	float sumx = 0;
	float sumy = 0;
	float sumz = 0;
	double buff[3];
	double matrix[3][3];
	int i;
//	Serial.println("Prepare to calibration");
//	delay(5000);
 	for(i = 0; i < 3000; i++){
 		  if(readByte(HMC5883L_ADDRESS, HMC5883L_STATUS) & 0x01) {
 			  readMagData(HMC5883LBuff);
 			  if(counter < 300){
 				 sumx = sumx + pow((HMC5883LBuff[0] - HMC5883LOldBuff[0]),2);
 				 sumy = sumy + pow((HMC5883LBuff[1] - HMC5883LOldBuff[1]),2);
 				 sumz = sumz + pow((HMC5883LBuff[2] - HMC5883LOldBuff[2]),2);
 				 counter++;
 			  }
 			  else
 			  {
				  if(HMC5883LBuff[0] > maxes[0][0] && pow((HMC5883LBuff[0] - HMC5883LOldBuff[0]),2) < (sumx/65) && pow((HMC5883LBuff[1] - HMC5883LOldBuff[1]),2) < (sumy/65)){
					 maxes[0][0] = HMC5883LBuff[0];
					 maxes[0][1] = HMC5883LBuff[1];
					 maxes[0][2] = HMC5883LBuff[2];
				  }
				  else if(HMC5883LBuff[0] < mins[0][0] && pow((HMC5883LBuff[0] - HMC5883LOldBuff[0]),2) < (sumx/65) && pow((HMC5883LBuff[1] - HMC5883LOldBuff[1]),2) < (sumy/65)){
					 mins[0][0] = HMC5883LBuff[0];
					 mins[0][1] = HMC5883LBuff[1];
					 mins[0][2] = HMC5883LBuff[2];
				  }
				  if(HMC5883LBuff[1] > maxes[1][1] && pow((HMC5883LBuff[1] - HMC5883LOldBuff[1]),2) < (sumy/65) && pow((HMC5883LBuff[0] - HMC5883LOldBuff[0]),2) < (sumx/65)){
					 maxes[1][0] = HMC5883LBuff[0];
					 maxes[1][1] = HMC5883LBuff[1];
					 maxes[1][2] = HMC5883LBuff[2];
				  }
				  else if(HMC5883LBuff[1] < mins[1][1]  && pow((HMC5883LBuff[1] - HMC5883LOldBuff[1]),2) < (sumy/65) && pow((HMC5883LBuff[0] - HMC5883LOldBuff[0]),2) < (sumx/65)){
					 mins[1][0] = HMC5883LBuff[0];
					 mins[1][1] = HMC5883LBuff[1];
					 mins[1][2] = HMC5883LBuff[2];
				  }
				  if(HMC5883LBuff[2] > maxes[2][2] && pow((HMC5883LBuff[2] - HMC5883LOldBuff[2]),2) < (sumz/65)){
					 maxes[2][0] = HMC5883LBuff[0];
					 maxes[2][1] = HMC5883LBuff[1];
					 maxes[2][2] = HMC5883LBuff[2];
				  }
				  else if(HMC5883LBuff[2] < mins[2][2] && pow((HMC5883LBuff[2] - HMC5883LOldBuff[2]),2) < (sumz/65)){
					 mins[2][0] = HMC5883LBuff[0];
					 mins[2][1] = HMC5883LBuff[1];
					 mins[2][2] = HMC5883LBuff[2];
				  }

 			  }
// 			  Serial.println(String(HMC5883LBuff[0])+","+String(HMC5883LBuff[1])+","+String(HMC5883LBuff[2]));
		 	  HMC5883LOldBuff[0] = HMC5883LBuff[0];
		 	  HMC5883LOldBuff[1] = HMC5883LBuff[1];
		 	  HMC5883LOldBuff[2] = HMC5883LBuff[2];
 	    }
 		delay(10);

 	}


// 	Serial.println("Data");
// 	delay(500);
// 	Serial.println("Max X-X : " + String(maxes[0][0]));
// 	delay(500);
// 	Serial.println("Max X-Y : " + String(maxes[0][1]));
// 	delay(500);
// 	Serial.println("Max Y-X : " + String(maxes[1][0]));
// 	delay(500);
// 	Serial.println("Max Y-Y : " + String(maxes[1][1]));
// 	delay(500);
//	Serial.println("Min X-X : " + String(mins[0][0]));
//	delay(500);
// 	Serial.println("Min X-Y : " + String(mins[0][1]));
// 	delay(500);
// 	Serial.println("Min Y-X : " + String(mins[1][0]));
// 	delay(500);
// 	Serial.println("Min Y-Y : " + String(mins[1][1]));
// 	delay(500);
// 	Serial.println("Step X : " + String(sqrt(sumx)/130));
// 	delay(500);
// 	Serial.println("Step Y : " + String(sqrt(sumy)/130));
// 	delay(500);
// 	Serial.println("Step Z : " + String(sqrt(sumz)/130));
// 	delay(500);
// 	Serial.println("Counter : " + String(counter));

 	Magtilt[0] = ( maxes[0][0] + mins[0][0] ) /2;
 	Magtilt[1] = ( maxes[1][1] + mins[1][1] ) /2;
 	Magtilt[2] = ( maxes[2][2] + mins[2][2] ) /2;


 	maxes[0][0] = maxes[0][0] - Magtilt[0];
 	maxes[1][0] = maxes[1][0] - Magtilt[0];
 	maxes[0][1] = maxes[0][1] - Magtilt[1];
 	maxes[1][1] = maxes[1][1] - Magtilt[1];

 	mins[0][0] = mins[0][0] - Magtilt[0];
 	mins[1][0] = mins[1][0] - Magtilt[0];
 	mins[0][1] = mins[0][1] - Magtilt[1];
 	mins[1][1] = mins[1][1] - Magtilt[1];
//
// 	Serial.println("After tilt---------------");
// 	Serial.println(Magtilt[0]);
// 	Serial.println(Magtilt[1]);
// 	Serial.println(Magtilt[2]);
// 	Serial.println("Data : ");
// 	Serial.println(maxes[0][0]);
// 	Serial.println(maxes[0][1]);
// 	Serial.println(maxes[1][0]);
// 	Serial.println(maxes[0][1]);
//	Serial.println(mins[0][0]);
// 	Serial.println(mins[0][1]);
// 	Serial.println(mins[1][0]);
// 	Serial.println(mins[0][1]);

//
//
 	fi = atan(maxes[1][1]/maxes[0][0]);

 	matrix[0][0] = pow(maxes[0][0],2);
 	matrix[0][1] = maxes[0][0]*maxes[0][1];
 	matrix[0][2] = pow(maxes[0][1],2);
 	matrix[1][0] = pow(maxes[1][0],2);
 	matrix[1][1] = maxes[1][0]*maxes[1][1];
 	matrix[1][2] = pow(maxes[1][1],2);
 	matrix[2][0] = pow(mins[0][0],2);
 	matrix[2][1] = mins[0][0]*mins[0][1];
 	matrix[2][2] = pow(mins[0][1],2);

// 	delay(500);
// 	Serial.println("Addr 11 : " + String(matrix[0][0]));
// 	delay(500);
// 	Serial.println("Addr 12 : " + String(matrix[0][1]));
// 	delay(500);
// 	Serial.println("Addr 13 : " + String(matrix[0][2]));
// 	delay(500);
// 	Serial.println("Addr 21 : " + String(matrix[1][0]));
// 	delay(500);
// 	Serial.println("Addr 22 : " + String(matrix[1][1]));
// 	delay(500);
// 	Serial.println("Addr 23 : " + String(matrix[1][2]));
// 	delay(500);
// 	Serial.println("Addr 31 : " + String(matrix[2][0]));
// 	delay(500);
// 	Serial.println("Addr 32 : " + String(matrix[2][1]));
// 	delay(500);
// 	Serial.println("Addr 33 : " + String(matrix[2][2]));

 	inv(matrix);
 	multiplyWithVector(matrix, vec, buff);

// 	delay(500);
// 	Serial.println("Inverse 11 : " + String(matrix[0][0]*100000));
// 	delay(500);
// 	Serial.println("Inverse 12 : " + String(matrix[0][1]*100000));
// 	delay(500);
// 	Serial.println("Inverse 13 : " + String(matrix[0][2]*100000));
// 	delay(500);
// 	Serial.println("Inverse 21 : " + String(matrix[1][0]*100000));
// 	delay(500);
// 	Serial.println("Inverse 22 : " + String(matrix[1][1]*100000));
// 	delay(500);
// 	Serial.println("Inverse 23 : " + String(matrix[1][2]*100000));
// 	delay(500);
// 	Serial.println("Inverse 31 : " + String(matrix[2][0]*100000));
// 	delay(500);
// 	Serial.println("Inverse 32 : " + String(matrix[2][1]*100000));
// 	delay(500);
// 	Serial.println("Inverse 33 : " + String(matrix[2][2]*100000));
//
// 	delay(500);
// 	Serial.println("Buff 1 : " + String(buff[0]*100000));
// 	delay(500);
// 	Serial.println("Buff 2 : " + String(buff[1]*100000));
// 	delay(500);
// 	Serial.println("Buff 3 : " + String(buff[2]*100000));

 	A = sqrt(abs(pow(buff[0], -1)));
 	B = sqrt(abs(pow(buff[2], -1)));

 	scaleFactor = A/B;


// 	delay(500);
// 	Serial.println("A Axis : " + String(sqrt(abs(pow(buff[0], -1)))));
// 	delay(500);
// 	Serial.println("B Axis : " + String(sqrt(abs(pow(buff[2], -1)))));
// 	delay(500);
// 	Serial.println("Scale Factor : " + String(scaleFactor));
// 	delay(500);
// 	Serial.println("Fi : " + String(fi));


}


// Gyro calibrate
void Gy80lib::L3G4200DCal(){

	int16_t L3G4200DBuff[3];
	float L3G4200DRes[3];
	int i;

 	for(i = 0; i < 500; i++){
 	    if(readByte(L3G4200D_ADDRESS, L3G4200D_STATUS_REG) & 0x08) {
 	    	readGyroData(L3G4200DBuff);
 	    	L3G4200DReadData(L3G4200DBuff, L3G4200DRes);
 	    	GyroBias[0] += L3G4200DRes[0];
 	    	GyroBias[1] += L3G4200DRes[1];
 	    	GyroBias[2] += L3G4200DRes[2];
 	    }
 	}

 	GyroBias[0] = GyroBias[0] / 100.0f;
 	GyroBias[1] = GyroBias[1] / 100.0f;
 	GyroBias[2] = GyroBias[2] / 100.0f;

}



// Accelerometer Calibration

void Gy80lib::ADXL345Cal(){

	 uint8_t data[6] = {0, 0, 0, 0, 0, 0};
	 int abias[3] = {0, 0, 0};
	 int16_t accel_bias[3] = {0, 0, 0};
	 int samples, ii;

	// Reset device

	writeByte(ADXL345_ADDRESS, ADXL345_POWER_CTL, 0x00); // Put device in standby mode and clear sleep bit 2
	delay(10);
	writeByte(ADXL345_ADDRESS, ADXL345_POWER_CTL, 0x08); // Put device in normal mode
	delay(10);

	// Justify bit select justified MSB mode
	writeByte(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, 0x04);
	uint16_t  accelsensitivity = 256;  // = 256 LSB/g at 2g full scale

	// Select normal power operation, and 100 Hz ODR and 50 Hz bandwidth
	writeByte(ADXL345_ADDRESS, ADXL345_BW_RATE, 0xAA);
	delay(10);

	writeByte(ADXL345_ADDRESS, ADXL345_FIFO_CTL, 0x6F);    // Enable FIFO stream mode | collect 32 FIFO samples
	delay(1000);  // delay 1000 milliseconds to collect FIFO samples

	samples = readByte(ADXL345_ADDRESS, ADXL345_FIFO_STATUS);

	for(ii = 0; ii < samples ; ii++) {
		readBytes(ADXL345_ADDRESS, ADXL345_DATAX0, 6, &data[0]);
		accel_bias[0] += (((int16_t)data[1] << 8) | data[0]) >> 6;
		accel_bias[1] += (((int16_t)data[3] << 8) | data[2]) >> 6;
		accel_bias[2] += (((int16_t)data[5] << 8) | data[4]) >> 6;
	}

	accel_bias[0] /= samples; // average the data
	accel_bias[1] /= samples;
	accel_bias[2] /= samples;


	// Remove gravity from z-axis accelerometer bias value
	if(accel_bias[2] > 0) {
	  accel_bias[2] -= accelsensitivity;
	}
	else {
	  accel_bias[2] += accelsensitivity;
	}

	abias[0] = (int)((-accel_bias[0]/4) & 0xFF); // offset register are 8 bit 2s-complement, so have sensitivity 1/4 of 2g full scale
	abias[1] = (int)((-accel_bias[1]/4) & 0xFF);
	abias[2] = (int)((-accel_bias[2]/4) & 0xFF);

	writeByte(ADXL345_ADDRESS, ADXL345_OFSX, abias[0]);
	writeByte(ADXL345_ADDRESS, ADXL345_OFSY, abias[1]);
	writeByte(ADXL345_ADDRESS, ADXL345_OFSZ, abias[2]);

}


// ----------------------------------------------- Device Initialization  --------------------------------------------

// Magnetometer Initialization

void Gy80lib::HMC5883LInit(){

	// Set magnetomer ODR; default is 15 Hz
	writeByte(HMC5883L_ADDRESS, HMC5883L_CONFIG_A, MRT_75 << 2);
	writeByte(HMC5883L_ADDRESS, HMC5883L_CONFIG_B, 0x00);  // set max resolution
	writeByte(HMC5883L_ADDRESS, HMC5883L_MODE, 0x80 );     // enable continuous data mode

}



// Gyroscope Initialization

void Gy80lib::L3G4200DInit(){

	 // Set gyro ODR to 100 Hz and Bandwidth to 25 Hz, enable normal mode
	  writeByte(L3G4200D_ADDRESS, L3G4200D_CTRL_REG1, GRTBW_200_50 << 4 | 0x0F);
	  writeByte(L3G4200D_ADDRESS, L3G4200D_CTRL_REG3, 0x08);        // Push/pull, active high interrupt, enable data ready interrupt
	  writeByte(L3G4200D_ADDRESS, L3G4200D_CTRL_REG4, GyroScale << 4); // set gyro full scale
	  writeByte(L3G4200D_ADDRESS, L3G4200D_CTRL_REG5, 0x00);

}



// Accelerometer calibration

void Gy80lib::ADXL345Init(){

	 // wake up device
	writeByte(ADXL345_ADDRESS, ADXL345_POWER_CTL, 0x00); // Put device in standby mode and clear sleep bit 2
	delay(100);  // Let device settle down
	writeByte(ADXL345_ADDRESS, ADXL345_POWER_CTL, 0x08); // Put device in normal mode

	 // Set accelerometer configuration; interrupt active high, left justify MSB
	writeByte(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, 0x04 | AFS_2G); // Set full scale range for the accelerometer

	// Choose ODR and bandwidth
	writeByte(ADXL345_ADDRESS, ADXL345_BW_RATE, ARTBW_200_100); // Select normal power operation, and ODR and bandwidth

	writeByte(ADXL345_ADDRESS, ADXL345_INT_ENABLE, 0x80);  // Enable data ready interrupt
	writeByte(ADXL345_ADDRESS, ADXL345_INT_MAP, 0x00);     // Enable data ready interrupt on INT_1

	writeByte(ADXL345_ADDRESS, ADXL345_FIFO_CTL, 0x00);    // Bypass FIFO

}


// -----------------------------------------------Read Data From Device  --------------------------------------------



// Read Accelerometer data from DATA regs

void Gy80lib::readAccelData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  readBytes(ADXL345_ADDRESS, ADXL345_DATAX0, 6, &rawData[0]);  // Read the six raw data registers into data array
  destination[0] = ((int16_t)rawData[1] << 8) | rawData[0];  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[3] << 8) | rawData[2];
  destination[2] = ((int16_t)rawData[5] << 8) | rawData[4];
}

// Read Gyroscope data from L3G4200D_OUT_X_L register


void Gy80lib::readGyroData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z gyro register data stored here
  readBytes(L3G4200D_ADDRESS, L3G4200D_OUT_X_L | 0x80, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int16_t)rawData[1] << 8) | rawData[0];  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[3] << 8) | rawData[1];
  destination[2] = ((int16_t)rawData[5] << 8) | rawData[4];
}

// Read Magnetometer data from HMC5883L_OUT_X_H register

void Gy80lib::readMagData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z gyro register data stored here
  readBytes(HMC5883L_ADDRESS, HMC5883L_OUT_X_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1];       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[4] << 8) | rawData[5];
  destination[2] = ((int16_t)rawData[2] << 8) | rawData[3];
}


void Gy80lib::ADXL345ReadData(int16_t * accelData, float * buffer){
	ADXL345getRes();
	buffer[0] = (float)accelData[0]*AccelRes;
	buffer[1] = (float)accelData[1]*AccelRes;
	buffer[2] = (float)accelData[2]*AccelRes;
}


void Gy80lib::L3G4200DReadData(int16_t * gyroData, float * buffer){
	L3G4200DgetRes();
	buffer[0] = (float)gyroData[0]*GyroRes - GyroBias[0];
	buffer[1] = (float)gyroData[1]*GyroRes - GyroBias[1];
	buffer[2] = (float)gyroData[2]*GyroRes - GyroBias[2];
}


void Gy80lib::HMC5883LReadData(int16_t * magData, float * buffer){

	float x;
	float y;

	float newx;
	float newy;

 	x = (float)magData[0] - Magtilt[0];
 	y = (float)magData[1] - Magtilt[1];

 	newx = x*cos(fi) + y*sin(fi);
 	newy = -x*sin(fi) + y*cos(fi);

 	newx = newx*scaleFactor;

	buffer[0] = newx*MagRes;
	buffer[1] = newy*MagRes;
	buffer[2] = ((float)magData[2] - Magtilt[2]) *MagRes ;

//	Serial.println(String(newx)+","+String(newy)+","+String((float)magData[2] - Magtilt[2]));
}


//------------------------------------------------Magdwick Algoritm----------------------------------------------

void Gy80lib::sensorsCallback(Buffers buff)
{

	//Magdwick compensate and change to quaterions
	MadgwickAHRSupdate(buff.L3G4200DRes[0]*PI/180.0f , buff.L3G4200DRes[1]*PI/180.0f , buff.L3G4200DRes[2]*PI/180.0f , buff.ADXL345Res[0], buff.ADXL345Res[1], buff.ADXL345Res[2], buff.HMC5883LRes[0], buff.HMC5883LRes[1], buff.HMC5883LRes[2]);

	//Set Quaternion message values
	quat.x = q0;
	quat.y = q1;
	quat.z = q2;
	quat.w = q3;

	euler.x = atan2((2*q1*q2 - 2*q0*q3), (2*q0*q0 + 2*q1*q1 - 1) ) * (180/PI);
	euler.y = -asin(2*q1*q3 + 2*q0*q2) * (180/PI);
	euler.z = atan2((2*q2*q3 - 2*q0*q1), (2*q0*q0 + 2*q3*q3 -1) ) * (180/PI);


}
// -----------------------------------------------Check device Presence --------------------------------------------

// Check Accelerometer absence
uint8_t Gy80lib::ADXL345Prs(){

	uint8_t buffer;
	buffer = readByte(ADXL345_ADDRESS, WHO_AM_I_ADXL345);
	if( buffer == 0xE5 )
		return true;
	else{
		return false;
	}

}


// Check Gyroscope presence
uint8_t Gy80lib::L3G4200DPrs(){

	uint8_t buffer;
	buffer = readByte(L3G4200D_ADDRESS, WHO_AM_I_L3G4200D);
	if( buffer == 0xD3 )
		return true;
	else{
		return false;
	}

}


// Check Gyroscope presence
uint8_t Gy80lib::HMC5883LPrs(){

	uint8_t buffer[3];
	buffer[0] = readByte(HMC5883L_ADDRESS, HMC5883L_IDA);
	buffer[1] = readByte(HMC5883L_ADDRESS, HMC5883L_IDB);
	buffer[2] = readByte(HMC5883L_ADDRESS, HMC5883L_IDC);
	if( buffer[0] == 0x48 &  buffer[1] == 0x34 & buffer[2] == 0x33)
		return true;
	else{
		return false;
	}

}

uint8_t Gy80lib::isOnline(){
	if(HMC5883LPrs() & L3G4200DPrs() & ADXL345Prs()){
		return true;
	}
	else{
		return false;
	}
}

// ----------------------------------------------- Device Test  --------------------------------------------

byte Gy80lib::HMC5883LTest(){

	int16_t selfTest[3] = {0, 0, 0};
	//  Perform self-test and calculate temperature compensation bias
	writeByte(HMC5883L_ADDRESS, HMC5883L_CONFIG_A, 0x71);   // set 8-average, 15 Hz default, positive self-test measurement
	writeByte(HMC5883L_ADDRESS, HMC5883L_CONFIG_B, 0xA0);   // set gain (bits[7:5]) to 5
	writeByte(HMC5883L_ADDRESS, HMC5883L_MODE, 0x80 );      // enable continuous data mode
	delay(150); // wait 150 ms

	uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};                        // x/y/z gyro register data stored here
	readBytes(HMC5883L_ADDRESS, HMC5883L_OUT_X_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
	selfTest[0] = ((int16_t)rawData[0] << 8) | rawData[1];          // Turn the MSB and LSB into a signed 16-bit value
	selfTest[1] = ((int16_t)rawData[4] << 8) | rawData[5];
	selfTest[2] = ((int16_t)rawData[2] << 8) | rawData[3];
	writeByte(HMC5883L_ADDRESS, HMC5883L_CONFIG_A, 0x00);   // exit self test

	if(selfTest[0] < 575 && selfTest[0] > 243 && selfTest[1] < 575 && selfTest[1] > 243 && selfTest[2] < 575 && selfTest[2] > 243)
	{
		return true;
	}
	else
	{
		return false;
	}

}




// -----------------------------------------------This section describe get Resolution method for all sensors --------------------------------------------

void Gy80lib::ADXL345getRes() {
  switch (AccelScale)
  {
 	// Possible accelerometer scales (and their register bit settings) are:
	// 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
    case AFS_2G:
    	  AccelRes = 2.0/(512.*64.);   // 10-bit 2s-complement
          break;
    case AFS_4G:
    	  AccelRes = 4.0/(1024.*32.);  // 11-bit 2s-complement
          break;
    case AFS_8G:
    	  AccelRes = 8.0/(2048.*16.);  // 12-bit 2s-complement
          break;
    case AFS_16G:
    	  AccelRes = 16.0/(4096.*8.);  // 13-bit 2s-complement
          break;
  }
}


void Gy80lib::L3G4200DgetRes() {
  switch (GyroScale)
  {
 	// Possible gyro scales (and their register bit settings) are:
	// 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
    case GFS_250DPS:
    	  GyroRes = 250.0/32768.0;
          break;
    case GFS_500DPS:
    	  GyroRes = 500.0/32768.0;
          break;
    case GFS_1000DPS:
    	  GyroRes = 1000.0/32768.0;
          break;
    case GFS_2000DPS:
    	  GyroRes = 2000.0/32768.0;
          break;
  }
}
