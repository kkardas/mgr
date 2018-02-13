#include <iostream>

#include "Point.h"
#include "RandomValuesGenerator.h"
#include "utils.h"

Point::Point(RandomValuesGenerator& rvg)
{
    coordinates = rvg.setRandomValues();
    functionValue = utils::goalFunction(coordinates);
}

const std::vector<double>& Point::getCoordinates() const
{
    return coordinates;
}

const double Point::getFunctionValue() const
{
    return functionValue;
}

bool Point::operator==(const Point &point) const
{
    return coordinates == point.getCoordinates();
}

void Point::printPoint(std::string str) const
{
    std::cout << str << std::endl;
    for (int i = 0; i < utils::DIMENTIONS; ++i)
    {
        std::cout << "x" << i << ": " << coordinates[i] << std::endl;
    }
    std::cout << "Function value: " << functionValue << std::endl;
}

void Point::setCoordinates(std::vector<double>&& coords)
{
    coordinates = coords;
    functionValue = utils::goalFunction(coordinates);
}
