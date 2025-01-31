#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "UTF8Symbols.hpp"
#include <math>

// Class representing a generic vector
class Vector
{
private:
	// Vector to store the values of the vector
	std::vector<double> value;
	// Shape of the vector
	std::string shape;

public:
	// Constructor that initializes the vector with a given vector of values and a given shape
	Vector(std::vector<double> value, std::string shape)
	{
		this->value = value;
		this->shape = shape;
	}
	// Constructor that initializes the vector with a given shape and size, and fills it with a given value
	Vector(int size, double value, std::string shape)
	{
		this->shape = shape;
		for (int i = 0; i < size; i++)
		{
			this->value.push_back(value);
		}
	}
	// Constructor that initializes the vector with a given size and fills it with zeros
	Vector(int size, std::string shape) : Vector(size, 0.0, shape)
	{
	}
	// Default constructor that initializes an empty vector
	Vector()
	{
		this->value = std::vector<double>();
		this->shape = "column";
	}
	// Destructor
	~Vector()
	{
	}
	// Get the size of the vector
	int size()
	{
		return this->value.size();
	}
	// Get the value of the vector
	std::vector<double> getValue()
	{
		return this->value;
	}
	// Get the value of the vector at a given index
	double getValue(int index)
	{
		return this->value[index];
	}
	// Get the shape of the vector
	std::string getShape()
	{
		return this->shape;
	}
	// Set the value of the vector
	void setValue(std::vector<double> value)
	{
		this->value = value;
	}
	// Set the value of the vector at a given index
	void setValue(int index, double value)
	{
		this->value[index] = value;
	}
	// Set the shape of the vector
	void setShape(std::string shape)
	{
		this->shape = shape;
	}
	// Method to overload the + operator to add two vectors
	Vector operator+(Vector other)
	{
		this->ensureEqualSize(other);
		this->ensureEqualShape(other);
		std::vector<double> result;
		for (int i = 0; i < this->size(); i++)
		{
			result.push_back(this->getValue(i) + other.getValue(i));
		}
		return Vector(result, this->shape);
	}
	// Method to overload the * operator to multiply a vector by a scalar
	Vector operator*(double scalar)
	{
		std::vector<double> result;
		for (int i = 0; i < this->size(); i++)
		{
			result.push_back(this->getValue(i) * scalar);
		}
		return Vector(result, this->shape);
	}
	// Method to overload the - operator to subtract two vectors
	Vector operator-(Vector other)
	{
		return *this + other * -1.0;
	}
	// Method to overload the / operator to divide a vector by a scalar
	Vector operator/(double scalar)
	{
		return *this * (1.0 / scalar);
	}
	// Method to overload the == operator to compare two vectors
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
	// Method to calculate the dot product of two vectors
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
	// Method to throw an error if the vectors are not the same size
	void ensureEqualSize(Vector other)
	{
		if (this->size() != other.size())
		{
			throw std::invalid_argument("Vectors must be the same size");
		}
	}
	// Method to throw an error if the vectors are not the same shape
	void ensureEqualShape(Vector other)
	{
		if (this->getShape() != other.getShape())
		{
			throw std::invalid_argument("Vectors must have the same shape");
		}
	}
	// Method to find the string representation of a vector element that is the longest
	int findLongestElementLength()
	{
		int result = 0;
		for (int i = 0; i < this->size(); i++)
		{
			if (result < std::to_string(this->getValue(i)).size())
			{
				result = std::to_string(this->getValue(i)).size();
			}
		}
		return result;
	}
	// Method to print the vector
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
			throw std::invalid_argument("Invalid shape");
		}
	}
	// Method to print the vector given the longest element length
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
			throw std::invalid_argument("Invalid shape");
		}
	}
	// Method to print the row vector
	void printRowVector(int longestElementLength)
	{
		std::string result = LEFT_SQUARE_BRACKET + " ";
	    int padding = 0;
		std::string element = "";
		for (int i = 0; i < Vector::size() - 1; i++)
		{
			element = std::to_string(this->getValue(i));
			padding = longestElementLength - element.size();
			result += element + std::string(padding, ' ') + " ";
		}
		element = std::to_string(this->getValue(this->size() - 1));
		padding = longestElementLength - element.size();
		result += element + std::string(padding, ' ') + " " + RIGHT_SQUARE_BRACKET + "\n";
		std::cout << result;
	}
	// Method to print the column vector
	void printColumnVector(int longestElementLength)
	{
		std::string element = std::to_string(this->getValue(0));
		int padding = longestElementLength - element.size();
		std::string result = LEFT_SQUARE_BRACKET_UPPER_CORNER + " " + element + std::string(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_UPPER_CORNER + "\n";
		for (int i = 1; i < Vector::size() - 1; i++)
		{
			element = std::to_string(this->getValue(i));
			padding = longestElementLength - element.size();
			result += LEFT_SQUARE_BRACKET_EXTENSION + " " + element + std::string(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_EXTENSION + "\n";
		}
		element = std::to_string(this->getValue(this->size() - 1));
		padding = longestElementLength - element.size();
		result += LEFT_SQUARE_BRACKET_LOWER_CORNER + " " + element + std::string(padding, ' ') + " " + RIGHT_SQUARE_BRACKET_LOWER_CORNER + "\n";
		std::cout << result;
	}
	// Method to calculate the transpose of the vector
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
			throw std::invalid_argument("Invalid shape");
		}
	}
	// Method to calculate the p-norm of the vector
	double pNorm(unsigned int p)
	{
		double result = 0.0;
		for (int i = 0; i < this->size(); i++)
		{
			result += pow(abs(this->getValue(i)), p);
		}
		return pow(result, 1.0 / p);
	}
	// Method to calculate the infinity norm of the vector
	double infinityNorm()
	{
		double result = 0.0;
		for (int i = 0; i < this->size(); i++)
		{
			result = std::max(result, abs(this->getValue(i)));
		}
		return result;
	}
	// Method to calculate the magnitude of the vector
	double magnitude()
	{
		return this->pNorm(2);
	}
	// Method to calculate the unit vector
	Vector unitVector()
	{
		return *this / this->magnitude();
	}
	// Method to overload the * operator to multiply a vector by another vector
	double operator*(Vector other)
	{
		this->ensureEqualSize(other);
		if (this->shape == "row" && other.getShape() == "column")
		{
			return this->dotProduct(other.transpose());
		}
		else
		{
			throw std::invalid_argument("Invalid shapes for multiplication");
		}
	}
	// Method to overload the != operator to compare two vectors
	bool operator!=(Vector other)
	{
		return !(*this == other);
	}
};
