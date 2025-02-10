#pragma once
#include <Arduino.h>
#include "Integral.hpp"
#include "Vector.hpp"
class VectorIntegral
{
private:
	Integral* integrals
public:
	VectorIntegral(uint8_t vectorSize)
	{
		this->integrals = new Integral[vectorSize];
	}
	~Integral()
	{
	}
	Vector update(Vector input)
	{
		ArrayList<double> result;
		for (int i = 0; i < input.size(); i++)
		{
			result.add(this->integrals[i].update(input.getValue(i)));
		}
		return Vector(result, input.getShape());
	}
	Vector getValue()
	{
		ArrayList<double> result;
		for (int i = 0; i < input.size(); i++)
		{
			result.add(this->integrals[i].getValue());
		}
		return Vector(result, input.getShape());
	}
};