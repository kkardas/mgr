#pragma once

#include "Cross.h"

static int MAXX_INT = 20000;

class OX1 : public Cross
{
public:
    virtual ~OX1() = default;

    bool inject(Permutation&,
                Permutation&,
                int,
                int) override;

private:
    static bool isElementContained(int,
                                   const std::vector<int>&);

    int getFirstAvailablePosition(const std::vector<int>&,
                                  int);

    int MAX_INT = 20000;
};
