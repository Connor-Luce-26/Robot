class FIR
{
private:
	uint8_t order;
	double *coefficients;
	double *buffer;
public:
	FIR(double *coefficients) 
	{
		this->order = sizeof(coefficients) - 1;
		this->coefficients = new double[this->order];
		this->buffer = new double[this->order];
		for (int i = 0; i < this->order; i++)
		{
			this->coefficients[i] = coefficients[i];
			this->buffer[i] = 0.0;
		}
	}
	~FIR()
	{
		delete[] this->coefficients;
		delete[] this->buffer;
	}
	double update(double input)
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
};