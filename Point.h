#pragma once

#include <vector>
#include <string>

class RandomValuesGenerator;

class Point
{
public:
    virtual ~Point() = default;
    explicit Point(RandomValuesGenerator&);

    const std::vector<double>& getCoordinates() const;
    const double getFunctionValue() const;
    void setCoordinates(std::vector<double>&&);
    bool operator==(const Point &point) const;
    void printPoint(std::string str) const;
private:
    std::vector<double> coordinates;
    double functionValue;
};