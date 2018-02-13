#include "RandomValuesGenerator.h"
#include "SpiralOptimization.h"
#include <iostream>

int main()
{
    std::random_device rd;
    auto randomValuesGenerator = RandomValuesGenerator(rd);
    auto spiralOptimization = SpiralOptimization(randomValuesGenerator);
    spiralOptimization.generateRandomPoints();
    spiralOptimization.calculateRotationMatrix();

    int iteration{0};
    while (iteration < utils::NUMBER_OF_ITERATIONS)
    {
        std::cout << "Iteration: " << iteration << std::endl;
        spiralOptimization.calculateNewPoints();

        ++iteration;
    }
}