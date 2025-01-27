#include "Vector.hpp"
#include "Matrix.hpp"
int main()
{	
	std::vector<std::vector<double>> values = { {1, 2, 3}, {4, 5, 6}, {7, 8, 10} };
	Matrix A = Matrix(values);
	A.print();
	A.inverse().print();
	return 0;
}
