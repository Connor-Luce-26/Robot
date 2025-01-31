#pragma once
#include <cstdint>
#include <vector>
#define TIMER_1_START 0
#define TRIGGER_PULSE_WIDTH 10
#define TRIGGER_TIMER_SCALER 16
std::vector<HCSR04> HCSR04s;
void setupHCSR04()
{
	TMSK1 |= (1 << ICIE1);
	TCCR1A = 0;
	TCCR1B |= (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	TCNT1 = TIMER_1_START;
	OCR1A = TRIGGER_PULSE_WIDTH * TRIGGER_TIMER_SCALER;
	sei();
}
class HCSR04
{
private:
	char triggerPort;
	uint8_t triggerBit;
	uint8_t echoInterrupt;
	uint16_t echoPulseWidth;
	bool echoActive = false;
	double distance = 0.0;
public:
	HCSR04(char triggerPort, uint8_t triggerBit, uint8_t echoInterrupt)
	{
		this->frequency = frequency;
		this->triggerPort = triggerPort;
		this->triggerBit = triggerBit;
		this->echoInterrupt = echoInterrupt;
		switch (this->echoInterrupt)
		{
		case 0:
			EICRA |= (1 << ISC00);
			EICRA &= ~(1 << ISC01);
			break;
		case 1:
			EICRA |= (1 << ISC10);
			EICRA &= ~(1 << ISC11);
			break;
		case 2:
			EICRA |= (1 << ISC20);
			EICRA &= ~(1 << ISC21);
			break;
		case 3:
			EICRA |= (1 << ISC30);
			EICRA &= ~(1 << ISC31);
			break;
		case 4:
			EICRB |= (1 << ISC40);
			EICRB &= ~(1 << ISC41);
			break;
		case 5:
			EICRB |= (1 << ISC50);
			EICRB &= ~(1 << ISC51);
			break;
		case 6:
			EICRB |= (1 << ISC60);
			EICRB &= ~(1 << ISC61);
			break;
		case 7:
			EICRB |= (1 << ISC70);
			EICRB &= ~(1 << ISC71);
			break;
		default:
			break;
		}
		sei();
		switch (this->triggerPort)
		{
		case 'A':
			DDRA |= (1 << this->triggerBit);
			break;
		case 'B':
			DDRB |= (1 << this->triggerBit);
			break;
		case 'C':
			DDRC |= (1 << this->triggerBit);
			break;
		case 'D':
			DDRD |= (1 << this->triggerBit);
			break;
		case 'E':
			DDRE |= (1 << this->triggerBit);
			break;
		case 'F':
			DDRF |= (1 << this->triggerBit);
			break;
		case 'G':
			DDRG |= (1 << this->triggerBit);
			break;
		case 'H':
			DDRH |= (1 << this->triggerBit);
			break;
		case 'J':
			DDRJ |= (1 << this->triggerBit);
			break;
		case 'K':
			DDRK |= (1 << this->triggerBit);
			break;
		case 'L':
			DDRL |= (1 << this->triggerBit);
			break;
		default:
			break;
		}
	}
	void startTrigger()
	{
		switch (this->triggerPort)
		{
		case 'A':
			PORTA |= (1 << this->triggerBit);
			break;
		case 'B':
			PORTB |= (1 << this->triggerBit);
			break;
		case 'C':
			PORTC |= (1 << this->triggerBit);
			break;
		case 'D':
			PORTD |= (1 << this->triggerBit);
			break;
		case 'E':
			PORTE |= (1 << this->triggerBit);
			break;
		case 'F':
			PORTF |= (1 << this->triggerBit);
			break;
		case 'G':
			PORTG |= (1 << this->triggerBit);
			break;
		case 'H':
			PORTH |= (1 << this->triggerBit);
			break;
		case 'J':
			PORTJ |= (1 << this->triggerBit);
			break;
		case 'K':
			PORTK |= (1 << this->triggerBit);
			break;
		case 'L':
			PORTL |= (1 << this->triggerBit);
			break;
		default:
			break;
		}
		TCNT1 = TIMER_1_START;
	}
	void endTrigger()
	{
		switch (this->triggerPort)
		{
		case 'A':
			PORTA &= ~(1 << this->triggerBit);
			break;
		case 'B':
			PORTB &= ~(1 << this->triggerBit);
			break;
		case 'C':
			PORTC &= ~(1 << this->triggerBit);
			break;
		case 'D':
			PORTD &= ~(1 << this->triggerBit);
			break;
		case 'E':
			PORTE &= ~(1 << this->triggerBit);
			break;
		case 'F':
			PORTF &= ~(1 << this->triggerBit);
			break;
		case 'G':
			PORTG &= ~(1 << this->triggerBit);
			break;
		case 'H':
			PORTH &= ~(1 << this->triggerBit);
			break;
		case 'J':
			PORTJ &= ~(1 << this->triggerBit);
			break;
		case 'K':
			PORTK &= ~(1 << this->triggerBit);
			break;
		case 'L':
			PORTL &= ~(1 << this->triggerBit);
			break;
		default:
			break;
		}
		this->startEcho();
	}
	void startEcho()
	{
		this->echoActive = true;
	}
	void endEcho(uint16_t echoPulseWidth, uint8_t echoInterrupt)
	{
		if (this->echoActive && (this->echoInterrupt == echoInterrupt))
		{
			this->echoPulseWidth = echoPulseWidth;
			this->distance = this->echoPulseWidth / 58.0;
			this->echoActive = false;
		}
	}
	double getDistance()
	{
		return this->distance;
	}
};
void endTrigger()
{
	for (int i = 0; i < HCSR04s.size(); i++)
	{
		HCSR04s[i].endTrigger();
	}
}
void endEcho(uint16_t echoPulseWidth, uint16_t echoInterrupt)
{
	for (int i = 0; i < HCSR04s.size(); i++)
	{
		HCSR04s[i].endEcho(echoPulseWidth, echoInterrupt);
	}
}
ISR(TIMER1_COMPA_vect)
{
	endTrigger();
}
ISR(INT0_vect)
{
	endEcho(time, 0);
}
ISR(INT1_vect)
{
	endEcho(time, 1);
}
ISR(INT2_vect)
{
	endEcho(time, 2);
}
ISR(INT3_vect)
{
	endEcho(time, 3);
}
ISR(INT4_vect)
{
	endEcho(time, 4);
}
ISR(INT5_vect)
{
	endEcho(time, 5);
}
ISR(INT6_vect)
{
	endEcho(time, 6);
}
ISR(INT7_vect)
{
	endEcho(time, 7);
}