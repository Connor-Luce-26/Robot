#pragma once
#include <Wire.h>
#define MPU6050_ADDRESS 0x68
#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define GYROSCOPE_FS_SEL_0 0x00
#define GYROSCOPE_FS_SEL_1 0x08
#define GYROSCOPE_FS_SEL_2 0x10
#define GYROSCOPE_FS_SEL_3 0x18
#define GYROSCOPE_FULL_SCALE_RANGE_0 250 // degrees per second
#define GYROSCOPE_FULL_SCALE_RANGE_1 500 // degrees per second
#define GYROSCOPE_FULL_SCALE_RANGE_2 1000 // degrees per second
#define GYROSCOPE_FULL_SCALE_RANGE_3 2000 // degrees per second
#define ACCELEROMETER_FULL_SCALE_RANGE_0 2 // gravitational acceleration
#define ACCELEROMETER_FULL_SCALE_RANGE_1 4 // gravitational acceleration
#define ACCELEROMETER_FULL_SCALE_RANGE_2 8 // gravitational acceleration
#define ACCELEROMETER_FULL_SCALE_RANGE_3 16 // gravitational acceleration
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
class MPU6050
{
private:
	uint16_t accelerometerScale;
	uint16_t gyroscopeScale;

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
	}
	int16_t getData(uint8_t addressH, uint8_t addressL)
	{
		int16_t data = this->read(addressH);
		data = (data << 8);
		data |= this->read(addressL);
		return data;
	}
	float getXAcceleration()
	{
		return ((float)this->getData(ACCEL_XOUT_H, ACCEL_XOUT_L)) / INT16_MAX * (this->accelerometerScale) * GRAVITATIONAL_ACCELERATION;
	}
	float getYAcceleration()
	{
		return ((float)this->getData(ACCEL_YOUT_H, ACCEL_YOUT_L)) / INT16_MAX * (this->accelerometerScale) * GRAVITATIONAL_ACCELERATION;
	}
	float getZAcceleration()
	{
		return ((float)this->getData(ACCEL_ZOUT_H, ACCEL_ZOUT_L)) / INT16_MAX * (this->accelerometerScale) * GRAVITATIONAL_ACCELERATION;
	}
	float getXGyroscope()
	{
		return ((float)this->getData(GYRO_XOUT_H, GYRO_XOUT_L)) / INT16_MAX * (this->gyroscopeScale);
	}
	float getYGyroscope()
	{
		return ((float)this->getData(GYRO_YOUT_H, GYRO_YOUT_L)) / INT16_MAX * (this->gyroscopeScale);
	}
	float getZGyroscope()
	{
		return ((float)this->getData(GYRO_ZOUT_H, GYRO_ZOUT_L)) / INT16_MAX * (this->gyroscopeScale);
	}
};