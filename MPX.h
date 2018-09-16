#pragma once

#include "Cross.h"

class MPX : public Cross
{
public:
    virtual ~MPX() = default;

    bool inject(Permutation&,
                Permutation&,
                int,
                int) override;

private:
    static bool isElementContained(int,
                                   const std::vector<int>&);

    int MAX_INT = 20000;
};
