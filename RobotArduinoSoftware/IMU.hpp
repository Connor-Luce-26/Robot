#pragma once
#include <Arduino.h>
#include "Integral.hpp"
#include <Adafruit_MPU6050.h>
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
	Adafruit_MPU6050 mpu;
public:
	IMU()
	{

	}
	~IMU()
	{
	}
	void setupIMU()
	{
		Serial.println("Starting IMU Setup");
		mpu.begin();
		mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
		mpu.setGyroRange(MPU6050_RANGE_250_DEG);
		mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
		Serial.println("IMU Setup Complete");
	}
	void updateIMU()
	{
		sensors_event_t a, g, temp;
    	mpu.getEvent(&a, &g, &temp);
		this->xAngularVelocity = g.gyro.x;
		this->yAngularVelocity = g.gyro.y;
		this->zAngularVelocity = g.gyro.z;
		this->xAngularPosition.updateIntegral(this->xAngularVelocity);
		this->yAngularPosition.updateIntegral(this->yAngularVelocity);
		this->zAngularPosition.updateIntegral(this->zAngularVelocity);
		this->xAcceleration = a.acceleration.x;
		this->yAcceleration = a.acceleration.y;
		this->zAcceleration = a.acceleration.z;
		this->xVelocity.updateIntegral(this->xAcceleration);
		this->yVelocity.updateIntegral(this->yAcceleration);
		this->zVelocity.updateIntegral(this->zAcceleration);
		this->xPosition.updateIntegral(this->xVelocity.getIntegralValue());
		this->yPosition.updateIntegral(this->yVelocity.getIntegralValue());
		this->zPosition.updateIntegral(this->zVelocity.getIntegralValue());
	}
	String getDataString()
	{
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
		data += String(this->xVelocity.getIntegralValue());
		data += "\n";
		data += "Y Velocity: ";
		data += String(this->yVelocity.getIntegralValue());
		data += "\n";
		data += "Z Velocity: ";
		data += String(this->zVelocity.getIntegralValue());
		data += "\n";
		data += "X Position: ";
		data += String(this->xPosition.getIntegralValue());
		data += "\n";
		data += "Y Position: ";
		data += String(this->yPosition.getIntegralValue());
		data += "\n";
		data += "Z Position: ";
		data += String(this->zPosition.getIntegralValue());
		data += "\n";
		data += "X Angular Velocity: ";
		data += String(this->xAngularVelocity);
		data += "\n";
		data += "Y Angular Velocity: ";
		data += String(this->yAngularVelocity);
		data += "\n";
		data += "Z Angular Velocity: ";
		data += String(this->zAngularVelocity);
		data += "\n";
		data += "X Angular Position: ";
		data += String(this->xAngularPosition.getIntegralValue());
		data += "\n";
		data += "Y Angular Position: ";
		data += String(this->yAngularPosition.getIntegralValue());
		data += "\n";
		data += "Z Angular Position: ";
		data += String(this->zAngularPosition.getIntegralValue());
		data += "\n";
		return data;
	}
	double getXAcceleration()
	{
		return this->xAcceleration;
	}
	double getYAcceleration()
	{
		return this->yAcceleration;
	}
	double getZAcceleration()
	{
		return this->zAcceleration;
	}
	double getXVelocity()
	{
		return this->xVelocity.getIntegralValue();
	}
	double getYVelocity()
	{
		return this->yVelocity.getIntegralValue();
	}
	double getZVelocity() 
	{
		return this->zVelocity.getIntegralValue();
	}
	double getXPosition()
	{
		return this->xPosition.getIntegralValue();
	}
	double getYPosition()
	{
		return this->yPosition.getIntegralValue();
	}
	double getZPosition()
	{
		return this->zPosition.getIntegralValue();
	}
	double getXAngularVelocity()
	{
		return this->xAngularVelocity;
	}
	double getYAngularVelocity()
	{
		return this->yAngularVelocity;
	}
	double getZAngularVelocity()
	{
		return this->zAngularVelocity;
	}
	double getXAngularPosition()
	{
		return this->xAngularPosition.getIntegralValue();
	}
	double getYAngularPosition()
	{
		return this->yAngularPosition.getIntegralValue();
	}
	double getZAngularPosition()
	{
		return this->zAngularPosition.getIntegralValue();
	}
};
