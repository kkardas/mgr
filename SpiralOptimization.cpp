#include "SpiralOptimization.h"
#include "RandomValuesGenerator.h"
#include <algorithm>
#include <iostream>

SpiralOptimization::SpiralOptimization(RandomValuesGenerator& rvg)
    : randomValuesGenerator(rvg),
      center(Point(rvg))
{
}

void SpiralOptimization::generateRandomPoints()
{
    for (int i = 0; i < utils::NUMBER_OF_SEARCH_POINTS; ++i)
    {
        searchPoints.emplace_back(Point(randomValuesGenerator));
    }
    calculateMinArg();

    printAllPoints();
}

void SpiralOptimization::calculateNewPoints()
{
    for (auto& point: searchPoints)
    {
        auto difference = utils::substractVectors(point.getCoordinates(), center.getCoordinates());
        auto multiplication = utils::multiplyMatrixAndVector(rotationMatrix, difference);
        auto multiplication2 = utils::multiplyConstAndVector(utils::STEP_RATE, multiplication);
        point.setCoordinates(std::move(utils::sumVectors(center.getCoordinates(), multiplication2)));
    }
    calculateMinArg();

    printAllPoints();
}


utils::Matrix SpiralOptimization::calculateRotationMatrix(int dimentionsToRotate)
{
    rotationMatrix = utils::Matrix();
    int nonRotated = 0;
    std::vector<int> nieDoRotowania;
    if (dimentionsToRotate == utils::DIMENTIONS - 1)
    {
        nonRotated = randomValuesGenerator.generateRandomValue<int>();
        for (int i = 0; i < nonRotated; ++i)
        {
            nieDoRotowania = randomValuesGenerator.setRandomValues<int>(nonRotated);
        }
    }

    utils::fillMatrix(rotationMatrix);

    for (int i = 0; i < static_cast<int>(rotationMatrix.size()); ++ i)
    {
        for (int j = 0; j < static_cast<int>(rotationMatrix.size()); ++ j)
        {
            if (i == j)
            {
                rotationMatrix[i][j] = 1;
            }
        }
    }

    for (int i = 0; i <= utils::DIMENTIONS - 2; ++i)
    {
        auto result1 = std::find(std::begin(nieDoRotowania), std::end(nieDoRotowania), i);

        if (dimentionsToRotate == utils::DIMENTIONS - 1 and
                result1 != nieDoRotowania.end())
        {
            continue;
        }
        for (int j = 0; j <= i; ++j)
        {
            utils::Matrix tempRotationMatrix;
            utils::fillBasicRotationMatrix(utils::DIMENTIONS - i - 2, utils::DIMENTIONS - j - 1, tempRotationMatrix);
            rotationMatrix = utils::multiplyTwoMatrixes(rotationMatrix, tempRotationMatrix);
        }
    }

//    for (int i = 0; i < utils::DIMENTIONS; ++i)
//    {
//        for (int j = i + 1; j < utils::DIMENTIONS - 1; ++j)
//        {
//            utils::Matrix tempRotationMatrix;
//            utils::fillBasicRotationMatrix(utils::DIMENTIONS - i - 2, utils::DIMENTIONS - j - 1, tempRotationMatrix);
//            rotationMatrix = utils::multiplyTwoMatrixes(rotationMatrix, tempRotationMatrix);
//        }
//    }

    rotationMatrix = utils::multiplyConstAndMatrix(std::pow(-1, utils::DIMENTIONS), rotationMatrix);
    return rotationMatrix;
}

void SpiralOptimization::calculateMinArg()
{
    Point min = center;
    double minVal = center.getFunctionValue();
    for (Point& point: searchPoints)
    {
        double tempVal = point.getFunctionValue();
        if (tempVal < minVal)
        {
            minVal = tempVal;
            min = point;
        }
    }
    if (min.getCoordinates() != center.getCoordinates())
    {
        auto position = std::find(searchPoints.begin(), searchPoints.end(), min);
        searchPoints.erase(position);
        searchPoints.push_back(center);
        center = min;
    }
}

void SpiralOptimization::printAllPoints()
{
    center.printPoint("Center coordinates: ");
    for (int i = 0; i < searchPoints.size(); ++i)
    {
        searchPoints[i].printPoint("Coordinates of point number " + std::to_string(i));
    }
}