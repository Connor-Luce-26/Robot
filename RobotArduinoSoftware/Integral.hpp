#pragma once
#include <Arduino.h>
#define MICROSECONDS_PER_SECOND 1000000.0
class Integral
{
private:
	long time;
	double value;
	double input;
public:
	Integral()
	{
		this->time = micros();
		this->value = 0.0;
		this->input = 0.0;
	}
	~Integral()
	{
	}
	double updateIntegral(double input)
	{
		long currentTime = micros();
		double dt = (currentTime - this->time) / MICROSECONDS_PER_SECOND;
		this->value += (this->input + input) / 2 * dt;
		this->time = currentTime;
		this->input = input;
		return this->value;
	}
	double getIntegralValue()
	{
		return this->value;
	}
};