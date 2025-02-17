#include <Arduino.h>
#include <SoftwareSerial.h>
#define TRANSCEIVER_TX_PIN 18
#define TRANSCEIVER_RX_PIN 19
#define SERIAL_BAUD 9600
#define TRANSCEIVER_BAUD 9600
#define TRANSCEIVER_M0_PIN 2
#define TRANSCEIVER_M1_PIN 3
#define TRANSCEIVER_AUX_PIN 4
SoftwareSerial transceiverSerial(TRANSCEIVER_RX_PIN, TRANSCEIVER_TX_PIN);
void setup() 
{
  Serial.begin(SERIAL_BAUD);
  Serial.println("Starting Robot Transceiver Software Setup");
  transceiverSerial.begin(TRANSCEIVER_BAUD);
  pinMode(TRANSCEIVER_M0_PIN, OUTPUT);
  pinMode(TRANSCEIVER_M1_PIN, OUTPUT);
  pinMode(TRANSCEIVER_AUX_PIN, INPUT);
  digitalWrite(TRANSCEIVER_M0_PIN, LOW);
  digitalWrite(TRANSCEIVER_M1_PIN, LOW);
  Serial.println("Robot Transceiver Software Setup Complete");
}
void loop()
{
  if (transceiverSerial.available()) {
    char data = transceiverSerial.read();
    Serial.print(data);
  }
  if (Serial.available()) {
    char data = Serial.read();
    transceiverSerial.print(data);
  }
}
