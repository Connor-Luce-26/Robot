#pragma once
#include "ArrayList.hpp"
#include "String.h"
#include "UTF8Symbols.hpp"
// Class representing a generic Vector
class Vector
{
private:
	// ArrayList to store the values of the Vector
	ArrayList<double> value;
	// Shape of the Vector
	String shape;

public:
	// Constructor that initializes the Vector with a given ArrayList of values and a given shape
	Vector(ArrayList<double> value, String shape)
	{
		this->value = value;
		this->shape = shape;
	}
	// Constructor that initializes the Vector with a given shape and size, and fills it with a given value
	Vector(int size, double value, String shape)
	{
		this->shape = shape;
		for (int i = 0; i < size; i++)
		{
			this->value.add(value);
		}
	}
	// Constructor that initializes the Vector with a given size and fills it with zeros
	Vector(int size, String shape) : Vector(size, 0.0, shape)
	{
	}
	// Default constructor that initializes an empty Vector
	Vector()
	{
		this->value = ArrayList<double>();
		this->shape = "column";
	}
	// Destructor
	~Vector()
	{
	}
	// Get the size of the Vector
	int getSize()
	{
		return this->value.getSize();
	}
	// Get the value of the Vector
	ArrayList<double> getValue()
	{
		return this->value;
	}
	// Get the value of the Vector at a given index
	double getValue(int index)
	{
		return this->value[index];
	}
	// Get the shape of the Vector
	String getShape()
	{
		return this->shape;
	}
	// Set the value of the Vector
	void setValue(ArrayList<double> value)
	{
		this->value = value;
	}
	// Set the value of the Vector at a given index
	void setValue(int index, double value)
	{
		this->value[index] = value;
	}
	// Set the shape of the Vector
	void setShape(String shape)
	{
		this->shape = shape;
	}
	// Method to overload the + operator to add two Vectors
	Vector operator+(Vector other)
	{
		this->ensureEqualSize(other);
		this->ensureEqualShape(other);
		ArrayList<double> result;
		for (int i = 0; i < this->getSize(); i++)
		{
			result.add(this->getValue(i) + other.getValue(i));
		}
		return Vector(result, this->shape);
	}
	// Method to overload the * operator to multiply a Vector by a scalar
	Vector operator*(double scalar)
	{
		ArrayList<double> result;
		for (int i = 0; i < this->getSize(); i++)
		{
			result.add(this->getValue(i) * scalar);
		}
		return Vector(result, this->shape);
	}
	// Method to overload the - operator to subtract two Vectors
	Vector operator-(Vector other)
	{
		return *this + other * -1.0;
	}
	// Method to overload the / operator to divide a Vector by a scalar
	Vector operator/(double scalar)
	{
		return *this * (1.0 / scalar);
	}
	// Method to overload the == operator to compare two Vectors
	bool operator==(Vector other)
	{
		this->ensureEqualSize(other);
		for (int i = 0; i < this->getSize(); i++)
		{
			if (this->getValue(i) != other.getValue(i))
			{
				return false;
			}
		}
		return true;
	}
	// Method to calculate the dot product of two Vectors
	double dotProduct(Vector other)
	{
		this->ensureEqualSize(other);
		this->ensureEqualShape(other);
		double result = 0.0;
		for (int i = 0; i < this->getSize(); i++)
		{
			result += this->getValue(i) * other.getValue(i);
		}
		return result;
	}
	// Method to throw an error if the Vectors are not the same size
	void ensureEqualSize(Vector other)
	{
		if (this->getSize() != other.getSize())
		{
			Serial.println("Vectors must have the same size");
		}
	}
	// Method to throw an error if the Vectors are not the same shape
	void ensureEqualShape(Vector other)
	{
		if (this->getShape() != other.getShape())
		{
			Serial.println("Vectors must have the same shape");
		}
	}
	// Method to find the String representation of a Vector element that is the longest
	int findLongestElementLength()
	{
		int result = 0;
		for (int i = 0; i < this->getSize(); i++)
		{
			if (result < toString(this->getValue(i)).getSize())
			{
				result = toString(this->getValue(i)).getSize();
			}
		}
		return result;
	}
	// Method to get the String representation of the Vector
	String toString()
	{
		int longestElementLength = this->findLongestElementLength();
		if (this->shape == "column")
		{
			return this->columnVectorToString(longestElementLength);
		}
		else if (this->shape == "row")
		{
			return this->rowVectorToString(longestElementLength);
		}
		else
		{
			return String("Invalid shape");
		}
	}
	// Method to get the String representation of a row vector
	String rowVectorToString(int longestElementLength)
	{
		String result = LEFT_SQUARE_BRACKET + " ";
		int padding = 0;
		String element = "";
		for (int i = 0; i < Vector::getSize() - 1; i++)
		{
			element = toString(this->getValue(i));
			padding = longestElementLength - element.getSize();
			result += element + String(padding, ' ') + " ";
		}
		element = toString(this->getValue(this->getSize() - 1));
		padding = longestElementLength - element.getSize();
		result += element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET + "\n";
		return result;
	}
	// Method to get the String representation of a column vector
 	String columnVectorToString(int longestElementLength)
	{
		String element = toString(this->getValue(0));
		int padding = longestElementLength - element.getSize();
		String result = LEFT_SQUARE_BRACKET_UPPER_CORNER + " " + element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_UPPER_CORNER + "\n";
		for (int i = 1; i < Vector::getSize() - 1; i++)
		{
			element = toString(this->getValue(i));
			padding = longestElementLength - element.getSize();
			result += LEFT_SQUARE_BRACKET_EXTENSION + " " + element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_EXTENSION + "\n";
		}
		element = toString(this->getValue(this->getSize() - 1));
		padding = longestElementLength - element.getSize();
		result += LEFT_SQUARE_BRACKET_LOWER_CORNER + " " + element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_LOWER_CORNER + "\n";
		return result;
	}
	// Method to get the String representation of the Vector
	String toString(int longestElementLength)
	{
		if (this->shape == "column")
		{
			return this->columnVectorToString(longestElementLength);
		}
		else if (this->shape == "row")
		{
			return this->rowVectorToString(longestElementLength);
		}
		else
		{
			return String("Invalid shape");
		}
	}
	// Method to calculate the transpose of the Vector
	Vector transpose()
	{
		if (this->shape == "column")
		{
			return Vector(this->value, "row");
		}
		else if (this->shape == "row")
		{
			return Vector(this->value, "column");
		}
		else
		{
			Serial.println("Invalid shape");
		}
	}
	// Method to calculate the p-norm of the Vector
	double pNorm(unsigned int p)
	{
		double result = 0.0;
		for (int i = 0; i < this->getSize(); i++)
		{
			result += pow(abs(this->getValue(i)), p);
		}
		return pow(result, 1.0 / p);
	}
	// Method to calculate the infinity norm of the Vector
	double infinityNorm()
	{
		double result = 0.0;
		for (int i = 0; i < this->getSize(); i++)
		{
			result = max(result, abs(this->getValue(i)));
		}
		return result;
	}
	// Method to calculate the magnitude of the Vector
	double magnitude()
	{
		return this->pNorm(2);
	}
	// Method to calculate the unit Vector
	Vector unitVector()
	{
		return *this / this->magnitude();
	}
	// Method to overload the * operator to multiply a Vector by another Vector
	double operator*(Vector other)
	{
		this->ensureEqualSize(other);
		if (this->shape == "row" && other.getShape() == "column")
		{
			return this->dotProduct(other.transpose());
		}
		else
		{
			Serial.println("Invalid shapes");
		}
	}
	// Method to overload the != operator to compare two Vectors
	bool operator!=(Vector other)
	{
		return !(*this == other);
	}
};
