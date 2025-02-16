#pragma once
#include <Arduino.h>
#define MICROSECONDS_PER_SECOND 1000000.0 // microseconds per second
#define SOUND_SPEED 343.0 // meters per second
#define HCSR04_LEFT_TRIGGER_PIN 38
#define HCSR04_RIGHT_TRIGGER_PIN 40
#define HCSR04_BACK_TRIGGER_PIN 42
#define HCSR04_FRONT_TRIGGER_PIN 44
#define HCSR04_LEFT_ECHO_PIN 3
#define HCSR04_RIGHT_ECHO_PIN 2
#define HCSR04_BACK_ECHO_PIN 18
#define HCSR04_FRONT_ECHO_PIN 19
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
	}
	~HCSR04()
	{
	}
	void setupHCSR04()
	{
		pinMode(this->triggerPin, OUTPUT);
		pinMode(this->echoPin, INPUT);
		digitalWrite(this->triggerPin, LOW);
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
		return (this->endEchoTime - this->startEchoTime) / (2.0 * MICROSECONDS_PER_SECOND) * SOUND_SPEED;
	}
};