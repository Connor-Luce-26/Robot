#pragma once
#include <Arduino.h>
#define MOTOR_FRONT_RIGHT_FORWARD_PIN 11
#define MOTOR_FRONT_RIGHT_REVERSE_PIN 10
#define MOTOR_FRONT_LEFT_FORWARD_PIN 9
#define MOTOR_FRONT_LEFT_REVERSE_PIN 8
#define MOTOR_BACK_RIGHT_FORWARD_PIN 7
#define MOTOR_BACK_RIGHT_REVERSE_PIN 6
#define MOTOR_BACK_LEFT_FORWARD_PIN 4
#define MOTOR_BACK_LEFT_REVERSE_PIN 5
class Motor
{
private:
	uint8_t forwardPin;
	uint8_t reversePin;
	uint8_t dutyCycle;
	bool forward;

public:
	Motor()
	{
		this->forward = true;
	}
	Motor(uint8_t forwardPin, uint8_t reversePin) : Motor()
	{
		this->forwardPin = forwardPin;
		this->reversePin = reversePin;
		this->dutyCycle = 0;
	}
	~Motor()
	{
	}
	void setupMotor()
	{
		pinMode(this->forwardPin, OUTPUT);
		pinMode(this->reversePin, OUTPUT);
	}
	void setForward()
	{
		digitalWrite(this->reversePin, LOW);
		this->forward = true;
	}
	void setReverse()
	{
		digitalWrite(this->forwardPin, LOW);
		this->forward = false;
	}
	void setDutyCycle(uint8_t dutyCycle)
	{
		this->dutyCycle = dutyCycle;
		if (this->forward)
		{
			analogWrite(this->forwardPin, dutyCycle);
		}
		else
		{
			analogWrite(this->reversePin, dutyCycle);
		}
	}
	void setThrottleLevel(int16_t setThrottleLevel)
	{
		if (setThrottleLevel > 0)
		{
			this->setForward();
			this->setDutyCycle(setThrottleLevel);
		}
		else if (setThrottleLevel < 0)
		{
			this->setReverse();
			this->setDutyCycle(-setThrottleLevel);
		}
		else
		{
			this->setDutyCycle(0);
		}
	}
};