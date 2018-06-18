#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <random>

class RandomValuesGenerator;

class Permutation
{
public:
    virtual ~Permutation() = default;
    explicit Permutation(std::vector<int>,
                         std::mt19937&,
                         std::vector<std::vector<int>>&,
                         std::vector<std::vector<int>>&);

    unsigned long calculateValue();
    std::vector<int>& getCoordinates();
    void setCoordinates(std::vector<int>);
    void regenerateSolution();
    bool operator<(const Permutation&);
    Permutation& operator=(const Permutation&);
    friend std::ostream& operator<<(std::ostream&, const Permutation&);

private:
    std::vector<int> coordinates;
    long functionValue;
    std::vector<std::vector<int>>& A;
    std::vector<std::vector<int>>& B;
};