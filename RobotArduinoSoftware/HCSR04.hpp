#pragma once
#include <Arduino.h>
#define MICROSECONDS_PER_SECOND 1000000.0 // microseconds per second
#define SOUND_SPEED 343.0 // meters per second
class HCSR04
{
private:
	uint8_t triggerOutput;
	uint8_t echoInput;
	long startEchoTime;
	long endEchoTime;

public:
	HCSR04(uint8_t triggerOutput, uint8_t echoInput)
	{
		this->triggerOutput = triggerOutput;
		this->echoInput = echoInput;
		pinMode(this->triggerOutput, OUTPUT);
		pinMode(this->echoInput, INPUT);
		digitalWrite(this->triggerOutput, LOW);
	}
	~HCSR04()
	{
	}
	void trigger()
	{
		digitalWrite(this->triggerOutput, HIGH);
		delayMicroseconds(10);
		digitalWrite(this->triggerOutput, LOW);
		this->echo();
	}
	void echo()
	{
		while (digitalRead(this->echoInput) == LOW);
        this->startEchoTime = micros();
        while (digitalRead(this->echoInput) == HIGH);
        this->endEchoTime = micros();
	}
	double getDistance()
	{
		this->trigger();
		return (this->endEchoTime - this->startEchoTime) / (2.0 * MICROSECONDS_PER_SECOND) / SOUND_SPEED;
	}
};