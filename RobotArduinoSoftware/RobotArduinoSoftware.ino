#include <Arduino.h>
#include "Motor.hpp"
Motor motorFrontRight(MOTOR_FRONT_RIGHT_FORWARD_PIN, MOTOR_FRONT_RIGHT_REVERSE_PIN);
Motor motorFrontLeft(MOTOR_FRONT_LEFT_FORWARD_PIN, MOTOR_FRONT_LEFT_REVERSE_PIN);
Motor motorBackRight(MOTOR_BACK_RIGHT_FORWARD_PIN, MOTOR_BACK_RIGHT_REVERSE_PIN);
Motor motorBackLeft(MOTOR_BACK_LEFT_FORWARD_PIN, MOTOR_BACK_LEFT_REVERSE_PIN);
String command;
void setup()
{
	Serial.begin(9600);
	Serial.println("Starting Setup");
	motorBackLeft.setupMotor();
	motorBackRight.setupMotor();
	motorFrontLeft.setupMotor();
	motorFrontRight.setupMotor();
	Serial.println("Setup Complete");
}
void loop()
{
	command = Serial.readStringUntil('\n');
	switch (command[0])
	{
	case '1':
		motorFrontRight.setThrottleLevel(command.substring(1).toInt());
		break;
	case '2':
		motorFrontLeft.setThrottleLevel(command.substring(1).toInt());
		break;
	case '3':
		motorBackLeft.setThrottleLevel(command.substring(1).toInt());
		break;
	case '4':
		motorBackRight.setThrottleLevel(command.substring(1).toInt());
		break;
	default:
		break;
	}
}