#include <Arduino.h>
#include "PositionControl.hpp"
PositionControl positionControl;
void setup()
{	
	positionControl.setupPositionControl();
	positionControl.setThetaPositionSetpoint(0);
	positionControl.setXPositionSetpoint(0);
	positionControl.setYPositionSetpoint(0);
}
void loop()
{
	positionControl.updatePositionControl();
}