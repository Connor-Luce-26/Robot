#pragma once
#include <Arduino.h>
#define MICROSECONDS_PER_SECOND 1000000.0 // microseconds per second
#define SOUND_SPEED 343.0 // meters per second
#define LEFT_TRIGGER_PIN 38
#define RIGHT_TRIGGER_PIN 40
#define BACK_TRIGGER_PIN 42
#define FRONT_TRIGGER_PIN 44
#define LEFT_ECHO_PIN 3
#define RIGHT_ECHO_PIN 2
#define BACK_ECHO_PIN 18
#define FRONT_ECHO_PIN 19
class HCSR04
{
private:
	uint8_t triggerPin;
	uint8_t echoPin;
	long startEchoTime;
	long endEchoTime;

public:
	HCSR04(uint8_t triggerPin, uint8_t echoPin)
	{
		this->triggerPin = triggerPin;
		this->echoPin = echoPin;
		pinMode(this->triggerPin, OUTPUT);
		pinMode(this->echoPin, INPUT);
		digitalWrite(this->triggerPin, LOW);
	}
	~HCSR04()
	{
	}
	void trigger()
	{
		digitalWrite(this->triggerPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(this->triggerPin, LOW);
		this->echo();
	}
	void echo()
	{
		while (digitalRead(this->echoPin) == LOW);
        this->startEchoTime = micros();
        while (digitalRead(this->echoPin) == HIGH);
        this->endEchoTime = micros();
	}
	double getDistance()
	{
		this->trigger();
		return (this->endEchoTime - this->startEchoTime) / (2.0 * MICROSECONDS_PER_SECOND) / SOUND_SPEED;
	}
};