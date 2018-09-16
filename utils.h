#pragma once

#include <vector>
#include <cmath>
#include "Permutation.h"

namespace utils
{
    enum class InjectionCalculationType
    {
        LINEAR,
        QUADRATIC, // (1 / dimentions ^ 2) * x ^ 2
        NEGATIVE_QUADRATIC, // (1 - b) / dimentions * x ^ 2 + b * x
        CUBIC
    };

    constexpr double MAX_RANDOM_ARG = 20000;
    constexpr double MIN_RANDOM_ARG = 0;
    constexpr int NUMBER_OF_SEARCH_POINTS = 20;
    constexpr int NUMBER_OF_ITERATIONS = 500;
    constexpr double STEP_RATE = 0.7;
    constexpr int DIMENTIONS = 40;
    constexpr double REVOLUTION_ANGLE = std::pow(-1, DIMENTIONS) * M_PI/2 ;
    constexpr bool GENERATE_NEW_PERMUTATIONS = true;
    constexpr bool OPT2_ALGORITHM = true;
    constexpr bool MATRIX_VERSION = true;
    constexpr bool NO_MATRIX_VERSION = false;
    constexpr InjectionCalculationType INJECTION_CALCULATION_TYPE = InjectionCalculationType::NEGATIVE_QUADRATIC;
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

    int calculateAmountToInject(int,
                                int);

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

    void readFromFile(std::string,
                      int&,
                      std::vector<std::vector<int>>&,
                      std::vector<std::vector<int>>&);
    std::vector<int> generatePermutationZero(int);
    std::vector<Permutation> generateStartPermutations(std::vector<int>&,
                                                       std::mt19937&,
                                                       std::vector<std::vector<int>>&,
                                                       std::vector<std::vector<int>>&);
    bool recalculateActualSolution(Permutation&,
                                   std::vector<Permutation>&);
    int calculateHammingDistance(Permutation&,
                                 Permutation&);
    Matrix generateMatrix(Permutation&);
    std::vector<int> generateVector(Matrix&);
    Matrix normalizeMatrix(Matrix&);
}
