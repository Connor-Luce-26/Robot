#pragma once
#include "ArrayList.hpp"
#include "String.h"
#include "UTF8Symbols.hpp"
#include "Serial.h"
// Class representing a generic ArrayList
class Vector
{
private:
	// Vector to store the values of the ArrayList
	ArrayList<double> value;
	// Shape of the ArrayList
	String shape;

public:
	// Constructor that initializes the ArrayList with a given ArrayList of values and a given shape
	Vector(ArrayList<double> value, String shape)
	{
		this->value = value;
		this->shape = shape;
	}
	// Constructor that initializes the ArrayList with a given shape and size, and fills it with a given value
	Vector(int size, double value, String shape)
	{
		this->shape = shape;
		for (int i = 0; i < size; i++)
		{
			this->value.push_back(value);
		}
	}
	// Constructor that initializes the ArrayList with a given size and fills it with zeros
	Vector(int size, String shape) : Vector(size, 0.0, shape)
	{
	}
	// Default constructor that initializes an empty ArrayList
	Vector()
	{
		this->value = ArrayList<double>();
		this->shape = "column";
	}
	// Destructor
	~Vector()
	{
	}
	// Get the size of the ArrayList
	int size()
	{
		return this->value.size();
	}
	// Get the value of the ArrayList
	ArrayList<double> getValue()
	{
		return this->value;
	}
	// Get the value of the ArrayList at a given index
	double getValue(int index)
	{
		return this->value[index];
	}
	// Get the shape of the ArrayList
	String getShape()
	{
		return this->shape;
	}
	// Set the value of the ArrayList
	void setValue(ArrayList<double> value)
	{
		this->value = value;
	}
	// Set the value of the ArrayList at a given index
	void setValue(int index, double value)
	{
		this->value[index] = value;
	}
	// Set the shape of the ArrayList
	void setShape(String shape)
	{
		this->shape = shape;
	}
	// Method to overload the + operator to add two ArrayLists
	Vector operator+(Vector other)
	{
		this->ensureEqualSize(other);
		this->ensureEqualShape(other);
		ArrayList<double> result;
		for (int i = 0; i < this->size(); i++)
		{
			result.push_back(this->getValue(i) + other.getValue(i));
		}
		return Vector(result, this->shape);
	}
	// Method to overload the * operator to multiply a ArrayList by a scalar
	Vector operator*(double scalar)
	{
		ArrayList<double> result;
		for (int i = 0; i < this->size(); i++)
		{
			result.push_back(this->getValue(i) * scalar);
		}
		return Vector(result, this->shape);
	}
	// Method to overload the - operator to subtract two ArrayLists
	Vector operator-(Vector other)
	{
		return *this + other * -1.0;
	}
	// Method to overload the / operator to divide a ArrayList by a scalar
	Vector operator/(double scalar)
	{
		return *this * (1.0 / scalar);
	}
	// Method to overload the == operator to compare two ArrayLists
	bool operator==(Vector other)
	{
		this->ensureEqualSize(other);
		for (int i = 0; i < this->size(); i++)
		{
			if (this->getValue(i) != other.getValue(i))
			{
				return false;
			}
		}
		return true;
	}
	// Method to calculate the dot product of two ArrayLists
	double dotProduct(Vector other)
	{
		this->ensureEqualSize(other);
		this->ensureEqualShape(other);
		double result = 0.0;
		for (int i = 0; i < this->size(); i++)
		{
			result += this->getValue(i) * other.getValue(i);
		}
		return result;
	}
	// Method to throw an error if the ArrayLists are not the same size
	void ensureEqualSize(Vector other)
	{
		if (this->size() != other.size())
		{
			Serial.println("Vectors must have the same size");
		}
	}
	// Method to throw an error if the ArrayLists are not the same shape
	void ensureEqualShape(Vector other)
	{
		if (this->getShape() != other.getShape())
		{
			Serial.println("Vectors must have the same shape");
		}
	}
	// Method to find the String representation of a ArrayList element that is the longest
	int findLongestElementLength()
	{
		int result = 0;
		for (int i = 0; i < this->size(); i++)
		{
			if (result < to_String(this->getValue(i)).size())
			{
				result = to_String(this->getValue(i)).size();
			}
		}
		return result;
	}
	// Method to print the ArrayList
	void print()
	{
		int longestElementLength = this->findLongestElementLength();
		if (this->shape == "column")
		{
			this->printColumnVector(longestElementLength);
		}
		else if (this->shape == "row")
		{
			this->printRowVector(longestElementLength);
		}
		else
		{
			Serial.println("Invalid shape");
		}
	}
	// Method to print the ArrayList given the longest element length
	void print(int longestElementLength)
	{
		if (this->shape == "column")
		{
			this->printColumnVector(longestElementLength);
		}
		else if (this->shape == "row")
		{
			this->printRowVector(longestElementLength);
		}
		else
		{
			Serial.println("Invalid shape");
		}
	}
	// Method to print the row ArrayList
	void printRowVector(int longestElementLength)
	{
		String result = LEFT_SQUARE_BRACKET + " ";
	    int padding = 0;
		String element = "";
		for (int i = 0; i < Vector::size() - 1; i++)
		{
			element = to_String(this->getValue(i));
			padding = longestElementLength - element.size();
			result += element + String(padding, ' ') + " ";
		}
		element = to_String(this->getValue(this->size() - 1));
		padding = longestElementLength - element.size();
		result += element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET + "\n";
		Serial.print(result);
	}
	// Method to print the column ArrayList
	void printColumnVector(int longestElementLength)
	{
		String element = to_String(this->getValue(0));
		int padding = longestElementLength - element.size();
		String result = LEFT_SQUARE_BRACKET_UPPER_CORNER + " " + element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_UPPER_CORNER + "\n";
		for (int i = 1; i < Vector::size() - 1; i++)
		{
			element = to_String(this->getValue(i));
			padding = longestElementLength - element.size();
			result += LEFT_SQUARE_BRACKET_EXTENSION + " " + element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_EXTENSION + "\n";
		}
		element = to_String(this->getValue(this->size() - 1));
		padding = longestElementLength - element.size();
		result += LEFT_SQUARE_BRACKET_LOWER_CORNER + " " + element + String(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_LOWER_CORNER + "\n";
		Serial.print(result);
	}
	// Method to calculate the transpose of the ArrayList
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
	// Method to calculate the p-norm of the ArrayList
	double pNorm(unsigned int p)
	{
		double result = 0.0;
		for (int i = 0; i < this->size(); i++)
		{
			result += pow(abs(this->getValue(i)), p);
		}
		return pow(result, 1.0 / p);
	}
	// Method to calculate the infinity norm of the ArrayList
	double infinityNorm()
	{
		double result = 0.0;
		for (int i = 0; i < this->size(); i++)
		{
			result = max(result, abs(this->getValue(i)));
		}
		return result;
	}
	// Method to calculate the magnitude of the ArrayList
	double magnitude()
	{
		return this->pNorm(2);
	}
	// Method to calculate the unit ArrayList
	Vector unitVector()
	{
		return *this / this->magnitude();
	}
	// Method to overload the * operator to multiply a ArrayList by another ArrayList
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
	// Method to overload the != operator to compare two ArrayLists
	bool operator!=(Vector other)
	{
		return !(*this == other);
	}
};
