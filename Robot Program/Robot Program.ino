#include <Arduino.h>
#include "IMU.hpp"
IMU imu = IMU(ACCELEROMETER_FULL_SCALE_RANGE_0, GYROSCOPE_FULL_SCALE_RANGE_0);
void setup() 
{
    Serial.begin(115200);
    imu.setup();
	Serial.println(imu.getCalibrationString());
}
void loop() 
{	
	imu.update();
	Serial.println(imu.getVelocity().toString());
	delay(1000);
}