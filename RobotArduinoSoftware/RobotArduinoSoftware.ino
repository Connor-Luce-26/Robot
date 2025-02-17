#include <Arduino.h>
#include "CollisionAvoidance.hpp"
CollisionAvoidance collisionAvoidance = CollisionAvoidance();
void setup()
{	
	collisionAvoidance.setupCollisionAvoidance();
}
void loop()
{
	collisionAvoidance.updateCollisionAvoidance();
}