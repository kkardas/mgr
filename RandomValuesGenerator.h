#pragma once

#include <random>

class RandomValuesGenerator
{
public:
    virtual ~RandomValuesGenerator() = default;
    explicit RandomValuesGenerator(std::random_device&);
    double generateRandomValue();
    std::vector<double> setRandomValues();
private:
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
};