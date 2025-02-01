#include "Arduino.h"
#include "HCSR04.hpp"
void setup()
{
	setupHCSR04();
	HCSR04s.add(HCSR04('D', 2, 0));
	HCSR04s[0].startTrigger();
}
void loop()
{
	HCSR04s[0].getDistance();
}