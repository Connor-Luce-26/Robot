#include <Arduino.h>
#include "CollisionAvoidance.hpp"
// #include "E32900T20D.hpp"
#include "ManipulatorArm.hpp"
#include "Motor.hpp"
#include <HCSR04.h>
#define HCSR04_LEFT_TRIGGER_PIN 38
#define HCSR04_RIGHT_TRIGGER_PIN 40
#define HCSR04_BACK_TRIGGER_PIN 42
#define HCSR04_FRONT_TRIGGER_PIN 44
#define HCSR04_LEFT_ECHO_PIN 3
#define HCSR04_RIGHT_ECHO_PIN 2
#define HCSR04_BACK_ECHO_PIN 18
#define HCSR04_FRONT_ECHO_PIN 19
#define HCSR04_ECHO_TIMEOUT 25000 // microseconds
#define METERS_PER_CENTERMETER 0.01 // meters per centimeter
#define COLLISION_AVOIDANCE_FRONT_THRESHOLD_DISTANCE 0.2
#define COLLISION_AVOIDANCE_BACK_THRESHOLD_DISTANCE 0.2
#define COLLISION_AVOIDANCE_LEFT_THRESHOLD_DISTANCE 0.2
#define COLLISION_AVOIDANCE_RIGHT_THRESHOLD_DISTANCE 0.2
#define COLLISION_AVOIDANCE_FRONT_BIT 0
#define COLLISION_AVOIDANCE_BACK_BIT 1
#define COLLISION_AVOIDANCE_LEFT_BIT 2
#define COLLISION_AVOIDANCE_RIGHT_BIT 3
#define HCSR04_MAX_DISTANCE 4 // meters
// UltraSonicDistanceSensor hcsr04Front(HCSR04_FRONT_TRIGGER_PIN, HCSR04_FRONT_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
// UltraSonicDistanceSensor hcsr04Back(HCSR04_BACK_TRIGGER_PIN, HCSR04_BACK_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
// UltraSonicDistanceSensor hcsr04Left(HCSR04_LEFT_TRIGGER_PIN, HCSR04_LEFT_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
// UltraSonicDistanceSensor hcsr04Right(HCSR04_RIGHT_TRIGGER_PIN, HCSR04_RIGHT_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
Motor motorFrontRight(MOTOR_FRONT_RIGHT_FORWARD_PIN, MOTOR_FRONT_RIGHT_REVERSE_PIN);
Motor motorFrontLeft(MOTOR_FRONT_LEFT_FORWARD_PIN, MOTOR_FRONT_LEFT_REVERSE_PIN);
Motor motorBackRight(MOTOR_BACK_RIGHT_FORWARD_PIN, MOTOR_BACK_RIGHT_REVERSE_PIN);
Motor motorBackLeft(MOTOR_BACK_LEFT_FORWARD_PIN, MOTOR_BACK_LEFT_REVERSE_PIN);
// CollisionAvoidance collisionAvoidance;
// E32900T20D e32900T20D;
// ManipulatorArm manipulatorArm;
String command;
void setup()
{
	Serial.begin(9600);
	Serial.println("Starting Setup");
	// collisionAvoidance.setupCollisionAvoidance();
	// e32900T20D.setupE32900T20D();
	motorBackLeft.setupMotor();
	motorBackRight.setupMotor();
	motorFrontLeft.setupMotor();
	motorFrontRight.setupMotor();
	// manipulatorArm.setupManipulatorArm();
	Serial.println("Setup Complete");
}
void loop()
{
	// Serial.println("Starting Loop");
	// collisionAvoidance.updateCollisionAvoidance();
	// e32900T20D.write(collisionAvoidance.getCollisionAvoidanceString());
	// Serial.println(collisionAvoidance.getCollisionAvoidanceString());
	// command = e32900T20D.read();
	// Serial.print("f");
	// Serial.print(hcsr04Front.measureDistanceCm() * METERS_PER_CENTERMETER);
	// Serial.print("\n");
	// Serial.print("b");
	// Serial.print(hcsr04Back.measureDistanceCm() * METERS_PER_CENTERMETER);
	// Serial.print("\n");
	// Serial.print("l");
	// Serial.print(hcsr04Left.measureDistanceCm() * METERS_PER_CENTERMETER);
	// Serial.print("\n");
	// Serial.print("r");
	// Serial.print(hcsr04Right.measureDistanceCm() * METERS_PER_CENTERMETER);
	// Serial.print("\n");
	command = Serial.readStringUntil('\n');
	switch (command[0])
	{
	// case '1':
	// 	manipulatorArm.setWaistAngle(command.substring(1).toDouble());
	// 	break;
	// case '2':
	// 	manipulatorArm.setShoulderAngle(command.substring(1).toDouble());
	// 	break;
	// case '3':
	// 	manipulatorArm.setElbowAngle(command.substring(1).toDouble());
	// 	break;
	// case '4':
	// 	manipulatorArm.setWristRollAngle(command.substring(1).toDouble());
	// 	break;
	// case '5':
	// 	manipulatorArm.setWristPitchAngle(command.substring(1).toDouble());
	// 	break;
	// case '6':
	// 	manipulatorArm.setWristYawAngle(command.substring(1).toDouble());
	// 	break;
	// case 'o':
	// 	manipulatorArm.openGripper();
	// 	break;
	// case 'c':
	// 	manipulatorArm.closeGripper();
	// 	break;
	case 'x':
		// collisionAvoidance.setDesiredXPositionSetpoint(command.substring(1).toDouble());
		motorBackLeft.setThrottleLevel(-command.substring(1).toInt());
		motorBackRight.setThrottleLevel(command.substring(1).toInt());
		motorFrontLeft.setThrottleLevel(command.substring(1).toInt());
		motorFrontRight.setThrottleLevel(-command.substring(1).toInt());
		break;
	case 'y':
		// collisionAvoidance.setDesiredYPositionSetpoint(command.substring(1).toDouble());
		motorBackLeft.setThrottleLevel(command.substring(1).toInt());
		motorBackRight.setThrottleLevel(command.substring(1).toInt());
		motorFrontLeft.setThrottleLevel(command.substring(1).toInt());
		motorFrontRight.setThrottleLevel(command.substring(1).toInt());
		break;
	case 't':
		// collisionAvoidance.setDesiredThetaPositionSetpoint(command.substring(1).toDouble());
		motorBackLeft.setThrottleLevel(-command.substring(1).toInt());
		motorBackRight.setThrottleLevel(command.substring(1).toInt());
		motorFrontLeft.setThrottleLevel(-command.substring(1).toInt());
		motorFrontRight.setThrottleLevel(command.substring(1).toInt());
		break;
	default:
		break;
	}
	// collisionAvoidance.updateCollisionAvoidance();
	
}