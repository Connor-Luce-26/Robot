#pragma once
#include "Vector.hpp"
class ColumnVector : public Vector
{
public:
    // Constructor that initializes the column vector with a given vector of values
    ColumnVector(std::vector<double> value) : Vector(value)
    {
    }
    // Constructor that initializes the column vector with a given size and fills it with a specified value
    ColumnVector(int size, double value) : Vector(size, value)
    {
    }
    // Constructor that initializes the column vector with a given size and fills it with zeros
    ColumnVector(int size) : Vector(size)
    {
    }
    // Default constructor that initializes an empty column vector
    ColumnVector() : Vector()
    {
    }
    // Method to get the size of the column vector
    std::tuple<int, int> size()
    {
        return std::make_tuple(Vector::size(), 1);
    }
    // Method to print the column vector
    void print()
    {
        std::string result = LEFT_SQUARE_BRACKET_UPPER_CORNER + " " + std::to_string(this->get(0)) + " " + RIGHT_SQUARE_BRACKET_UPPER_CORNER + "\n";
        for (int i = 1; i < Vector::size() - 1; i++)
        {
            result += LEFT_SQUARE_BRACKET_EXTENSION + " " + std::to_string(this->get(i)) + " " + RIGHT_SQUARE_BRACKET_EXTENSION + "\n";
        }
        result += LEFT_SQUARE_BRACKET_LOWER_CORNER + " " + std::to_string(this->get(Vector::size() - 1)) + " " + RIGHT_SQUARE_BRACKET_LOWER_CORNER + "\n";
        std::cout << result;
    }
    // Method to overload the + operator to add two vectors
    ColumnVector operator+(ColumnVector other)
    {
        return ColumnVector(Vector::operator+(other).get());
    }
    // Method to overload the * operator to multiply a vector by a scalar
    ColumnVector operator*(double scalar)
    {
        return ColumnVector(Vector::operator*(scalar).get());
    }
    // Method to overload the - operator to subtract two vectors
    ColumnVector operator-(ColumnVector other)
    {
        return ColumnVector(Vector::operator-(other).get());
    }
    // Method to overload the / operator to divide a vector by a scalar
    ColumnVector operator/(double scalar)
    {
        return ColumnVector(Vector::operator/(scalar).get());
    }
    
};