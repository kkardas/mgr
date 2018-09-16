#include <vector>
#include "Permutation.h"
#include "OX1.h"

bool OX1::inject(Permutation& currentSolution,
                 Permutation& permutation,
                 int indexToStartInjecting,
                 int amountToInject)
{
    auto size = currentSolution.getCoordinates().size();
    auto lastIndexToInject = indexToStartInjecting + amountToInject - 1;
    std::vector<int> result(size, MAX_INT);

    for (int i = indexToStartInjecting; i <= lastIndexToInject; ++i)
    {
        result[i] = currentSolution.getCoordinates2()[i];
    }

    for (int i = lastIndexToInject + 1; i < size; ++i)
    {
        if (not isElementContained(permutation.getCoordinates2()[i], result))
        {
            auto index = getFirstAvailablePosition(result, lastIndexToInject);
            result[index] = permutation.getCoordinates2()[i];
        }
    }

    for (int i = 0; i <= lastIndexToInject; ++i)
    {
        if (not isElementContained(permutation.getCoordinates2()[i], result))
        {
            auto index = getFirstAvailablePosition(result, indexToStartInjecting);
            result[index] = permutation.getCoordinates2()[i];
        }
    }

    permutation.setCoordinates(result);

    permutation.checkConsistency();
    return true;
}

bool OX1::isElementContained(int elem,
                             const std::vector<int> &permutation)
{
    for (int i : permutation)
        if (elem == i)
            return true;

    return false;
}

int OX1::getFirstAvailablePosition(const std::vector<int> &permutation,
                                   int startPos)
{
    for (int i = startPos + 1; i < permutation.size(); ++i)
    {
        if (permutation[i] == MAX_INT)
            return i;
    }

    for (int j = 0; j <= startPos; ++j)
    {
        if (permutation[j] == MAX_INT)
            return j;
    }

    return MAX_INT;
}