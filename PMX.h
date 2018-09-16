#pragma once

#include "Cross.h"

class PMX : public Cross
{
public:
    virtual ~PMX() = default;

    bool inject(Permutation&,
                Permutation&,
                int,
                int) override;

private:
    static bool isElementContained(int,
                                   const std::vector<int>&,
                                   int,
                                   int);
    static int getElementIndex(int,
                               const std::vector<int>&,
                               int,
                               int);
};
