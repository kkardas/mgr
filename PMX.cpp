#include <vector>
#include "Permutation.h"
#include "PMX.h"

bool PMX::inject(Permutation& currentSolution,
                 Permutation& permutation,
                 int indexToStartInjecting,
                 int amountToInject)
{
    auto lastIndexToInject = indexToStartInjecting + amountToInject - 1;
    std::vector<int> result{permutation.getCoordinates2()};

    for (int i = indexToStartInjecting; i <= lastIndexToInject; ++i)
    {
        result[i] = currentSolution.getCoordinates2()[i];
    }

    for (int i = 0; i < currentSolution.getCoordinates().size(); ++i)
    {

        if (i < indexToStartInjecting or i > lastIndexToInject)
        {

            auto currentElement = result[i];

            if (isElementContained(currentElement, result, indexToStartInjecting, lastIndexToInject))
            {

                auto replacedElementIndex = getElementIndex(currentElement, result, indexToStartInjecting, lastIndexToInject);

                auto replacedElement = permutation.getCoordinates()[replacedElementIndex];

                while (isElementContained(replacedElement, result, indexToStartInjecting, lastIndexToInject))
                {

                    replacedElementIndex = getElementIndex(replacedElement, result, indexToStartInjecting, lastIndexToInject);
                    replacedElement = permutation.getCoordinates()[replacedElementIndex];

                }

                result[i] = replacedElement;
            }
        }
    }

    permutation.setCoordinates(result);

    permutation.checkConsistency();
    return true;
}

bool PMX::isElementContained(int elem,
                             const std::vector<int> &permutation,
                             int lowerIndex,
                             int upperIndex)
{
    for (int i = lowerIndex; i <= upperIndex; i++)
        if (elem == permutation[i])
            return true;

    return false;
}

int PMX::getElementIndex(int elem,
                         const std::vector<int> &permutation,
                         int lowerIndex,
                         int upperIndex)
{
    for (int i = lowerIndex; i <= upperIndex; i++)
        if (elem == permutation[i])
            return i;

    return -1;
}