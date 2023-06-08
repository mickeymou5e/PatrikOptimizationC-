#include "portfolioOptimizer.h"
#include <vector>
#include "matrix.h"
#include <sstream>
#include <iostream>

using namespace std;

Optimizer::Optimizer(double desiredRETURN, int numberOfAssets, Matrix Qarray):desiredRETURN(desiredRETURN), numberOfAssets(numberOfAssets),Qarray(Qarray){}

std::vector<double> Optimizer::subtractVectors(const std::vector<double>& vector1, const std::vector<double>& vector2) {
    // Verify the vectors are of the same size.

    if (vector1.size() != vector2.size()) {
        throw std::invalid_argument("Vectors are not the same size subtractVectors.");
    }

    std::vector<double> result(vector1.size());
    for (int i = 0; i < vector1.size(); ++i) {
        result[i] = vector1[i] - vector2[i];
    }

    return result;
}

std::vector<double> Optimizer::addVectors(const std::vector<double>& vector1, const std::vector<double>& vector2) {
    // Verify the vectors are of the same size.
    if (vector1.size() != vector2.size()) {
        throw std::invalid_argument("Vectors are not the same size addVectors.");
    }

    std::vector<double> result(vector1.size());
    for (int i = 0; i < vector1.size(); ++i) {
        result[i] = vector1[i] + vector2[i];
    }

    return result;
}

double Optimizer::dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Vectors are of different sizes dotProduct ");
    }

    double result = 0.0;
    for (int i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

std::vector<double> Optimizer::scalarMultiplier(const std::vector<double>& vec1, const double& scalar) {
    

    std::vector<double> result(vec1.size());
    for (int i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] * scalar;
    }
    return result;
}

std::vector<double> Optimizer::multiplyMatrixByVector(const Matrix& mat, const std::vector<double>& vec) {
    
    int numRows = mat.getRows();
    int numCols = mat.getCols();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (mat.getMat()[i][j] == -2.0) {
                throw std::runtime_error("Matrix contains -2 value, multiplication not allowed.");
            }
        }
    }

    // Initialize the result vector
    std::vector<double> result(numRows, 0.0);

    // Perform the multiplication
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            result[i] += mat.getMat()[i][j] * vec[j];
        }
    }

    return result;
}

std::vector<double> Optimizer::multiplyVectorByMatrix(const std::vector<double>& vec,const Matrix& mat) {
    
    int numRows = mat.getRows();
    int numCols = mat.getCols();
    // Initialize the result vector
    std::vector<double> result(numRows, 0.0);

    // Perform the multiplication
    for (int i = 0; i < numCols; ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            result[i] += vec[j]*mat.getMat()[j][i] ;
        }
    }

    return result;
}


std::vector<double> Optimizer::CGM() {

    vector<double> vectorB(numberOfAssets+2,0.0);
    vectorB[numberOfAssets] = -desiredRETURN;
    vectorB[numberOfAssets+1] = -1;
    cout << desiredRETURN;

    vector<double> vectorX(numberOfAssets+2, 0.0);

    for (int i = 0; i < numberOfAssets; i++) {
        vectorX[i] = 1.0/numberOfAssets;
    }
    vectorX[numberOfAssets] = 0;
    vectorX[numberOfAssets+1] = 0;

    std::vector<double> vectorS = subtractVectors(vectorB, multiplyMatrixByVector(Qarray, vectorX));
    std::vector<double> vectorP = vectorS;
    
    double residuals = this-> dotProduct(vectorS, vectorS);

    while (residuals > 10e-6){

        std::vector<double> pQ = this->multiplyVectorByMatrix(vectorP,Qarray);
        double alpha = residuals / this->dotProduct(pQ, vectorP);

        vectorX = addVectors(vectorX, scalarMultiplier(vectorP, alpha));
        //cout << vectorB[83];
        std::vector<double> Qp = this->multiplyMatrixByVector(Qarray,vectorP);

        vectorS = subtractVectors(vectorS, scalarMultiplier(Qp, alpha));

        double beta = (this->dotProduct(vectorS,vectorS)/residuals);
        vectorP = addVectors(vectorS, scalarMultiplier(vectorP, beta));
        residuals = this->dotProduct(vectorS,vectorS);
    }
    
    vectorX.resize(numberOfAssets);

    return vectorX;
}
