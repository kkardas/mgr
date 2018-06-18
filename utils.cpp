#include <cstdlib>
#include <algorithm>
#include <random>
#include <iostream>
#include "utils.h"
#include <fstream>

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
        for (int i = 0; i < static_cast<int>(matrix.size()); ++ i) {
            for (int j = 0; j < static_cast<int>(matrix.size()); ++ j)
            {
                if (i == j)
                {
                    matrix[i][j] = 1;
                }
            }
        }
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
//            temp[i] = 1;
            matrix.push_back(temp);
        }
    }

    Matrix multiplyTwoMatrixes(Matrix& firstMatrix,
                               Matrix& secondMatrix)
    {
        Matrix resultMatrix(utils::DIMENTIONS, std::vector<double>(utils::DIMENTIONS, 0));
        for (auto i = 0; i < utils::DIMENTIONS; ++i)
        {
            for (auto j = 0; j < utils::DIMENTIONS; ++j)
            {
                for (auto k = 0; k < utils::DIMENTIONS; ++k)
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

    Matrix substractMatrixes(const Matrix& first,
                             const Matrix& second)
    {
        Matrix tempMatrix;
        for (int i = 0; i < first.size(); ++i)
        {
            std::vector<double> tempVector;
            for (int j = 0; j < first.size(); ++j)
            {
                tempVector.push_back(first[i][j] - second[i][j]);
            }
            tempMatrix.push_back(tempVector);
        }
        return std::move(tempMatrix);
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

    Matrix sumMatrixes(const Matrix& first,
                       const Matrix& second)
    {
        Matrix tempMatrix;
        for (int i = 0; i < first.size(); ++i)
        {
            std::vector<double> tempVector;
            for (int j = 0; j < first.size(); ++j)
            {
                tempVector.push_back(first[i][j] + second[i][j]);
            }
            tempMatrix.push_back(tempVector);
        }
        return std::move(tempMatrix);
    }

    void readFromFile(int& dimention,
                      std::vector<std::vector<int>>& A,
                      std::vector<std::vector<int>>& B)
    {
        std::ifstream file("data.txt");
        file >> dimention;
        std::cout << "wymiar: " << dimention << std::endl;
        for (int i = 0; i < dimention; ++i)
        {
            std::vector<int> tempV;
            for(int j = 0; j < dimention; ++j)
            {
                int temp;
                file >> temp;
                tempV.push_back(temp);
            }
            A.push_back(tempV);
        }

        for (int i = 0; i < dimention; ++i)
        {
            std::vector<int> tempV;
            for(int j = 0; j < dimention; ++j)
            {
                int temp;
                file >> temp;
                tempV.push_back(temp);
            }
            B.push_back(tempV);
        }
        file.close();
    }

    std::vector<int> generatePermutationZero(int dimention)
    {
        auto permutationZero = std::vector<int>();
        for (int i = 0; i < dimention; ++i)
        {
            permutationZero.push_back(i);
        }

        return permutationZero;
    }

    std::vector<Permutation> generateStartPermutations(std::vector<int>& permutationZero,
                                                       std::mt19937& g,
                                                       std::vector<std::vector<int>>& A,
                                                       std::vector<std::vector<int>>& B)
    {
        auto permutations = std::vector<Permutation>();
        for (int i = 0; i < utils::NUMBER_OF_SEARCH_POINTS; ++i)
        {
            permutations.emplace_back(Permutation(permutationZero, g, A, B));
        }
        return permutations;
    }

    bool recalculateActualSolution(Permutation& currentSolution,
                                   std::vector<Permutation>& permutations)
    {
        bool flag = false;
        for (auto& permutation : permutations)
        {
            if (permutation < currentSolution)
            {
                auto temp = currentSolution;
                currentSolution = permutation;
                permutation = temp;
                flag = true;
            }
        }
        return flag;
    }

    Matrix generateMatrix(Permutation& permutation)
    {
        Matrix tempMatrix;
        fillMatrix(tempMatrix);
        auto& coordinates = permutation.getCoordinates();
        for (int i = 0; i < coordinates.size(); ++i)
        {
            tempMatrix[i][coordinates[i]] = 1;
        }
        return tempMatrix;
    }

    std::vector<int> generateVector(Matrix& matrix)
    {
        std::vector<int> temp;
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix.size(); ++j)
            {
                if (matrix[i][j] == 1)
                {
                    temp.push_back(j);
                }
            }
        }
        return temp;
    }

    Matrix normalizeMatrix(Matrix& matrix)
    {
        Matrix temp = matrix;
        for (int i = 0; i < matrix.size(); ++i)
        {
            int columnSum = 0;
            for (auto& j : matrix) {
                columnSum += j[i];
            }

            for (int j = 0; j < matrix.size(); ++j)
            {
                temp[j][i] = matrix[j][i] / columnSum;
            }

            int maxIndex = 0;
            for (int j = 0; j < matrix.size(); ++j)
            {
                if (temp[maxIndex][i] < temp[j][i])
                {
                    maxIndex = j;
                }
            }
            for (int j = 0; j < matrix.size(); ++j)
            {
                if (j == maxIndex)
                {
                    temp[j][i] = 1;
                } else
                {
                    temp[j][i] = 0;
                }
            }
        }
        return temp;
    }

}
