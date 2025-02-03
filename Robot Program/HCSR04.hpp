#pragma once
#include <Arduino.h>
class HCSR04
{
private:
	uint8_t triggerOutput;
	uint8_t echoInterrupt;
	long startEchoTime;
	long endEchoTime;
public:
	HCSR04(uint8_t triggerOutput, uint8_t echoInterrupt)
	{
		this->triggerOutput = triggerOutput;
		this->echoInterrupt = echoInterrupt;
		pinMode(this->triggerOutput, OUTPUT);
		pinMode(this->echoInterrupt, INPUT);
		digitalWrite(this->triggerOutput, LOW);
	}
	~HCSR04();
	void trigger()
	{
		digitalWrite(this->triggerOutput, HIGH);
		delayMicroseconds(10);
		digitalWrite(this->triggerOutput, LOW);
		this->startEchoTime = micros();
	}
	void echo()
	{
		this->endEchoTime = micros();
	}
	void attachInterrupt()
	{
		attachInterrupt(digitalPinToInterrupt(this->echoInterrupt), this->echo, FALLING);
	}
	double getDistance()
	{
		this->attachInterrupt();
		this->trigger();
		return (this->endEchoTime - this->startEchoTime) / 58.0;
	}
};