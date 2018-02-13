#include "RandomValuesGenerator.h"
#include "utils.h"

RandomValuesGenerator::RandomValuesGenerator(std::random_device& rd)
        : gen(rd()),
          dis(utils::MIN_RANDOM_ARG, utils::MAX_RANDOM_ARG)
{
}

double RandomValuesGenerator::generateRandomValue()
{
    return dis(gen);
}

std::vector<double> RandomValuesGenerator::setRandomValues()
{
    std::vector<double> temp;
    for (int i = 0; i < utils::DIMENTIONS; ++i)
    {
        temp.push_back(generateRandomValue());
    }
    return temp;
}
