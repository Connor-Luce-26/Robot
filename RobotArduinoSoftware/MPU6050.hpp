#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "FIR.hpp"
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
#define GRAVITATIONAL_ACCELEROMETER 9.81 // meters per second squared
#define MPU6050_NUMBER_OF_CALIBRATION_SAMPLES 1000
#define MPU6050_FIR_COEFFICIENTS {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}
#define MPU6050_FIR_ORDER 10
#define MPU6050_CALIBRATION_DELAY 10
#define MPU6050_FIR_DELAY 10
constexpr double MPU6050FIRCoefficients[MPU6050_FIR_ORDER] = MPU6050_FIR_COEFFICIENTS;
class MPU6050
{
private:
	uint16_t accelerometerScale;
	uint16_t gyroscopeScale;
	double xAccelerometerCalibration;
	double yAccelerometerCalibration;
	double zAccelerometerCalibration;
	double xGyroscopeCalibration;
	double yGyroscopeCalibration;
	double zGyroscopeCalibration;
	FIR xAccelerometerFIR;
	FIR yAccelerometerFIR;
	FIR zAccelerometerFIR;
	FIR xGyroscopeFIR;
	FIR yGyroscopeFIR;
	FIR zGyroscopeFIR;

public:
	MPU6050(uint16_t accelerometerScale, uint16_t gyroscopeScale);
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
		{
		}
		return Wire.read();
	}
	int16_t getData(uint8_t addressH, uint8_t addressL)
	{
		int16_t data = this->read(addressH);
		data = (data << 8);
		data |= this->read(addressL);
		return data;
	}
	double getUnfilteredXAccelerometer()
	{
		return ((double)this->getData(ACCEL_XOUT_H, ACCEL_XOUT_L)) / INT16_MAX * (this->accelerometerScale) * GRAVITATIONAL_ACCELEROMETER;
	}
	double getUnfilteredYAccelerometer()
	{
		return ((double)this->getData(ACCEL_YOUT_H, ACCEL_YOUT_L)) / INT16_MAX * (this->accelerometerScale) * GRAVITATIONAL_ACCELEROMETER;
	}
	double getUnfilteredZAccelerometer()
	{
		return ((double)this->getData(ACCEL_ZOUT_H, ACCEL_ZOUT_L)) / INT16_MAX * (this->accelerometerScale) * GRAVITATIONAL_ACCELEROMETER;
	}
	double getUnfilteredXGyroscope()
	{
		return ((double)this->getData(GYRO_XOUT_H, GYRO_XOUT_L)) / INT16_MAX * (this->gyroscopeScale);
	}
	double getUnfilteredYGyroscope()
	{
		return ((double)this->getData(GYRO_YOUT_H, GYRO_YOUT_L)) / INT16_MAX * (this->gyroscopeScale);
	}
	double getUnfilteredZGyroscope()
	{
		return ((double)this->getData(GYRO_ZOUT_H, GYRO_ZOUT_L)) / INT16_MAX * (this->gyroscopeScale);
	}
	double getXGyroscope()
	{
		for (uint8_t i = 0; i < MPU6050_FIR_ORDER; i++)
		{
			this->xGyroscopeFIR.update(this->getUnfilteredXGyroscope() - this->xGyroscopeCalibration);
			delay(MPU6050_FIR_DELAY);
		}
		return this->xGyroscopeFIR.getOutput();
	}
	double getYGyroscope()
	{
		for (uint8_t i = 0; i < MPU6050_FIR_ORDER; i++)
		{
			this->yGyroscopeFIR.update(this->getUnfilteredYGyroscope() - this->yGyroscopeCalibration);
			delay(MPU6050_FIR_DELAY);
		}
		return this->yGyroscopeFIR.getOutput();
	}
	double getZGyroscope()
	{
		for (uint8_t i = 0; i < MPU6050_FIR_ORDER; i++)
		{
			this->zGyroscopeFIR.update(this->getUnfilteredZGyroscope() - this->zGyroscopeCalibration);
			delay(MPU6050_FIR_DELAY);
		}
		return this->zGyroscopeFIR.getOutput();
	}
	double getXAccelerometer()
	{
		for (uint8_t i = 0; i < MPU6050_FIR_ORDER; i++)
		{
			this->xAccelerometerFIR.update(this->getUnfilteredXAccelerometer() - this->xAccelerometerCalibration);
			delay(MPU6050_FIR_DELAY);
		}
		return this->xAccelerometerFIR.getOutput();
	}
	double getYAccelerometer()
	{
		for (uint8_t i = 0; i < MPU6050_FIR_ORDER; i++)
		{
			this->yAccelerometerFIR.update(this->getUnfilteredYAccelerometer() - this->yAccelerometerCalibration);
			delay(MPU6050_FIR_DELAY);
		}
		return this->yAccelerometerFIR.getOutput();
	}
	double getZAccelerometer()
	{
		for (uint8_t i = 0; i < MPU6050_FIR_ORDER; i++)
		{
			this->zAccelerometerFIR.update(this->getUnfilteredZAccelerometer() - this->zAccelerometerCalibration);
			delay(MPU6050_FIR_DELAY);
		}
		return this->zAccelerometerFIR.getOutput();
	}
	void updateAccelerometerRotationCorrection(double xAngularPosition, double yAngularPosition, double zAngularPosition)
	{
		double oldXAccelerometerCalibration = this->xAccelerometerCalibration;
		double oldYAccelerometerCalibration = this->yAccelerometerCalibration;
		double oldZAccelerometerCalibration = this->zAccelerometerCalibration;
		this->xAccelerometerCalibration = oldXAccelerometerCalibration * cos(yAngularPosition) * cos(zAngularPosition) +
										  oldYAccelerometerCalibration * (sin(xAngularPosition) * sin(yAngularPosition) * cos(zAngularPosition) - cos(xAngularPosition) * sin(zAngularPosition)) +
										  oldZAccelerometerCalibration * (cos(xAngularPosition) * sin(yAngularPosition) * cos(zAngularPosition) + sin(xAngularPosition) * sin(zAngularPosition));
		this->yAccelerometerCalibration = oldXAccelerometerCalibration * cos(yAngularPosition) * sin(zAngularPosition) +
										  oldYAccelerometerCalibration * (sin(xAngularPosition) * sin(yAngularPosition) * sin(zAngularPosition) + cos(xAngularPosition) * cos(zAngularPosition)) +
										  oldZAccelerometerCalibration * (cos(xAngularPosition) * sin(yAngularPosition) * sin(zAngularPosition) - sin(xAngularPosition) * cos(zAngularPosition));
		this->zAccelerometerCalibration = -oldXAccelerometerCalibration * sin(yAngularPosition) +
										  oldYAccelerometerCalibration * sin(xAngularPosition) * cos(yAngularPosition) +
										  oldZAccelerometerCalibration * cos(xAngularPosition) * cos(yAngularPosition);
	}
	String getDataString()
	{
		return "X Accelerometer: " + String(this->getXAccelerometer()) + " m/s^2\n" +
			   "Y Accelerometer: " + String(this->getYAccelerometer()) + " m/s^2\n" +
			   "Z Accelerometer: " + String(this->getZAccelerometer()) + " m/s^2\n" +
			   "X Gyroscope: " + String(this->getXGyroscope()) + " degrees/s\n" +
			   "Y Gyroscope: " + String(this->getYGyroscope()) + " degrees/s\n" +
			   "Z Gyroscope: " + String(this->getZGyroscope()) + " degrees/s\n";
	}
	void calibrate()
	{
		Serial.println("Starting MPU6050 Calibration");
		double xAccelerometer = 0.0;
		double yAccelerometer = 0.0;
		double zAccelerometer = 0.0;
		double xGyroscope = 0.0;
		double yGyroscope = 0.0;
		double zGyroscope = 0.0;
		for (int i = 0; i < MPU6050_NUMBER_OF_CALIBRATION_SAMPLES; i++)
		{
			xAccelerometer += this->getUnfilteredXAccelerometer();
			yAccelerometer += this->getUnfilteredYAccelerometer();
			zAccelerometer += this->getUnfilteredZAccelerometer();
			xGyroscope += this->getUnfilteredXGyroscope();
			yGyroscope += this->getUnfilteredYGyroscope();
			zGyroscope += this->getUnfilteredZGyroscope();
			delay(MPU6050_CALIBRATION_DELAY);
			Serial.print("Calibration Sample ");
			Serial.print(i);
			Serial.print(" of ");
			Serial.println(MPU6050_NUMBER_OF_CALIBRATION_SAMPLES);
		}
		this->xAccelerometerCalibration = xAccelerometer / MPU6050_NUMBER_OF_CALIBRATION_SAMPLES;
		this->yAccelerometerCalibration = yAccelerometer / MPU6050_NUMBER_OF_CALIBRATION_SAMPLES;
		this->zAccelerometerCalibration = zAccelerometer / MPU6050_NUMBER_OF_CALIBRATION_SAMPLES;
		this->xGyroscopeCalibration = xGyroscope / MPU6050_NUMBER_OF_CALIBRATION_SAMPLES;
		this->yGyroscopeCalibration = yGyroscope / MPU6050_NUMBER_OF_CALIBRATION_SAMPLES;
		this->zGyroscopeCalibration = zGyroscope / MPU6050_NUMBER_OF_CALIBRATION_SAMPLES;
		Serial.println("MPU6050 Calibration Complete");
		Serial.println(this->getCalibrationString());
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
		return "X Accelerometer Calibration: " + String(this->xAccelerometerCalibration) + "\n" +
			   "Y Accelerometer Calibration: " + String(this->yAccelerometerCalibration) + "\n" +
			   "Z Accelerometer Calibration: " + String(this->zAccelerometerCalibration) + "\n" +
			   "X Gyroscope Calibration: " + String(this->xGyroscopeCalibration) + "\n" +
			   "Y Gyroscope Calibration: " + String(this->yGyroscopeCalibration) + "\n" +
			   "Z Gyroscope Calibration: " + String(this->zGyroscopeCalibration) + "\n";
	}
};
MPU6050::MPU6050(uint16_t accelerometerScale, uint16_t gyroscopeScale)
	: accelerometerScale(accelerometerScale), gyroscopeScale(gyroscopeScale),
	  xAccelerometerFIR(MPU6050FIRCoefficients), yAccelerometerFIR(MPU6050FIRCoefficients),
	  zAccelerometerFIR(MPU6050FIRCoefficients), xGyroscopeFIR(MPU6050FIRCoefficients),
	  yGyroscopeFIR(MPU6050FIRCoefficients), zGyroscopeFIR(MPU6050FIRCoefficients)
{
	Wire.begin();
}