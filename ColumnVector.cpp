#include <vector>
class ColumnVector
{
private:
    std::vector<double> columnVector;

public:
    ColumnVector(std::vector<double> columnVector)
    {
        this->columnVector = columnVector;
    }
};