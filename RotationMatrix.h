#pragma once

#include "utils.h"
class RotationMatrix
{
public:
    virtual ~RotationMatrix() = default;
    explicit RotationMatrix();
private:
    utils::Matrix rotationMatrix;
};