#pragma once

#include "Cross.h"

class MPMX : public Cross
{
public:
    virtual ~MPMX() = default;

    bool inject(Permutation&,
                Permutation&,
                int,
                int) override;

private:
    static bool isElementContained(int,
                                   const std::vector<int>&);

    void injectNotPresent(std::vector<int>&,
                          Permutation&,
                          int,
                          int);
    int MAX_INT = 20000;
};
