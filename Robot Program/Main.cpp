#include "ColumnVector.hpp"
int main()
{
	Vector a;
	a = Vector(6, 1.0);
	a.print();
	Vector b;
	b = a / 2.0;
	b.print();
	return 0;
}
