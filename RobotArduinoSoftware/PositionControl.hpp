#pragma once
#include <Arduino.h>
#include "IMU.hpp"
#include "Motor.hpp"
#define X_POSITION_PROPORTIONAL_GAIN 1
#define Y_POSITION_PROPORTIONAL_GAIN 1
#define THETA_POSITION_PROPORTIONAL_GAIN 1

class PositionControl
{
private:
	IMU imu;
	Motor motorFrontRight;
	Motor motorFrontLeft;
	Motor motorBackRight;
	Motor motorBackLeft;
	double xPosition;
	double yPosition;
	double thetaPosition;
	double xPositionSetpoint;
	double yPositionSetpoint;
	double thetaPositionSetpoint;
	double xPositionPrefilterGain;
	double yPositionPrefilterGain;
	double thetaPositionPrefilterGain;
	double xControlSignal;
	double yControlSignal;
	double thetaControlSignal;
public:
	PositionControl()
	{
		this->motorFrontRight = Motor(MOTOR_FRONT_RIGHT_FORWARD_PIN, MOTOR_FRONT_RIGHT_REVERSE_PIN);
		this->motorFrontLeft = Motor(MOTOR_FRONT_LEFT_FORWARD_PIN, MOTOR_FRONT_LEFT_REVERSE_PIN);
		this->motorBackRight = Motor(MOTOR_BACK_RIGHT_FORWARD_PIN, MOTOR_BACK_RIGHT_REVERSE_PIN);
		this->motorBackLeft = Motor(MOTOR_BACK_LEFT_FORWARD_PIN, MOTOR_BACK_LEFT_REVERSE_PIN);
	}
	~PositionControl()
	{
	}
	void setupPositionControl()
	{
		this->imu.setupIMU();
		this->motorFrontRight.setupMotor();
		this->motorFrontLeft.setupMotor();
		this->motorBackRight.setupMotor();
		this->motorBackLeft.setupMotor();
	}
	void updatePrefilterGains()
	{
		this->xPositionPrefilterGain = this->xPositionSetpoint / this->xPosition;
		this->yPositionPrefilterGain = this->yPositionSetpoint / this->yPosition;
		this->thetaPositionPrefilterGain = this->thetaPositionSetpoint / this->thetaPosition;
	}
	void updateControlSignals()
	{
		this->xControlSignal = X_POSITION_PROPORTIONAL_GAIN * ((this->xPositionPrefilterGain * this->xPositionSetpoint) - this->xPosition);
		this->yControlSignal = Y_POSITION_PROPORTIONAL_GAIN * ((this->yPositionPrefilterGain * this->yPositionSetpoint) - this->yPosition);
		this->thetaControlSignal = THETA_POSITION_PROPORTIONAL_GAIN * ((this->thetaPositionPrefilterGain * this->thetaPositionSetpoint) - this->thetaPosition);
	}
	int16_t getFrontRightThrottleLevelControlSignal()
	{
		return (int16_t) (-this->xControlSignal + this->yControlSignal + this->thetaControlSignal);
	}
	int16_t getFrontLeftThrottleLevelControlSignal()
	{
		return (int16_t) (this->xControlSignal + this->yControlSignal - this->thetaControlSignal);
	}
	int16_t getBackRightThrottleLevelControlSignal()
	{
		return (int16_t) (this->xControlSignal + this->yControlSignal + this->thetaControlSignal);
	}
	int16_t getBackLeftThrottleLevelControlSignal()
	{
		return (int16_t) (-this->xControlSignal + this->yControlSignal - this->thetaControlSignal);
	}
	void updateSensorData()
	{
		this->imu.updateIMU();
		this->xPosition = this->imu.getXPosition();
		this->yPosition = this->imu.getYPosition();
		this->thetaPosition = this->imu.getZAngularPosition();
	}
	void updatePositionControl()
	{
		this->updateSensorData();
		this->updatePrefilterGains();
		this->updateControlSignals();
		this->motorFrontRight.setThrottleLevel(this->getFrontRightThrottleLevelControlSignal());
		this->motorFrontLeft.setThrottleLevel(this->getFrontLeftThrottleLevelControlSignal());
		this->motorBackRight.setThrottleLevel(this->getBackRightThrottleLevelControlSignal());
		this->motorBackLeft.setThrottleLevel(this->getBackLeftThrottleLevelControlSignal());
	}
	void setXPositionSetpoint(double xPositionSetpoint)
	{
		this->xPositionSetpoint = xPositionSetpoint;
	}
	void setYPositionSetpoint(double yPositionSetpoint)
	{
		this->yPositionSetpoint = yPositionSetpoint;
	}
	void setThetaPositionSetpoint(double thetaPositionSetpoint)
	{
		this->thetaPositionSetpoint = thetaPositionSetpoint;
	}
	double getXPosition()
	{
		return this->xPosition;
	}
	double getYPosition()
	{
		return this->yPosition;
	}
	double getThetaPosition()
	{
		return this->thetaPosition;
	}
	String getPositionString()
	{
		return "X Position: " + String(this->xPosition) + " m\n" +
			   "Y Position: " + String(this->yPosition) + " m\n" +
			   "Theta Position: " + String(this->thetaPosition) + " degrees";
	}
	double getXPositionSetpoint()
	{
		return this->xPositionSetpoint;
	}
	double getYPositionSetpoint()
	{
		return this->yPositionSetpoint;
	}
};