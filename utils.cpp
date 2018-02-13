#include <cstdlib>
#include <algorithm>
#include <random>
#include <iostream>
#include "utils.h"

namespace utils
{
    double goalFunction(const std::vector<double> &coordinates)
    {
        double result{0.0};
        for (auto& coordinate: coordinates)
        {
            result += coordinate * coordinate;
        }
        return result;
    }

    void fillBasicRotationMatrix(int firstDimention,
                                 int secondDimention,
                                 Matrix& matrix)
    {
        fillMatrix(matrix);
        matrix[firstDimention][firstDimention] = cos(REVOLUTION_ANGLE);
        matrix[firstDimention][secondDimention] = -sin(REVOLUTION_ANGLE);
        matrix[secondDimention][firstDimention] = sin(REVOLUTION_ANGLE);
        matrix[secondDimention][secondDimention] = cos(REVOLUTION_ANGLE);
    }

    void fillMatrix(Matrix& matrix)
    {
        for (int i = 0; i < DIMENTIONS; ++ i)
        {
            std::vector<double> temp(DIMENTIONS, 0.0);
            temp[i] = 1;
            matrix.push_back(temp);
        }
    }

    Matrix multiplyTwoMatrixes(Matrix& firstMatrix,
                               Matrix& secondMatrix)
    {
        Matrix resultMatrix(utils::DIMENTIONS, std::vector<double>(utils::DIMENTIONS, 0));
        for (auto j = 0; j < utils::DIMENTIONS; ++j)
        {
            for (auto k = 0; k < utils::DIMENTIONS; ++k)
            {
                for (auto i = 0; i < utils::DIMENTIONS; ++i)
                {
                    resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
                }
            }
        }
        return std::move(resultMatrix);
    }

    std::vector<double> multiplyMatrixAndVector(Matrix& matrix,
                                                std::vector<double>& vector)
    {
        std::vector<double> resultVector(utils::DIMENTIONS, 0);
        for (auto j = 0; j < utils::DIMENTIONS; ++j)
        {
            for (auto k = 0; k < utils::DIMENTIONS; ++k)
            {
                resultVector[j] += matrix[j][k] * vector[k];
            }
        }
        return std::move(resultVector);
    }

    std::vector<double> multiplyConstAndVector(double value,
                                               std::vector<double>& vector)
    {
        std::vector<double> resultVector(utils::DIMENTIONS, 0);
        for (auto j = 0; j < utils::DIMENTIONS; ++j)
        {
            resultVector[j] += vector[j] * value;
        }
        return std::move(resultVector);
    }

    Matrix multiplyConstAndMatrix(double value,
                                  Matrix& matrix)
    {
        Matrix resultMatrix(utils::DIMENTIONS, std::vector<double>(utils::DIMENTIONS, 0));
        for (auto i = 0; i < utils::DIMENTIONS; ++i)
        {
            for (auto j = 0; j < utils::DIMENTIONS; ++j)
            {
                resultMatrix[i][j] += matrix[i][j] * value;
            }
        }
        return std::move(resultMatrix);
    }

    void printRotationMatrix(Matrix& rotationMatrix)
    {
        std::cout << "Rotation matrix: " << std::endl;
        std::cout.precision(2);
        for (int i = 0; i < DIMENTIONS; ++i)
        {
            for (int j = 0; j < DIMENTIONS; ++j)
            {
                std::cout << std::fixed  << rotationMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<double> substractVectors(const std::vector<double>& firstVector,
                                         const std::vector<double>& secondVector)
    {
        std::vector<double> temp;
        std::set_difference(
                firstVector.begin(),
                firstVector.end(),
                secondVector.begin(),
                secondVector.end(),
                std::back_inserter(temp)
        );
        return std::move(temp);
    }

    std::vector<double> sumVectors(const std::vector<double>& firstVector,
                                   const std::vector<double>& secondVector)
    {
        std::vector<double> temp;
        for (int i = 0; i < firstVector.size(); ++i)
        {
            temp.push_back(firstVector[i] + secondVector[i]);
        }
        return std::move(temp);
    }
}
