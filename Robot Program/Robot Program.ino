#include <Arduino.h>
#include "HCSR04.hpp"
#include "MPU6050.hpp"
void setup() 
{
	Serial.begin(115200);
	MPU6050 mpu = mpu6050(ACCELEROMETER_FULL_SCALE_RANGE_0, GYROSCOPE_FULL_SCALE_RANGE_0);
	MPU6050.setup();
}
void loop() 
{
	Serial.println(mpu.getAccelerationX());	
}