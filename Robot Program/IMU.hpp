#pragma once
#include "Vector.hpp"
#include "VectorIntegral.hpp"
#include "MPU6050.hpp"
#define VELOCITY_VECTOR_SIZE 3
#define POSITION_VECTOR_SIZE 3
#define ANGLE_VECTOR_SIZE 3
class IMU
{
private:
	MPU6050 mpu;
	VectorIntegral velocity;
	VectorIntegral position;
	VectorIntegral angle;
public:
	IMU(uint16_t accelerometerScale, uint16_t gyroscopeScale)
	{
		this->mpu = MPU6050(accelerometerScale, gyroscopeScale);
		this->velocity = VectorIntegral(VELOCITY_VECTOR_SIZE);
		this->position = VectorIntegral(POSITION_VECTOR_SIZE);
		this->angle = VectorIntegral(ANGLE_VECTOR_SIZE);
	}
	~IMU();
	void setup()
	{
		this->mpu.setup();
	}
	void update()
	{
		this->angle.update(this->mpu.getFilteredAngularVelocityVector());
		this->velocity.update(this->mpu.getFilteredAccelerationVector(this->angle.getValue()));
		this->position.update(this->velocity.getValue());
	}
	String getCalibrationString()
	{
		this->mpu.getCalibrationString();
	}
	Vector getVelocity()
	{
		return this->velocity.getValue();
	}
	Vector getPosition()
	{
		return this->position.getValue();
	}
	Vector getAngle()
	{
		return this->angle.getValue();
	}
};