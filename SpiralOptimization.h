#pragma once

#include "Point.h"
#include "utils.h"

class Point;
class RandomValuesGenerator;

class SpiralOptimization
{
public:
    virtual ~SpiralOptimization() = default;
    explicit SpiralOptimization(RandomValuesGenerator&);
    void generateRandomPoints();
    void calculateRotationMatrix();
    void calculateNewPoints();
private:
    void calculateMinArg();
    void printAllPoints();

    RandomValuesGenerator& randomValuesGenerator;
    Point center;
    std::vector<Point> searchPoints;
    utils::Matrix rotationMatrix;
};