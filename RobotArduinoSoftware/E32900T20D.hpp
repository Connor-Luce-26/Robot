#pragma once
#include <Arduino.h>
#define TRANSCEIVER_BAUD 9600
#define TRANSCEIVER_M0_PIN 2
#define TRANSCEIVER_M1_PIN 3
#define TRANSCEIVER_AUX_PIN 4
class E32900T20D
{
private:
public:
	E32900T20D()
	{
	}
	~E32900T20D()
	{
	}
	void setupE32900T20D()
	{
		Serial.println("Starting E32900T20D Setup");
		Serial2.begin(TRANSCEIVER_BAUD);
		pinMode(TRANSCEIVER_M0_PIN, OUTPUT);
		pinMode(TRANSCEIVER_M1_PIN, OUTPUT);
		pinMode(TRANSCEIVER_AUX_PIN, INPUT);
		digitalWrite(TRANSCEIVER_M0_PIN, LOW);
		digitalWrite(TRANSCEIVER_M1_PIN, LOW);
		Serial.println("E32900T20D Setup Complete");
	}
	void write(String data)
	{
		if (Serial2.availableForWrite() > data.length())
		{
			Serial2.print(data);
		}
		else
		{
			Serial.println("Transceiver Buffer Full");
		}
	}
	String read()
	{
		if (Serial2.available() > 0)
		{
			return Serial2.readStringUntil('\n');
		}
		else
		{
			Serial.println("Transceiver Buffer Empty");
			return "";
		}
	}
};
