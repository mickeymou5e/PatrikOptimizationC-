#include <vector>
#ifndef RETURNS_H
#define RETURNS_H

class Returns
{
public:
    // Default Constructor 
    
    Returns();

    // Calculating the return function

    double CalculateMeanReturn(const std::vector<double>& array, int start, int end);

    // Calculating covariance matrix return function

    double CalculateCovariance(const std::vector<double>& array1,const std::vector<double>& array2, int start, int end);

    // Calculating the total return 





    


private:

    int numberOfDays;
    int outOfSample;

};
#endif
