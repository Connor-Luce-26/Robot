#pragma once
#include <Arduino.h>
#include "MPU6050.hpp"
#include "Integral.hpp"
class IMU
{
private:
	double xAcceleration;
	double yAcceleration;
	double zAcceleration;
	Integral xVelocity;
	Integral yVelocity;
	Integral zVelocity;
	Integral xPosition;
	Integral yPosition;
	Integral zPosition;
	double xAngularVelocity;
	double yAngularVelocity;
	double zAngularVelocity;
	Integral xAngularPosition;
	Integral yAngularPosition;
	Integral zAngularPosition;
	MPU6050 mpu;
public:
	IMU()
	{

	}
	~IMU()
	{
	}
	void setup()
	{
		Serial.println("Starting IMU Setup");
		this->mpu.setup();
		Serial.println("IMU Setup Complete");
	}
	void update()
	{
		this->xAngularVelocity = this->mpu.getXGyroscope();
		this->yAngularVelocity = this->mpu.getYGyroscope();
		this->zAngularVelocity = this->mpu.getZGyroscope();
		this->xAngularPosition.update(this->xAngularVelocity);
		this->yAngularPosition.update(this->yAngularVelocity);
		this->zAngularPosition.update(this->zAngularVelocity);
		this->mpu.updateAccelerometerRotationCorrection(this->xAngularPosition.getValue(), this->yAngularPosition.getValue(), this->zAngularPosition.getValue());
		this->xAcceleration = this->mpu.getXAccelerometer();
		this->yAcceleration = this->mpu.getYAccelerometer();
		this->zAcceleration = this->mpu.getZAccelerometer();
		this->xVelocity.update(this->xAcceleration);
		this->yVelocity.update(this->yAcceleration);
		this->zVelocity.update(this->zAcceleration);
		this->xPosition.update(this->xVelocity.getValue());
		this->yPosition.update(this->yVelocity.getValue());
		this->zPosition.update(this->zVelocity.getValue());
	}
	String getDataString()
	{
		this->update();
		String data = "";
		data += "X Acceleration: ";
		data += this->xAcceleration;
		data += "\n";
		data += "Y Acceleration: ";
		data += this->yAcceleration;
		data += "\n";
		data += "Z Acceleration: ";
		data += this->zAcceleration;
		data += "\n";
		data += "X Velocity: ";
		data += this->xVelocity.getValue();
		data += "\n";
		data += "Y Velocity: ";
		data += this->yVelocity.getValue();
		data += "\n";
		data += "Z Velocity: ";
		data += this->zVelocity.getValue();
		data += "\n";
		data += "X Position: ";
		data += this->xPosition.getValue();
		data += "\n";
		data += "Y Position: ";
		data += this->yPosition.getValue();
		data += "\n";
		data += "Z Position: ";
		data += this->zPosition.getValue();
		data += "\n";
		data += "X Angular Velocity: ";
		data += this->xAngularVelocity;
		data += "\n";
		data += "Y Angular Velocity: ";
		data += this->yAngularVelocity;
		data += "\n";
		data += "Z Angular Velocity: ";
		data += this->zAngularVelocity;
		data += "\n";
		data += "X Angular Position: ";
		data += this->xAngularPosition.getValue();
		data += "\n";
		data += "Y Angular Position: ";
		data += this->yAngularPosition.getValue();
		data += "\n";
		data += "Z Angular Position: ";
		data += this->zAngularPosition.getValue();
		data += "\n";
		return data;
	}
};
