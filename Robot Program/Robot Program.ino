#include <Arduino.h>
//#include "HCSR04.hpp"
#include "MPU6050.hpp"
#include "Integral.hpp"
MPU6050 mpu(ACCELEROMETER_FULL_SCALE_RANGE_0, GYROSCOPE_FULL_SCALE_RANGE_0);
Integral velocity;
Integral position;
int counter = 0;
void setup() 
{
    Serial.begin(115200);
    mpu.setup();
	Serial.print(mpu.getCalibrationString());
}

void loop() 
{	
	Serial.print("X Accelerometer: ");
	Serial.println(mpu.getXAccelerometer());
	// position.update(velocity.update(fir.update(mpu.getXAccelerometer())));
	// Serial.print("Position: ");
	// Serial.println(position.getValue());
	// Serial.print("Velocity: ");
	// Serial.println(velocity.getValue());
	delay(1000);
}