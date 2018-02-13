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


void SpiralOptimization::calculateRotationMatrix()
{
    utils::fillMatrix(rotationMatrix);

    for (int i = 0; i < utils::DIMENTIONS - 1; ++i)
    {
        utils::Matrix tempRotationMatrix;
        utils::fillBasicRotationMatrix(i, i + 1, tempRotationMatrix);
        rotationMatrix = utils::multiplyTwoMatrixes(rotationMatrix, tempRotationMatrix);
    }
    rotationMatrix = utils::multiplyConstAndMatrix(std::pow(-1, utils::DIMENTIONS), rotationMatrix);
    utils::printRotationMatrix(rotationMatrix);
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