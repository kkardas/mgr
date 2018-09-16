#pragma once

#include <random>

class RandomValuesGenerator
{
public:
    virtual ~RandomValuesGenerator() = default;
    explicit RandomValuesGenerator(std::mt19937&);

    template <class T>
    std::vector<T> setRandomValues(int dimention)
    {
        std::vector<T> temp;
        for (int i = 0; i < dimention; ++i)
        {
            temp.push_back(generateRandomValue<T>());
        }
        return temp;
    }

    template <class T>
    T generateRandomValue()
    {
        return dis(gen);
    }

    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
};