#pragma once
#include "Vector.hpp"
// Class representing a generic matrix
class Matrix
{
private:
	// Matrix to store the values of the matrix
	std::vector<std::vector<double>> value;

public:
	// Constructor that initializes the matrix with a given matrix of values
	Matrix(std::vector<std::vector<double>> value)
	{
		this->value = value;
	}
	// Constructor that initializes the matrix with a given number of numberOfRows and numberOfColumns, and fills it with a given value
	Matrix(int numberOfRows, int numberOfColumns, double value)
	{
		for (int i = 0; i < numberOfRows; i++)
		{
			std::vector<double> row;
			for (int j = 0; j < numberOfColumns; j++)
			{
				row.push_back(value);
			}
			this->value.push_back(row);
		}
	}
	// Constructor that initializes the matrix with a given number of numberOfRows and numberOfColumns, and fills it with zeros
	Matrix(int numberOfRows, int numberOfColumns) : Matrix(numberOfRows, numberOfColumns, 0.0)
	{
	}
	// Constructor that initializes the matrix with a vector of vectors
	Matrix(std::vector<Vector> vectors)
	{
		if (vectors[0].getShape() == "column")
		{
			for (int column = 0; column < vectors[0].size(); column++)
			{
				for (int row = 0; row < vectors.size(); row++)
				{
					this->value[row].push_back(vectors[row].getValue(column));
				}
			}
		}
		else if (vectors[0].getShape() == "row")
		{
			for (int row = 0; row < vectors.size(); row++)
			{
				this->value.push_back(vectors[row].getValue());
			}
		}
		else
		{
			throw std::invalid_argument("Invalid shape");
		}
	}
	// Default constructor that initializes an empty matrix
	Matrix()
	{
		this->value = std::vector<std::vector<double>>();
	}
	// Destructor
	~Matrix()
	{
	}
	// Get the number of numberOfRows in the matrix
	int numberOfRows()
	{
		return this->value.size();
	}
	// Get the number of numberOfColumns in the matrix
	int numberOfColumns()
	{
		return this->value[0].size();
	}
	// Get the value of the matrix
	std::vector<std::vector<double>> getValue()
	{
		return this->value;
	}
	// Get the value of the matrix at a given row and column
	double getValue(int row, int column)
	{
		return this->value[row][column];
	}
	// Set the value of the matrix
	void setValue(std::vector<std::vector<double>> value)
	{
		this->value = value;
	}
	// Set the value of the matrix at a given row and column
	void setValue(int row, int column, double value)
	{
		this->value[row][column] = value;
	}
	// Method to convert a row of the matrix to a string
	std::string rowToString(int row)
	{
		std::string result = "";
		for (int column = 0; column < this->numberOfColumns(); column++)
		{
			result += std::to_string(this->getValue(row, column)) + " ";
		}
		return result;
	}
	// Method to print the matrix
	void print()
	{
		std::string result = "";
		if (this->numberOfRows() <= 1)
		{
			Vector(this->value[0], "row").print();
		}
		else
		{
			std::string result = LEFT_SQUARE_BRACKET_UPPER_CORNER + " ";
			result += this->rowToString(0);
			result += RIGHT_SQUARE_BRACKET_UPPER_CORNER + "\n";
			for(int row = 1; row < this->numberOfRows() - 1; row++)
			{
				result += LEFT_SQUARE_BRACKET_EXTENSION + " ";
				this->rowToString(row);
				result += RIGHT_SQUARE_BRACKET_EXTENSION + "\n";
			}
			result += LEFT_SQUARE_BRACKET_LOWER_CORNER + " ";
			result += this->rowToString(this->numberOfRows() - 1);
			result += RIGHT_SQUARE_BRACKET_LOWER_CORNER + "\n";
			std::cout << result;
		}
	}
	// Method to convert the matrix to a vector of column vectors
	std::vector<Vector> toColumnVectors()
	{
		std::vector<Vector> result;
		for (int column = 0; column < this->numberOfColumns(); column++)
		{
			std::vector<double> values;
			for (int row = 0; row < this->numberOfRows(); row++)
			{
				values.push_back(this->getValue(row, column));
			}
			result.push_back(Vector(values, "column"));
		}
		return result;
	}
	// Method to convert the matrix to a vector of row vectors
	std::vector<Vector> toRowVectors()
	{
		std::vector<Vector> result;
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			result.push_back(Vector(this->value[row], "row"));
		}
		return result;
	}
	// Method to calculate the transpose of the matrix
	Matrix transpose()
	{
		std::vector<Vector> oldVectors = this->toColumnVectors();
		std::vector<Vector> newVectors;
		for (int i = 0; i < oldVectors.size(); i++)
		{
			newVectors[i] = oldVectors[i].transpose();
		}
		return Matrix(newVectors);
	}
	// Method to overload the * operator to multiply a matrix by a scalar
	Matrix operator*(double scalar)
	{
		std::vector<Vector> oldVectors = this->toColumnVectors();
		std::vector<Vector> newVectors;
		for (int i = 0; i < oldVectors.size(); i++)
		{
			newVectors[i] = oldVectors[i] * scalar;
		}
		return Matrix(newVectors);
	}
};