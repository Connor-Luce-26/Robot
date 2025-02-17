#pragma once
#include <Arduino.h>
#include <Servo.h>
#define WAIST_SERVO_PIN 22
#define SHOULDER_SERVO_PIN 24
#define ELBOW_SERVO_PIN 26
#define WRIST_ROLL_SERVO_PIN 28
#define WRIST_PITCH_SERVO_PIN 30
#define WRIST_YAW_SERVO_PIN 32
#define LEFT_GRIPPER_SERVO_PIN 34
#define RIGHT_GRIPPER_SERVO_PIN 36
#define LEFT_GRIPPER_OPEN_ANGLE 0
#define LEFT_GRIPPER_CLOSE_ANGLE 90
#define RIGHT_GRIPPER_OPEN_ANGLE 180
#define RIGHT_GRIPPER_CLOSE_ANGLE 90
#define SETUP_WAIST_ANGLE 90
#define SETUP_SHOULDER_ANGLE 90
#define SETUP_ELBOW_ANGLE 90
#define SETUP_WRIST_ROLL_ANGLE 90
#define SETUP_WRIST_PITCH_ANGLE 90
#define SETUP_WRIST_YAW_ANGLE 90
class ManipulatorArm
{
private:
	Servo servoWaist;
	Servo servoShoulder;
	Servo servoElbow;
	Servo servoWristRoll;
	Servo servoWristPitch;
	Servo servoWristYaw;
	Servo servoLeftGripper;
	Servo servoRightGripper;

public:
	ManipulatorArm()
	{
	}
	~ManipulatorArm()
	{
	}
	void setWaistAngle(double angle)
	{
		this->servoWaist.write(angle);
	}
	void setShoulderAngle(double angle)
	{
		this->servoShoulder.write(angle);
	}
	void setElbowAngle(double angle)
	{
		this->servoElbow.write(angle);
	}
	void setWristRollAngle(double angle)
	{
		this->servoWristRoll.write(angle);
	}
	void setWristPitchAngle(double angle)
	{
		this->servoWristPitch.write(angle);
	}
	void setWristYawAngle(double angle)
	{
		this->servoWristYaw.write(angle);
	}
	void setLeftGripperAngle(double angle)
	{
		this->servoLeftGripper.write(angle);
	}
	void setRightGripperAngle(double angle)
	{
		this->servoRightGripper.write(angle);
	}
	void openGripper()
	{
		this->servoLeftGripper.write(LEFT_GRIPPER_OPEN_ANGLE);
		this->servoRightGripper.write(RIGHT_GRIPPER_OPEN_ANGLE);
	}
	void closeGripper()
	{
		this->servoLeftGripper.write(LEFT_GRIPPER_CLOSE_ANGLE);
		this->servoRightGripper.write(RIGHT_GRIPPER_CLOSE_ANGLE);
	}
	void setupManipulatorArm()
	{
		this->servoWaist.attach(WAIST_SERVO_PIN);
		this->servoShoulder.attach(SHOULDER_SERVO_PIN);
		this->servoElbow.attach(ELBOW_SERVO_PIN);
		this->servoWristRoll.attach(WRIST_ROLL_SERVO_PIN);
		this->servoWristPitch.attach(WRIST_PITCH_SERVO_PIN);
		this->servoWristYaw.attach(WRIST_YAW_SERVO_PIN);
		this->servoLeftGripper.attach(LEFT_GRIPPER_SERVO_PIN);
		this->servoRightGripper.attach(RIGHT_GRIPPER_SERVO_PIN);
		this->openGripper();
		this->setWaistAngle(SETUP_WAIST_ANGLE);
		this->setShoulderAngle(SETUP_SHOULDER_ANGLE);
		this->setElbowAngle(SETUP_ELBOW_ANGLE);
		this->setWristRollAngle(SETUP_WRIST_ROLL_ANGLE);
		this->setWristPitchAngle(SETUP_WRIST_PITCH_ANGLE);
		this->setWristYawAngle(SETUP_WRIST_YAW_ANGLE);
	}
};