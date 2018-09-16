#pragma once

class Permutation;

class Cross {
public:
    virtual bool inject(Permutation&,
                        Permutation&,
                        int,
                        int) = 0;
};