#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.h"
#include "matrix.h"
#include "returns.h"
#include "portfolioOptimizer.h"
#include <iostream>
#include <fstream>


//g++ -c read_data.cpp
// g++ -c csv.cpp
// g++ -o portfolioSolver csv.o read_data.o
// ./portfolioSolver


double string_to_double(const std::string& s );
void readData(double **data,string fileName);

Matrix CalculateQMatrix(Matrix& array, int start, int end)
{
    int assets = 83;
    int extendedSize = assets + 2;  // Changed from assets+2 to assets+3 to accommodate indices up to assets+2
    Matrix CovarMatrix(extendedSize, extendedSize);
    Returns returnsCalculator;

    vector<double> returnVector(assets,0.0);

    for (int i =  0; i<assets;i++){

        returnVector[i] = returnsCalculator.CalculateMeanReturn(array.getRow(i), start, end);
    }

    for (int i = 0; i < assets; i++)
    
    {
        CovarMatrix.setElement(i, assets, -returnVector[i]);
        CovarMatrix.setElement(i, assets+1, -1);

        CovarMatrix.setElement(assets, i, -returnVector[i]);
        CovarMatrix.setElement(assets+1, i, -1);
        
        for (int j = 0; j < assets; j++)
        {
            CovarMatrix.setElement(i, j, returnsCalculator.CalculateCovariance(array.getRow(i), array.getRow(j), start, end));
        }
    }

    CovarMatrix.setElement(assets, assets, 0);
    CovarMatrix.setElement(assets+1, assets, 0);
    CovarMatrix.setElement(assets, assets+1, 0);
    CovarMatrix.setElement(assets+1, assets+1, 0);

    return CovarMatrix;
}

int main(int argc, char *argv[])
{

    int numberAssets = 83;
    int numberReturns = 700;
    int start = 0;
    int end = 100;

    Matrix matrixReturns(numberAssets, numberReturns);
    Returns returnsCalcualtor;
    Optimizer Optimize(int desiredRETURN, int numberOfAssets, Matrix Qarray);

    // read the data from the file and store it into the return matrix
    string fileName = "asset_returns.csv";
    readData(matrixReturns.matrix, fileName);  // Assuming readData takes Matrix object as argument
    
    Matrix QMatrix = CalculateQMatrix(matrixReturns,start,end);
    
    for (double desiredRETURN = 0; desiredRETURN <0.1;desiredRETURN += 0.005 ) {
        Optimizer optimize(desiredRETURN,numberAssets,QMatrix);
        vector<double> weights = optimize.CGM();
        Matrix CovarMatrixOOS(numberAssets, numberAssets);
        Returns returnsCalculator1;

        vector<double> returnVectorOSS(numberAssets,0.0);
        double returnOOS = 0;
       

        for (int i = 0; i < numberAssets; i++){
            for (int j = 0; j < numberAssets; j++)
            {
                CovarMatrixOOS.setElement(i, j, returnsCalculator1.CalculateCovariance(matrixReturns.getRow(i), matrixReturns.getRow(j), end, end+12));
                returnVectorOSS[i] = returnsCalculator1.CalculateMeanReturn(matrixReturns.getRow(i), end, end+12);

            }
        }
        
    
        double variance = 0.0;
        for (int i = 0; i < weights.size(); ++i) {
            for (int j = 0; j < weights.size(); ++j) {
                variance += weights[i] * CovarMatrixOOS.getMat()[i][j] * weights[j];
            }
        }
        for (int i = 0; i<numberAssets;i++){
            returnOOS += weights[i]*returnVectorOSS[i];
        }
    
        
        // Open the file in append mode
        std::ofstream file("outputMPO.csv", std::ios::app);
        if (!file) {
            std::cerr << "File could not be opened!\n";
        }

        // Write weights
        for (const auto& weight : weights) {
            file << weight << ",";
        }

        // Write variance and returnOOS
        file << variance << "," << returnOOS << "\n";

        // Close the file
        file.close();
    } 
    return 0;
}

double string_to_double( const std::string& s )
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
} 

void readData(double **data,string fileName)
{
	char tmp[20];
	ifstream file (strcpy(tmp, fileName.c_str()));
	Csv csv(file);
	string line;
	if (file.is_open())
	{
		int i=0;
		while (csv.getline(line) != 0) {
         	for (int j = 0; j < csv.getnfield(); j++)
            {
               double temp=string_to_double(csv.getfield(j));
               //cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
               data[j][i]=temp;
            }
            i++;
		}
		
		file.close();
	}
	else {cout <<fileName <<" missing\n";exit(0);}
                                                                 }
                                                                    

