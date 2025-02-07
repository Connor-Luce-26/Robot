#pragma once
#include "Vector.hpp"
#include "FIR.hpp"
class VectorFIR
{
private:
	FIR *fir;
public:
	VectorFIR(double *coefficients, uint8_t vectorSize)
	{
		for (int i = 0; i < vectorSize; i++)
		{
			this->fir[i] = new FIR(coefficients);
		}

	}
	~VectorFIR()
	{
		delete this->fir;
	}
	Vector update(Vector input)
	{
		ArrayList<double> result;
		for (int i = 0; i < input.size(); i++)
		{
			result.push_back(this->fir[i].update(input.getValue(i)));
		}
		return Vector(result, input.getShape());
	}
};