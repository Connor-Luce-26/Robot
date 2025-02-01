#pragma once
#include "Vector.hpp"
#include "ArrayList.hpp"
#include "String.h"
// Class representing a generic matrix
class Matrix
{
private:
	// Matrix to store the values of the matrix
	ArrayList<ArrayList<double>> value;

public:
	// Constructor that initializes the matrix with a given matrix of values
	Matrix(ArrayList<ArrayList<double>> value)
	{
		this->value = value;
	}
	// Constructor that initializes the matrix with a given number of numberOfRows and numberOfColumns, and fills it with a given value
	Matrix(int numberOfRows, int numberOfColumns, double value)
	{
		for (int i = 0; i < numberOfRows; i++)
		{
			ArrayList<double> row;
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
	// Constructor that initializes the matrix with a ArrayList of Vector objects
	Matrix(ArrayList<Vector> VectorArrayList)
	{
		if (VectorArrayList[0].getShape() == "column")
		{
			for (int column = 0; column < VectorArrayList[0].size(); column++)
			{
				for (int row = 0; row < VectorArrayList.size(); row++)
				{
					this->value[row].push_back(VectorArrayList[row].getValue(column));
				}
			}
		}
		else if (VectorArrayList[0].getShape() == "row")
		{
			for (int row = 0; row < VectorArrayList.size(); row++)
			{
				this->value.push_back(VectorArrayList[row].getValue());
			}
		}
		else
		{
			Serial.println("Invalid shape");
		}
	}
	// Constructor that initializes an identity matrix of a given size
	Matrix(int size) : Matrix(size, size, 0.0)
	{
		for (int i = 0; i < size; i++)
		{
			this->setValue(i, i, 1.0);
		}
	}
	// Default constructor that initializes an empty matrix
	Matrix()
	{
		this->value = ArrayList<ArrayList<double>>();
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
	ArrayList<ArrayList<double>> getValue()
	{
		return this->value;
	}
	// Get the value of the matrix at a given row and column
	double getValue(int row, int column)
	{
		return this->value[row][column];
	}
	// Set the value of the matrix
	void setValue(ArrayList<ArrayList<double>> value)
	{
		this->value = value;
	}
	// Set the value of the matrix at a given row and column
	void setValue(int row, int column, double value)
	{
		if (row < 0 || row >= this->numberOfRows() || column < 0 || column >= this->numberOfColumns())
		{
			Serial.println("Index out of bounds");
		}
		this->value[row][column] = value;
	}
	// Method to convert a row of the matrix to a String
	String rowToString(int row, int longestElementLength)
	{
		String result = "";
		for (int column = 0; column < this->numberOfColumns(); column++)
		{
			String element = to_String(this->getValue(row, column));
			int padding = longestElementLength - element.size();
			result += element + String(padding, ' ') + " ";
		}
		return result;
	}
	// Method to find the String representation of a matrix element that is the longest
	int findLongestElementLength()
	{
		int result = 0;
		ArrayList<Vector> rowVectors = this->toRowVectors();
		for (int i = 0; i < this->numberOfRows(); i++)
		{
			if (result < rowVectors[i].findLongestElementLength())
			{
				result = rowVectors[i].findLongestElementLength();
			}
		}
		return result;
	}
	// Method to print the matrix
	void print()
	{
		int longestElementLength = this->findLongestElementLength();
		String result = "";
		if (this->numberOfRows() <= 1)
		{
			Vector(this->value[0], "row").print();
		}
		else
		{
			String result = LEFT_SQUARE_BRACKET_UPPER_CORNER + " ";
			result += this->rowToString(0, longestElementLength);
			result += RIGHT_SQUARE_BRACKET_UPPER_CORNER + "\n";
			for (int row = 1; row < this->numberOfRows() - 1; row++)
			{
				result += LEFT_SQUARE_BRACKET_EXTENSION + " ";
				result += this->rowToString(row, longestElementLength);
				result += RIGHT_SQUARE_BRACKET_EXTENSION + "\n";
			}
			result += LEFT_SQUARE_BRACKET_LOWER_CORNER + " ";
			result += this->rowToString(this->numberOfRows() - 1, longestElementLength);
			result += RIGHT_SQUARE_BRACKET_LOWER_CORNER + "\n";
			serial.print(result);
		}
	}
	// Method to convert the matrix to a ArrayList of column ArrayLists
	ArrayList<Vector> toColumnVectors()
	{
		ArrayList<Vector> result;
		for (int column = 0; column < this->numberOfColumns(); column++)
		{
			ArrayList<double> values;
			for (int row = 0; row < this->numberOfRows(); row++)
			{
				values.push_back(this->getValue(row, column));
			}
			result.push_back(Vector(values, "column"));
		}
		return result;
	}
	// Method to convert the matrix to a ArrayList of row ArrayLists
	ArrayList<Vector> toRowVectors()
	{
		ArrayList<Vector> result;
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			result.push_back(Vector(this->value[row], "row"));
		}
		return result;
	}
	// Method to calculate the transpose of the matrix
	Matrix transpose()
	{
		ArrayList<Vector> oldVectors = this->toColumnVectors();
		ArrayList<Vector> newVectors;
		for (int i = 0; i < oldVectors.size(); i++)
		{
			newVectors.push_back(oldVectors[i].transpose());
		}
		return Matrix(newVectors);
	}
	// Method to overload the * operator to multiply a matrix by a scalar
	Matrix operator*(double scalar)
	{
		ArrayList<Vector> oldVectors = this->toRowVectors();
		ArrayList<Vector> newVectors;
		for (int i = 0; i < oldVectors.size(); i++)
		{
			newVectors.push_back(oldVectors[i] * scalar);
		}
		return Matrix(newVectors);
	}
	// Method to overload the * operator to multiply two matrices
	Matrix operator*(Matrix other)
	{
		if (this->numberOfColumns() != other.numberOfRows())
		{
			Serial.println("Invalid dimensions");
		}
		ArrayList<Vector> rowVectors = this->toRowVectors();
		ArrayList<Vector> columnVectors = other.toColumnVectors();
		ArrayList<ArrayList<double>> results;
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			ArrayList<double> result;
			for (int column = 0; column < other.numberOfColumns(); column++)
			{
				result.push_back(rowVectors[row] * (columnVectors[column]));
			}
			results.push_back(result);
		}
		return Matrix(results);
	}
	// Method to throw an error if the matrices are not the same size
	void ensureEqualSize(Matrix other)
	{
		if (this->numberOfRows() != other.numberOfRows() || this->numberOfColumns() != other.numberOfColumns())
		{
			Serial.println("Matrices must have the same size");
		}
	}
	// Method to overload the + operator to add two matrices
	Matrix operator+(Matrix other)
	{
		this->ensureEqualSize(other);
		ArrayList<Vector> oldVectors = this->toRowVectors();
		ArrayList<Vector> otherVectors = other.toRowVectors();
		ArrayList<Vector> newVectors;
		for (int i = 0; i < oldVectors.size(); i++)
		{
			newVectors.push_back(oldVectors[i] + otherVectors[i]);
		}
		return Matrix(newVectors);
	}
	// Method to overload the - operator to subtract two matrices
	Matrix operator-(Matrix other)
	{
		return *this + (other * -1.0);
	}
	// Method to overload the / operator to divide a matrix by a scalar
	Matrix operator/(double scalar)
	{
		return *this * (1.0 / scalar);
	}
	// Method to overload the == operator to compare two matrices
	bool operator==(Matrix other)
	{
		ArrayList<Vector> oldVectors = this->toRowVectors();
		ArrayList<Vector> otherVectors = other.toRowVectors();
		for (int i = 0; i < oldVectors.size(); i++)
		{
			if (oldVectors[i] != otherVectors[i])
			{
				return false;
			}
		}
		return true;
	}
	// Method to overload the != operator to compare two matrices
	bool operator!=(Matrix other)
	{
		return !(*this == other);
	}
	// method to throw an error if the matrix is not square
	void ensureSquare()
	{
		if (this->numberOfRows() != this->numberOfColumns())
		{
			Serial.println("Matrix must be square");
		}
	}
	// Method to calculate the determinant of the matrix
	double determinant()
	{
		this->ensureSquare();
		if (this->numberOfRows() == 1)
		{
			return this->getValue(0, 0);
		}
		else
		{
			double result = 0.0;
			for (int column = 0; column < this->numberOfColumns(); column++)
			{
				Matrix submatrix = Matrix(this->numberOfRows() - 1, this->numberOfColumns() - 1);
				for (int row = 1; row < this->numberOfRows(); row++)
				{
					int subcolumn = 0;
					for (int subrow = 0; subrow < this->numberOfColumns(); subrow++)
					{
						if (subrow != column)
						{
							submatrix.setValue(row - 1, subcolumn, this->getValue(row, subrow));
							subcolumn++;
						}
					}
				}
				result += pow(-1, column) * this->getValue(0, column) * submatrix.determinant();
			}
			return result;
		}
	}
	// Method to throw an error if the matrix is not invertible
	void ensureInvertible()
	{
		if (this->determinant() == 0.0)
		{
			Serial.println("Matrix must be invertible");
		}
	}
	// Method to check if the matrix is an identity matrix
	bool isIdentity()
	{
		this->ensureSquare();
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			for (int column = 0; column < this->numberOfColumns(); column++)
			{
				if (row == column)
				{
					if (this->getValue(row, column) != 1.0)
					{
						return false;
					}
				}
				else
				{
					if (this->getValue(row, column) != 0.0)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	// Method to calculate the minor of the matrix
	Matrix minor()
	{
		this->ensureSquare();
		Matrix result = Matrix(this->numberOfRows(), this->numberOfColumns());
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			for (int column = 0; column < this->numberOfColumns(); column++)
			{
				Matrix submatrix = Matrix(this->numberOfRows() - 1, this->numberOfColumns() - 1);
				int subrow = 0;
				for (int i = 0; i < this->numberOfRows(); i++)
				{
					if (i != row)
					{
						int subcolumn = 0;
						for (int j = 0; j < this->numberOfColumns(); j++)
						{
							if (j != column)
							{
								submatrix.setValue(subrow, subcolumn, this->getValue(i, j));
								subcolumn++;
							}
						}
						subrow++;
					}
				}
				result.setValue(row, column, submatrix.determinant());
			}
		}
		return result;
	}
	// Method to calculate the cofactor of the matrix
	Matrix cofactor()
	{
		this->ensureSquare();
		Matrix minor = this->minor();
		Matrix result = Matrix(this->numberOfRows(), this->numberOfColumns());
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			for (int column = 0; column < this->numberOfColumns(); column++)
			{
				result.setValue(row, column, pow(-1, row + column + 2) * minor.getValue(row, column));
			}
		}
		return result;
	}
	// Method to calculate the adjoint of the matrix
	Matrix adjoint()
	{
		this->ensureSquare();
		return this->cofactor().transpose();
	}
	// Method to calculate the inverse of the matrix
	Matrix inverse()
	{
		this->ensureSquare();
		this->ensureInvertible();
		return this->adjoint() / this->determinant();
	}
	// Method to multiply a matrix by a ArrayList
	Vector operator*(Vector other)
	{
		if (this->numberOfColumns() != other.size() && other.getShape() == "column")
		{
			Serial.println("Invalid dimensions");
		}
		ArrayList<double> result;
		ArrayList<Vector> rowVectors = this->toRowVectors();
		for (int row = 0; row < this->numberOfRows(); row++)
		{
			result.push_back(rowVectors[row] * other);
		}
		return Vector(result, "column");
	}
	// Method to check if the matrix is square
	bool isSquare()
	{
		return this->numberOfRows() == this->numberOfColumns();
	}
	// Method to calculate the pseudo-inverse of the matrix
	Matrix pseudoInverse()
	{
		if (this->isSquare())
		{
			this->ensureInvertible();
			return this->inverse();
		}
		else
		{
			Matrix transposedMatrix = this->transpose();
			Matrix matrixCopy = Matrix(this->getValue());
			return (transposedMatrix * matrixCopy).inverse() * transposedMatrix;
		}
	}
};