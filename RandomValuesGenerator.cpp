#include "RandomValuesGenerator.h"
#include "utils.h"

RandomValuesGenerator::RandomValuesGenerator(std::mt19937& rd)
        : gen(rd),
          dis(0, utils::DIMENTIONS)
{
}
