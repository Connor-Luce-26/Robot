#pragma once
#include <Arduino.h>
#include "FIR.hpp"
#define MICROSECONDS_PER_SECOND 1000000.0 // microseconds per second
#define SOUND_SPEED 58 // inches per second
#define HCSR04_FIR_COEFFICIENTS {0.5, 0.5}
#define HCSR04_FIR_ORDER 2
constexpr double HCSR04FIRCoefficients[HCSR04_FIR_ORDER] = HCSR04_FIR_COEFFICIENTS;
class HCSR04
{
private:
	uint8_t triggerOutput;
	uint8_t echoInput;
	long startEchoTime;
	long endEchoTime;
	FIR fir;
	

public:
	HCSR04(uint8_t triggerOutput, uint8_t echoInput) : fir(HCSR04FIRCoefficients)
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
		return this->fir.update((this->endEchoTime - this->startEchoTime) / (2.0 * MICROSECONDS_PER_SECOND) * SOUND_SPEED);
	}
};