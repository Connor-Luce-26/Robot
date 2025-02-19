#include <Arduino.h>
#include "CollisionAvoidance.hpp"
#include "E32900T20D.hpp"
#include "ManipulatorArm.hpp"
// CollisionAvoidance collisionAvoidance;
// E32900T20D e32900T20D;
// ManipulatorArm manipulatorArm;
// Motor motorFrontRight = Motor(MOTOR_FRONT_RIGHT_FORWARD_PIN, MOTOR_FRONT_RIGHT_REVERSE_PIN);
// Motor motorFrontLeft = Motor(MOTOR_FRONT_LEFT_FORWARD_PIN, MOTOR_FRONT_LEFT_REVERSE_PIN);
// Motor motorBackRight = Motor(MOTOR_BACK_RIGHT_FORWARD_PIN, MOTOR_BACK_RIGHT_REVERSE_PIN);
// Motor motorBackLeft = Motor(MOTOR_BACK_LEFT_FORWARD_PIN, MOTOR_BACK_LEFT_REVERSE_PIN);
// String command;
void setup()
{	
	Serial.begin(115200);
	Serial.println("Starting Setup");
	// collisionAvoidance.setupCollisionAvoidance();
	// e32900T20D.setupE32900T20D();
	// manipulatorArm.setupManipulatorArm();
	// motorFrontRight.setupMotor();
	// motorFrontLeft.setupMotor();
	// motorBackRight.setupMotor();
	// motorBackLeft.setupMotor();
	Serial.println("Setup Complete");
	
}
void loop()
{	
	Serial.println("Starting Loop");
	// collisionAvoidance.updateCollisionAvoidance();
  	// Serial.println(collisionAvoidance.getCollisionAvoidanceString());
	// command = Serial.readStringUntil('\n');
	// e32900T20D.write(collisionAvoidance.getCollisionAvoidanceString());
	// command = e32900T20D.read();
	// switch (command[0])
	// {
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
	// case 'x':
	// 	collisionAvoidance.setDesiredXPositionSetpoint(command.substring(1).toDouble());
	// 	break;
	// case 'y':
	// 	collisionAvoidance.setDesiredYPositionSetpoint(command.substring(1).toDouble());
	// 	break;
	// case 't':
	// 	collisionAvoidance.setDesiredThetaPositionSetpoint(command.substring(1).toDouble());
	// 	break;
	// default:
	// 	break;
	// }
	// collisionAvoidance.updateCollisionAvoidance();
	// motorFrontRight.setThrottleLevel(255);
	// motorFrontLeft.setThrottleLevel(255);
	// motorBackRight.setThrottleLevel(255);
	// motorBackLeft.setThrottleLevel(255);
	analogWrite(MOTOR_FRONT_RIGHT_FORWARD_PIN, 255);
}