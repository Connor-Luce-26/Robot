#include "Vector.hpp"
#include "Matrix.hpp"
int main()
{
	Matrix A = Matrix(2, 2, 1.0);
	A.print();
	(A * 2.0).print();
	return 0;
}
