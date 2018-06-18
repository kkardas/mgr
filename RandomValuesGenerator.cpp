#include "RandomValuesGenerator.h"
#include "utils.h"

RandomValuesGenerator::RandomValuesGenerator(std::random_device& rd)
        : gen(rd()),
          dis(0, utils::DIMENTIONS)
{
}
