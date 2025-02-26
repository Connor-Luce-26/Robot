#pragma once

#include "PositionControl.hpp"
#include <HCSR04.h>
#include <Arduino.h>
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
class CollisionAvoidance
{
private:
	UltraSonicDistanceSensor hcsr04Front;
	UltraSonicDistanceSensor hcsr04Back;
	UltraSonicDistanceSensor hcsr04Left;
	UltraSonicDistanceSensor hcsr04Right;
	PositionControl positionControl;
	double frontDistance;
	double backDistance;
	double leftDistance;
	double rightDistance;
	uint8_t collisionDirection;
	double desiredXPositionSetpoint;
	double desiredYPositionSetpoint;
	double desiredThetaPositionSetpoint;

public:
	CollisionAvoidance()
	{
		this->hcsr04Front = UltraSonicDistanceSensor(HCSR04_FRONT_TRIGGER_PIN, HCSR04_FRONT_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
		this->hcsr04Back = UltraSonicDistanceSensor(HCSR04_BACK_TRIGGER_PIN, HCSR04_BACK_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
		this->hcsr04Left = UltraSonicDistanceSensor(HCSR04_LEFT_TRIGGER_PIN, HCSR04_LEFT_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
		this->hcsr04Right = UltraSonicDistanceSensor(HCSR04_RIGHT_TRIGGER_PIN, HCSR04_RIGHT_ECHO_PIN, HCSR04_ECHO_TIMEOUT, HCSR04_MAX_DISTANCE * METERS_PER_CENTERMETER);
	}
	~CollisionAvoidance()
	{
	}
	void setupCollisionAvoidance()
	{
		Serial.println("Setting up Collision Avoidance");
		this->positionControl.setupPositionControl();
		Serial.println("Collision Avoidance Setup Complete");
	}
	void checkCollision()
	{
		this->collisionDirection = 0;
		if (this->frontDistance <= COLLISION_AVOIDANCE_FRONT_THRESHOLD_DISTANCE)
		{
			this->collisionDirection |= (1 << COLLISION_AVOIDANCE_FRONT_BIT);
		}
		if (this->backDistance <= COLLISION_AVOIDANCE_BACK_THRESHOLD_DISTANCE)
		{
			this->collisionDirection |= (1 << COLLISION_AVOIDANCE_BACK_BIT);
		}
		if (this->leftDistance < COLLISION_AVOIDANCE_LEFT_THRESHOLD_DISTANCE)
		{
			this->collisionDirection |= (1 << COLLISION_AVOIDANCE_LEFT_BIT);
		}
		if (this->rightDistance < COLLISION_AVOIDANCE_RIGHT_THRESHOLD_DISTANCE)
		{
			this->collisionDirection |= (1 << COLLISION_AVOIDANCE_RIGHT_BIT);
		}
	}
	void changePositionControlSetpoints()
	{
		if ((this->collisionDirection & (1 << COLLISION_AVOIDANCE_FRONT_BIT)) && !(this->collisionDirection & (1 << COLLISION_AVOIDANCE_BACK_BIT)))
		{
			this->desiredYPositionSetpoint = this->positionControl.getYPositionSetpoint();
			this->positionControl.setYPositionSetpoint(this->positionControl.getYPosition() - (COLLISION_AVOIDANCE_FRONT_THRESHOLD_DISTANCE - this->frontDistance));
		}
		if ((this->collisionDirection & (1 << COLLISION_AVOIDANCE_BACK_BIT)) && !(this->collisionDirection & (1 << COLLISION_AVOIDANCE_FRONT_BIT)))
		{
			this->desiredYPositionSetpoint = this->positionControl.getYPositionSetpoint();
			this->positionControl.setYPositionSetpoint(this->positionControl.getYPosition() + (COLLISION_AVOIDANCE_BACK_THRESHOLD_DISTANCE - this->backDistance));
		}
		if ((this->collisionDirection & (1 << COLLISION_AVOIDANCE_LEFT_BIT)) && !(this->collisionDirection & (1 << COLLISION_AVOIDANCE_RIGHT_BIT)))
		{
			this->desiredXPositionSetpoint = this->positionControl.getXPositionSetpoint();
			this->positionControl.setXPositionSetpoint(this->positionControl.getXPosition() + (COLLISION_AVOIDANCE_LEFT_THRESHOLD_DISTANCE - this->leftDistance));
		}
		if ((this->collisionDirection & (1 << COLLISION_AVOIDANCE_RIGHT_BIT)) && !(this->collisionDirection & (1 << COLLISION_AVOIDANCE_LEFT_BIT)))
		{
			this->desiredXPositionSetpoint = this->positionControl.getXPositionSetpoint();
			this->positionControl.setXPositionSetpoint(this->positionControl.getXPosition() - (COLLISION_AVOIDANCE_RIGHT_THRESHOLD_DISTANCE - this->rightDistance));
		}
		if ((this->collisionDirection & (1 << COLLISION_AVOIDANCE_FRONT_BIT)) && (this->collisionDirection & (1 << COLLISION_AVOIDANCE_BACK_BIT)))
		{
			this->desiredYPositionSetpoint = this->positionControl.getYPositionSetpoint();
			this->positionControl.setYPositionSetpoint(this->positionControl.getYPosition() + (this->frontDistance - this->backDistance));
		}
		if ((this->collisionDirection & (1 << COLLISION_AVOIDANCE_LEFT_BIT)) && (this->collisionDirection & (1 << COLLISION_AVOIDANCE_RIGHT_BIT)))
		{
			this->desiredXPositionSetpoint = this->positionControl.getXPositionSetpoint();
			this->positionControl.setXPositionSetpoint(this->positionControl.getXPosition() - (this->leftDistance - this->rightDistance));
		}
		if (this->collisionDirection == 0)
		{
			this->positionControl.setXPositionSetpoint(this->desiredXPositionSetpoint);
			this->positionControl.setYPositionSetpoint(this->desiredYPositionSetpoint);
		}
		this->positionControl.setThetaPositionSetpoint(this->desiredThetaPositionSetpoint);
		this->positionControl.updatePositionControl();
	}
	void updateCollisionAvoidance()
	{
		this->frontDistance = this->hcsr04Front.measureDistanceCm() * METERS_PER_CENTERMETER;
		this->backDistance = this->hcsr04Back.measureDistanceCm() * METERS_PER_CENTERMETER;
		this->leftDistance = this->hcsr04Left.measureDistanceCm() * METERS_PER_CENTERMETER;
		this->rightDistance = this->hcsr04Right.measureDistanceCm() * METERS_PER_CENTERMETER;
		this->positionControl.updateSensorData();
		this->checkCollision();
		this->changePositionControlSetpoints();
	}
	void setDesiredXPositionSetpoint(double desiredXPositionSetpoint)
	{
		this->desiredXPositionSetpoint = desiredXPositionSetpoint;
	}
	void setDesiredYPositionSetpoint(double desiredYPositionSetpoint)
	{
		this->desiredYPositionSetpoint = desiredYPositionSetpoint;
	}
	void setDesiredThetaPositionSetpoint(double desiredThetaPositionSetpoint)
	{
		this->desiredThetaPositionSetpoint = desiredThetaPositionSetpoint;
	}
	String getCollisionAvoidanceString()
	{
		String data = "";
		data += "f ";
		data += String(this->frontDistance);
		data += " \n";
		data += "b ";
		data += String(this->backDistance);
		data += " \n";
		data += "l ";
		data += String(this->leftDistance);
		data += " \n";
		data += " r";
		data += String(this->rightDistance);
		data += " \n";
		data += "x ";
		data += String(this->positionControl.getXPosition());
		data += " \n";
		data += "y ";
		data += String(this->positionControl.getYPosition());
		data += " \n";
		data += "t ";
		data += String(this->positionControl.getThetaPosition());
		data += " \n";
	}
};