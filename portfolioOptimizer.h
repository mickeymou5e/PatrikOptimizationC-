#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "matrix.h"
#include <vector>


class Optimizer
{
    public:
        Optimizer(double desiredRETURN, int numberOfAssets,Matrix Qarray);
        std::vector<double> multiplyMatrixByVector(const Matrix& mat, const std::vector<double>& vectorX);
        std::vector<double> calculateResiduals(Matrix array1,std::vector<double> b, std::vector<double> x);
        std::vector<double> subtractVectors(const std::vector<double>& vector1, const std::vector<double>& vector2);
        double dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2);
        std::vector<double> addVectors(const std::vector<double>& vector1, const std::vector<double>& vector2);
        std::vector<double> scalarMultiplier(const std::vector<double>& vec1, const double& scalar);
        std::vector<double> CGM();
        std::vector<double> multiplyVectorByMatrix(const std::vector<double>& vec,const Matrix& mat);
         




    private:

        double tolerance;
        double desiredRETURN;
        int numberOfAssets;
        Matrix Qarray;
};
#endif 
