#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>
#define TRANSCEIVER_BAUD 9600
#define TRANSCEIVER_M0_PIN 2
#define TRANSCEIVER_M1_PIN 3
#define TRANSCEIVER_AUX_PIN 4
#define TRANSCEIVER_RX_PIN 17
#define TRANSCEIVER_TX_PIN 16
class E32900T20D
{
private:
	SoftwareSerial E32900T20DSerial = SoftwareSerial(TRANSCEIVER_RX_PIN, TRANSCEIVER_TX_PIN);;
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
		this->E32900T20DSerial.begin(TRANSCEIVER_BAUD);
		pinMode(TRANSCEIVER_M0_PIN, OUTPUT);
		pinMode(TRANSCEIVER_M1_PIN, OUTPUT);
		pinMode(TRANSCEIVER_AUX_PIN, INPUT);
		digitalWrite(TRANSCEIVER_M0_PIN, LOW);
		digitalWrite(TRANSCEIVER_M1_PIN, LOW);
		Serial.println("E32900T20D Setup Complete");

	}
	void write(String data)
	{
		if (this->E32900T20DSerial.availableForWrite() > data.length())
		{
			this->E32900T20DSerial.write(data.c_str());
		}
		else
		{
			Serial.println("Transceiver Buffer Full");
		}
	}
	String read()
	{
		if (this->E32900T20DSerial.available() > 0)
		{
			return this->E32900T20DSerial.readStringUntil('\n');
		}
		else
		{
			Serial.println("Transceiver Buffer Empty");
			return "";
		}
	}
};
