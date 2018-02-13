#pragma once

#include <vector>
#include <cmath>

namespace utils
{
    constexpr double MAX_RANDOM_ARG = 20000;
    constexpr double MIN_RANDOM_ARG = 0;
    constexpr int NUMBER_OF_SEARCH_POINTS = 1;
    constexpr int NUMBER_OF_ITERATIONS = 1000;
    constexpr double STEP_RATE = 0.75;
    constexpr int DIMENTIONS = 2;
    constexpr double REVOLUTION_ANGLE = std::pow(-1, DIMENTIONS) * M_PI/2;
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
    std::vector<double> sumVectors(const std::vector<double>&,
                                   const std::vector<double>&);
    void printRotationMatrix(std::vector<std::vector<double>>&);
}
