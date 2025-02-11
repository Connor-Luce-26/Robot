#pragma once
#include <Wire.h>
#include <Arduino.h>
#include "FIR.hpp"
#include "Vector.hpp"
#define MPU6050_ADDRESS 0x68
#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define GYROSCOPE_FS_SEL_0 0x00
#define GYROSCOPE_FS_SEL_1 0x08
#define GYROSCOPE_FS_SEL_2 0x10
#define GYROSCOPE_FS_SEL_3 0x18
#define GYROSCOPE_FULL_SCALE_RANGE_0 250	// degrees per second
#define GYROSCOPE_FULL_SCALE_RANGE_1 500	// degrees per second
#define GYROSCOPE_FULL_SCALE_RANGE_2 1000	// degrees per second
#define GYROSCOPE_FULL_SCALE_RANGE_3 2000	// degrees per second
#define ACCELEROMETER_FULL_SCALE_RANGE_0 2	// gravitational Accelerometer
#define ACCELEROMETER_FULL_SCALE_RANGE_1 4	// gravitational Accelerometer
#define ACCELEROMETER_FULL_SCALE_RANGE_2 8	// gravitational Accelerometer
#define ACCELEROMETER_FULL_SCALE_RANGE_3 16 // gravitational Accelerometer
#define ACCELEROMETER_FS_SEL_0 0x00
#define ACCELEROMETER_FS_SEL_1 0x08
#define ACCELEROMETER_FS_SEL_2 0x10
#define ACCELEROMETER_FS_SEL_3 0x18
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define GRAVITATIONAL_ACCELERATION 9.81 // meters per second squared
#define NUMBER_OF_CALIBRATION_SAMPLES 1000
#define FIR_COEFFICIENTS {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}
#define FIR_ORDER 10
#define CALIBRATION_DELAY 10
class MPU6050
{
private:
	uint16_t accelerometerScale;
	uint16_t gyroscopeScale;
	Vector accelerationVector;
	Vector angularVelocityVector;
	Vector accelerationCalibrationVector;
	Vector angularVelocityCalibrationVector;
public:
	MPU6050(uint16_t accelerometerScale, uint16_t gyroscopeScale)
	{
		this->accelerometerScale = accelerometerScale;
		this->gyroscopeScale = gyroscopeScale;
		Wire.begin();
	}
	~MPU6050()
	{
		Wire.end();
	}
	void write(uint8_t address, uint8_t data)
	{
		Wire.beginTransmission(MPU6050_ADDRESS);
		Wire.write(address);
		Wire.write(data);
		Wire.endTransmission();
	}
	uint8_t read(uint8_t address)
	{
		Wire.beginTransmission(MPU6050_ADDRESS);
		Wire.write(address);
		Wire.endTransmission(false);
		Wire.requestFrom(MPU6050_ADDRESS, 1);
		while (!Wire.available())
			;
		return Wire.read();
	}
	int16_t getData(uint8_t addressH, uint8_t addressL)
	{
		int16_t data = this->read(addressH);
		data = (data << 8);
		data |= this->read(addressL);
		return data;
	}
	Vector getUnfilteredAcceleration()
	{
		double x = this->getData(ACCEL_XOUT_H, ACCEL_XOUT_L) * GRAVITATIONAL_ACCELERATION * 2 / UINT16_MAX;
		double y = this->getData(ACCEL_YOUT_H, ACCEL_YOUT_L) * GRAVITATIONAL_ACCELERATION * 2 / UINT16_MAX;
		double z = this->getData(ACCEL_ZOUT_H, ACCEL_ZOUT_L) * GRAVITATIONAL_ACCELERATION * 2 / UINT16_MAX;
		Vector acceleration = Vector({x, y, z}, "column");
		return acceleration;
	}
	Vector getUnfilteredAngularVelocity()
	{
		double x = this->getData(GYRO_XOUT_H, GYRO_XOUT_L) * this->gyroscopeScale / UINT16_MAX;
		double y = this->getData(GYRO_YOUT_H, GYRO_YOUT_L) * this->gyroscopeScale / UINT16_MAX;
		double z = this->getData(GYRO_ZOUT_H, GYRO_ZOUT_L) * this->gyroscopeScale / UINT16_MAX;
		Vector angularVelocity = Vector({x, y, z}, "column");
		return angularVelocity;
	}	
	void calibrate()
	{
		uint_8 sampleCount = 0;
		this->accelerationCalibrationVector = Vector({0, 0, 0}, "column");
		this->angularVelocityCalibrationVector = Vector({0, 0, 0}, "column");
		while (sampleCount < NUMBER_OF_CALIBRATION_SAMPLES)
		{
			this->accelerationCalibrationVector = this->accelerationCalibrationVector + this->getUnfilteredAcceleration();
			this->angularVelocityCalibrationVector = this->angularVelocityCalibrationVector + this->getUnfilteredAngularVelocity();
			sampleCount++;
			delay(CALIBRATION_DELAY);
		}
	}
	void setup()
	{
		this->write(PWR_MGMT_1, 0);
		switch (this->gyroscopeScale)
		{
		case GYROSCOPE_FULL_SCALE_RANGE_0:
			this->write(GYRO_CONFIG, GYROSCOPE_FS_SEL_0);
			break;
		case GYROSCOPE_FULL_SCALE_RANGE_1:
			this->write(GYRO_CONFIG, GYROSCOPE_FS_SEL_1);
			break;
		case GYROSCOPE_FULL_SCALE_RANGE_2:
			this->write(GYRO_CONFIG, GYROSCOPE_FS_SEL_2);
			break;
		case GYROSCOPE_FULL_SCALE_RANGE_3:
			this->write(GYRO_CONFIG, GYROSCOPE_FS_SEL_3);
			break;
		default:
			break;
		}
		switch (this->accelerometerScale)
		{
		case ACCELEROMETER_FULL_SCALE_RANGE_0:
			this->write(ACCEL_CONFIG, ACCELEROMETER_FS_SEL_0);
			break;
		case ACCELEROMETER_FULL_SCALE_RANGE_1:
			this->write(ACCEL_CONFIG, ACCELEROMETER_FS_SEL_1);
			break;
		case ACCELEROMETER_FULL_SCALE_RANGE_2:
			this->write(ACCEL_CONFIG, ACCELEROMETER_FS_SEL_2);
			break;
		case ACCELEROMETER_FULL_SCALE_RANGE_3:
			this->write(ACCEL_CONFIG, ACCELEROMETER_FS_SEL_3);
			break;
		default:
			break;
		}
		this->calibrate();
	}
	String getCalibrationString()
	{
		//TODO: Implement getCalibrationString
	}
};