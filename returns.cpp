#include "returns.h"
#include <vector>

using namespace std;

Returns::Returns(){}

    
double Returns::CalculateMeanReturn(const std::vector<double>& array, int start, int end)
{
    if (start < 0 || end > array.size() || start > end) {
        throw std::out_of_range("Invalid start or end range");
    }
    double sum = 0 ;
    double avgReturn ;
    int numberOfDays = end - start;  // Number of days now depends on the range specified by start and end

    for (int idx = start; idx < end; idx++)
    {
        sum += array[idx];
    }

    avgReturn = sum/numberOfDays;

    return avgReturn;
}

double Returns::CalculateCovariance(const std::vector<double>& array1,const std::vector<double>& array2, int start, int end)
{
    if (start < 0 || end > array1.size() || start > end || end > array2.size()) {
        throw std::out_of_range("Invalid start or end range for the arrays");
    }

    double variance = 0;
    double covariance;
    int numberOfDays = end - start;  // Number of days now depends on the range specified by start and end
    double avgReturn1 = CalculateMeanReturn(array1, start, end);
    double avgReturn2 = CalculateMeanReturn(array2, start, end);

    for (int idx = start; idx < end; idx++)
    {
       variance += (array1[idx]-avgReturn1)*(array2[idx]-avgReturn2);
    }

    covariance = variance/(numberOfDays-1);
    return covariance;
}

