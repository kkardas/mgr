#pragma once

#include <vector>
#include <cmath>
#include "Permutation.h"

namespace utils
{
    constexpr double MAX_RANDOM_ARG = 20000;
    constexpr double MIN_RANDOM_ARG = 0;
    constexpr int NUMBER_OF_SEARCH_POINTS = 20;
    constexpr int NUMBER_OF_ITERATIONS = 500;
    constexpr double STEP_RATE = 0.9;
    constexpr int DIMENTIONS = 20;
    constexpr double REVOLUTION_ANGLE = std::pow(-1, DIMENTIONS) * M_PI/2 ;
    typedef std::vector<std::vector<double>> Matrix;

    double goalFunction(const std::vector<double> &coordinates);
    void fillBasicRotationMatrix(int,
                                 int,
                                 Matrix&);
    void fillMatrix(Matrix&);
    Matrix multiplyTwoMatrixes(Matrix&,
                               Matrix&);
    std::vector<double> multiplyMatrixAndVector(Matrix&,
                                               std::vector<double>&);
    std::vector<double> multiplyConstAndVector(double,
                                               std::vector<double>&);
    Matrix multiplyConstAndMatrix(double,
                                  Matrix&);
    std::vector<double> substractVectors(const std::vector<double>&,
                                         const std::vector<double>&);
    Matrix substractMatrixes(const Matrix&,
                             const Matrix&);
    std::vector<double> sumVectors(const std::vector<double>&,
                                   const std::vector<double>&);
    Matrix sumMatrixes(const Matrix&,
                       const Matrix&);
    void printRotationMatrix(std::vector<std::vector<double>>&);
    template <class T>
    void printMatrix(const std::vector<std::vector<T>>& matrix)
    {
        std::cout << "Matrix: " << std::endl;
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix.size(); ++j)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void readFromFile(int&,
                      std::vector<std::vector<int>>&,
                      std::vector<std::vector<int>>&);
    std::vector<int> generatePermutationZero(int);
    std::vector<Permutation> generateStartPermutations(std::vector<int>&,
                                                       std::mt19937&,
                                                       std::vector<std::vector<int>>&,
                                                       std::vector<std::vector<int>>&);
    bool recalculateActualSolution(Permutation&,
                                   std::vector<Permutation>&);
    Matrix generateMatrix(Permutation&);
    std::vector<int> generateVector(Matrix&);
    Matrix normalizeMatrix(Matrix&);
}
