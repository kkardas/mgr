#include <vector>
#include "Permutation.h"
#include "MPMX.h"

bool MPMX::inject(Permutation& currentSolution,
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

    injectNotPresent(result,
                     permutation,
                     indexToStartInjecting,
                     lastIndexToInject);

    for (int i = 0; i < size; ++i)
    {
        if (result[i] == MAX_INT)
        {
            for (int j = 0; j < size; ++j)
            {
                if (not isElementContained(permutation.getCoordinates2()[j], result))
                    result[i] = permutation.getCoordinates2()[j];
            }
        }
    }

    permutation.setCoordinates(result);

    permutation.checkConsistency();
    return true;
}

bool MPMX::isElementContained(int elem,
                              const std::vector<int> &permutation)
{
    for (int i : permutation)
        if (elem == i)
            return true;

    return false;
}

void MPMX::injectNotPresent(std::vector<int>& result,
                            Permutation& permutation,
                            int firstIndexInjected,
                            int lastIndexInjected)
{
    for (int i = 0; i < firstIndexInjected; ++i)
    {
        if (not isElementContained(permutation.getCoordinates2()[i], result))
            result[i] = permutation.getCoordinates2()[i];
    }

    for (int i = lastIndexInjected + 1; i < result.size(); ++i)
    {
        if (not isElementContained(permutation.getCoordinates2()[i], result))
            result[i] = permutation.getCoordinates2()[i];
    }
}