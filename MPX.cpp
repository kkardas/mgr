#include <vector>
#include "Permutation.h"
#include "MPX.h"

bool MPX::inject(Permutation& currentSolution,
                 Permutation& permutation,
                 int indexToStartInjecting,
                 int amountToInject)
{
    auto size = currentSolution.getCoordinates().size();
    auto lastIndexToInject = indexToStartInjecting + amountToInject - 1;
    std::vector<int> result(size, MAX_INT);

    for (int i = 0, j = indexToStartInjecting; j <= lastIndexToInject; ++i, ++j)
    {
        result[i] = currentSolution.getCoordinates2()[j];
    }

    auto indexToStartFilling = amountToInject;
    for (int j = 0; j < size; ++j)
    {
        if (not isElementContained(permutation.getCoordinates2()[j], result))
        {
            result[indexToStartFilling] = permutation.getCoordinates2()[j];
            ++indexToStartFilling;
        }
    }

    permutation.setCoordinates(result);

    permutation.checkConsistency();
    return true;
}

bool MPX::isElementContained(int elem,
                             const std::vector<int> &permutation)
{
    for (int i : permutation)
        if (elem == i)
            return true;

    return false;
}
