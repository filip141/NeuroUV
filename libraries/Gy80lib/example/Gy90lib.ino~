// Gy80lib

#include <Gy80lib.h>

Gy80lib imu;
int16_t ADXL345Buff[3];
int16_t L3G4200DBuff[3];
int16_t HMC5883LBuff[3];
Buffers buff;

void setup()
{
	Serial.begin(9600);

	if(imu.ADXL345Prs()){
		Serial.println("Accelerometer online !");
	}
	delay(500);
	if(imu.L3G4200DPrs()){
		Serial.println("Gyroscope online !");
	}
	delay(500);
	if(imu.HMC5883LPrs()){
		Serial.println("Magnetometer online !");
	}
	delay(500);
	if(imu.isOnline()){
		Serial.println("Congrats imu is online !");
	}
	Serial.println("Start Calibrating Accelerometer");
	imu.ADXL345Cal();
	delay(100);
	Serial.println("Accelerometer initialization");
	imu.ADXL345Init();
	delay(100);
	Serial.println("Start Calibrating Gyroscope");
	imu.L3G4200DCal();
	delay(100);
	Serial.println("Gyroscope Initialization");
	imu.L3G4200DInit();
	delay(100);
	Serial.println("Magnetometer Self Test");
	if(imu.HMC5883LTest()){
		Serial.println("Magnetometer passed test");
	}
	delay(200);
	Serial.println("Magnetometer initialization");
	imu.HMC5883LInit();
	delay(1000);
	Serial.println("Start Magnetometer Calibration");
	imu.HMC5883LCal();



}
// The loop function is called in an endless loop
void loop()
{
	if(imu.readByte(ADXL345_ADDRESS, ADXL345_INT_SOURCE) & 0x80) {
		imu.readAccelData(ADXL345Buff);
		imu.ADXL345ReadData(ADXL345Buff, buff.ADXL345Res);
	}

	if(imu.readByte(L3G4200D_ADDRESS, L3G4200D_STATUS_REG) & 0x08) {
		imu.readGyroData(L3G4200DBuff);
		imu.L3G4200DReadData(L3G4200DBuff, buff.L3G4200DRes);


	}


	if(imu.readByte(HMC5883L_ADDRESS, HMC5883L_STATUS) & 0x01) {
		imu.readMagData(HMC5883LBuff);
		imu.HMC5883LReadData(HMC5883LBuff, buff.HMC5883LRes);
	}

	imu.sensorsCallback(buff);

	Serial.println(imu.euler.x);

	delay(10);





}

