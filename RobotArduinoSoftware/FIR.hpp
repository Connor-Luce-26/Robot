#pragma once

class FIR
{
private:
	uint8_t order;
	double *coefficients;
	double *buffer;
public:
	FIR()
	{
	}
	FIR(uint8_t order)
	{
		this->order = order;
		this->coefficients = new double[this->order];
		this->buffer = new double[this->order];
		for (int i = 0; i < this->order; i++)
		{
			this->coefficients[i] = 1.0 / this->order;
			this->buffer[i] = 0.0;
		}
	}
	~FIR()
	{
		delete[] this->coefficients;
		delete[] this->buffer;
	}
	double setCoefficients(const double coefficients[])
	{
		this->order = sizeof(coefficients) / sizeof(coefficients[0]);
		this->coefficients = new double[this->order];
		for (int i = 0; i < this->order; i++)
		{
			this->coefficients[i] = coefficients[i];
		}
	}
	FIR(const double coefficients[])
	{
		this->setCoefficients(coefficients);
	}
	double updateFIR(double input)
	{
		double output = 0.0;
		for (int i = this->order - 1; i > 0; i--)
		{
			this->buffer[i] = this->buffer[i - 1];
			output += this->coefficients[i] * this->buffer[i];
		}
		this->buffer[0] = input;
		output += this->coefficients[0] * this->buffer[0];
		return output;
	}
	double getOutput()
	{
		double output = 0.0;
		for (int i = this->order - 1; i > 0; i--)
		{
			output += this->coefficients[i] * this->buffer[i];
		}
		output += this->coefficients[0] * this->buffer[0];
		return output;
	}
};