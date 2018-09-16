#include <algorithm>
#include "Permutation.h"
#include <stdexcept>

Permutation::Permutation(std::vector<int> p_coordinates,
                         std::mt19937& g,
                         std::vector<std::vector<int>>& p_A,
                         std::vector<std::vector<int>>& p_B)
        : A(p_A),
          B(p_B)
{
    std::shuffle(p_coordinates.begin(), p_coordinates.end(), g);
    coordinates = p_coordinates;
    calculateValue();
}

unsigned long Permutation::calculateValue()
{
    unsigned long value = 0;
    auto dimentions = static_cast<int>(coordinates.size());
    for (int i = 0; i < dimentions; ++i)
    {
        for (int j = 0; j < dimentions; ++j)
        {
            value += A[coordinates[i]][coordinates[j]] * B[i][j];
        }
    }
    functionValue = value;
    return value;
}

std::vector<int>& Permutation::getCoordinates()
{
    return coordinates;
}

std::vector<int> Permutation::getCoordinates2()
{
    return coordinates;
}

int Permutation::getSingleCoordinate(int index)
{
    return coordinates[index];
}

long Permutation::getFunctionValue()
{
    return functionValue;
}

void Permutation::setCoordinates(std::vector<int> p_coordinates)
{
    coordinates = std::move(p_coordinates);
    calculateValue();
}

void Permutation::bestOpt2Algorithm()
{
    std::vector<int> tempCoordinates = coordinates;
    long tempSolution = functionValue;
    for (int i = 0; i < coordinates.size(); ++i)
    {
        for (int j = i + 1; j < coordinates.size(); ++j)
        {
            std::iter_swap(coordinates.begin() + i, coordinates.begin() + j);
            calculateValue();

            if (functionValue < tempSolution)
            {
                tempCoordinates = coordinates;
                tempSolution = functionValue;
            }

            std::iter_swap(coordinates.begin() + j, coordinates.begin() + i);
            calculateValue();
        }
    }
    coordinates = tempCoordinates;
    functionValue = tempSolution;
}

void Permutation::opt2Algorithm()
{
    std::vector<int> tempCoordinates = coordinates;
    long tempSolution = functionValue;
    for (int i = 0; i < coordinates.size(); ++i)
    {
        for (int j = i + 1; j < coordinates.size(); ++j)
        {
            std::iter_swap(coordinates.begin() + i, coordinates.begin() + j);
            calculateValue();

            if (functionValue < tempSolution)
            {
                tempCoordinates = coordinates;
                tempSolution = functionValue;
                break;
            }

            std::iter_swap(coordinates.begin() + j, coordinates.begin() + i);
            calculateValue();
        }
    }
    coordinates = tempCoordinates;
    functionValue = tempSolution;
}

bool Permutation::checkConsistency()
{
    auto size = coordinates.size();
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (coordinates[i] == coordinates[j])
            {
                std::cout << "Permutation is not consistent" << std::endl;
                std::cout << "Doubled: " << coordinates[j] << std::endl;
                std::cout << *this << std::endl;
                throw std::domain_error{""};
            }
        }
    }
    return true;
}


bool Permutation::operator<(const Permutation& permutation)
{
    return functionValue < permutation.functionValue;
}

Permutation& Permutation::operator=(const Permutation& permutation)
{
    if (this != &permutation)
    {
        coordinates = permutation.coordinates;
        functionValue = permutation.functionValue;
        A = permutation.A;
        B = permutation.B;
    }
    return * this;
}


std::ostream& operator<<(std::ostream& os,
                         const Permutation& permutation)
{
    os << "Permutation: " << std::endl;
    for (const int& coordinate : permutation.coordinates)
    {
        os << coordinate << " ";
    }
    os << std::endl;
    os << "Function value: " << permutation.functionValue << std::endl;
    return os;
}
