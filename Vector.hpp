#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "UTF8Symbols.hpp"

// Class representing a generic vector
class Vector
{
private:
	// Vector to store the values of the vector
	std::vector<double> value;

public:
	// Constructor that initializes the vector with a given vector of values
	Vector(std::vector<double> value)
	{
		this->value = value;
	}
	// Constructor that initializes the vector with a given size and fills it with a specified value
	Vector(int size, double value)
	{
		this->value = std::vector<double>(size, value);
	}
	// Constructor that initializes the vector with a given size and fills it with zeros
	Vector(int size) : Vector(size, 0.0)
	{
	}
	// Default constructor that initializes an empty vector
	Vector()
	{
		this->value = std::vector<double>();
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
	std::vector<double> get()
	{
		return this->value;
	}
	// Get the value of the vector at a given index
	double get(int index)
	{
		return this->value[index];
	}
	// Set the value of the vector
	void set(std::vector<double> value)
	{
		this->value = value;
	}
	// Set the value of the vector at a given index
	void set(int index, double value)
	{
		this->value[index] = value;
	}
	// Method to overload the + operator to add two vectors
	Vector operator+(Vector other)
	{
		this->checkSize(other);
		std::vector<double> result;
		for (int i = 0; i < this->size(); i++)
		{
			result.push_back(this->get(i) + other.get(i));
		}
		return Vector(result);
	}
	// Method to overload the * operator to multiply a vector by a scalar
	Vector operator*(double scalar)
	{
		std::vector<double> result;
		for (int i = 0; i < this->size(); i++)
		{
			result.push_back(this->get(i) * scalar);
		}
		return Vector(result);
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
		this->checkSize(other);
		for (int i = 0; i < this->size(); i++)
		{
			if (this->get(i) != other.get(i))
			{
				return false;
			}
		}
		return true;
	}
	// Method to calculate the dot product of two vectors
	double dot(Vector other)
	{
		this->checkSize(other);
		double result = 0.0;
		for (int i = 0; i < this->size(); i++)
		{
			result += this->get(i) * other.get(i);
		}
		return result;
	}
	// Method to throw an error if the vectors are not the same size
	void checkSize(Vector other)
	{
		if (this->size() != other.size())
		{
			throw std::invalid_argument("Vectors must be the same size");
		}
	}
	// Method to print the vector
	void print()
	{
		std::string result = LEFT_POINTING_ANGLE_BRACKET;
		for (int i = 0; i < this->size() - 1; i++)
		{
			result += std::to_string(this->get(i)) + ", ";
		}
		result += std::to_string(this->get(this->size() - 1)) + " " + RIGHT_POINTING_ANGLE_BRACKET + "\n";
		std::cout << result;
	}
};
