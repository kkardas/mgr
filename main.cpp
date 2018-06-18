#include "RandomValuesGenerator.h"
#include "SpiralOptimization.h"
#include <algorithm>

int main()
{
    std::random_device rd;
    std::mt19937 g(rd());
    auto randomValuesGenerator = RandomValuesGenerator(rd);
    auto spiralOptimization = SpiralOptimization(randomValuesGenerator);
//    spiralOptimization.generateRandomPoints();
//
//    int iteration{0};
//    while (iteration < utils::NUMBER_OF_ITERATIONS)
//    {
//        std::cout << "Iteration: " << iteration << std::endl;
//        spiralOptimization.calculateNewPoints();
//
//        ++iteration;
//    }




    std::vector<std::vector<int>> A, B;
    int dimention = 0;

    utils::readFromFile(dimention, B, A);
    auto rotationMatrix = spiralOptimization.calculateRotationMatrix(dimention);

    utils::printMatrix<int>(A);
    std::cout << std::endl;
    utils::printMatrix<int>(B);

//    std::vector<int> a = {6,4,11,1,0,2,8,10,9,5,7,3};
//    Permutation q = Permutation(a, g, A, B);
//    q.setCoordinates(a);
//    std::cout << "Wynik: " << q << std::endl;





//    for (int z = 1; z < 20; ++z)
//    {
//        double step = z * 0.05;

        int currentIteration = 0;
        int dk = 0;
        int noChange = 0;
        int generateNew = 0;
        auto permutationZero = utils::generatePermutationZero(dimention);

        auto currentSolution = Permutation(permutationZero, g, A, B);
        auto permutations = utils::generateStartPermutations(permutationZero, g, A, B);

        utils::recalculateActualSolution(currentSolution, permutations);

//        std::cout << "Aktualne rozwiazanie: " << std::endl;
//        std::cout << currentSolution;
//
//        std::cout << "Permutacje startowe: " << std::endl;
//        for (int i = 0; i < utils::NUMBER_OF_SEARCH_POINTS; ++i)
//        {
//            std::cout << permutations[i];
//        }
//        std::cout << std::endl;
//        std::cout << std::endl;

        while (currentIteration < utils::NUMBER_OF_ITERATIONS) {
            double r = 0.0;
//            std::cout << "dk: " << dk << std::endl;
//            std::cout << "k: " << currentIteration << std::endl;
            if (currentIteration >= dk && currentIteration <= dk + 2 * dimention - 1)
            {
                r = 1;
            }
            else if (currentIteration >= dk + 2 * dimention)
            {
                r = utils::STEP_RATE;
            }
            auto currentSolutionMatrix = utils::generateMatrix(currentSolution);
//        std::cout << "current solution matrix: " << std::endl;
//        utils::printMatrix(currentSolutionMatrix);
            std::vector<utils::Matrix> permutationMatrixes;

            for (auto& permutation: permutations)
            {
                permutationMatrixes.push_back(utils::generateMatrix(permutation));
            }

            for (auto& permutationMatrix: permutationMatrixes)
            {
                auto difference = utils::substractMatrixes(permutationMatrix, currentSolutionMatrix);
//            std::cout << "difference: " << std::endl;
//            utils::printMatrix(difference);
                auto multiplication = utils::multiplyTwoMatrixes(rotationMatrix, difference);
//            std::cout << "multiplication: " << std::endl;
//            utils::printMatrix(multiplication);
                auto multiplication2 = utils::multiplyConstAndMatrix(r, multiplication);
//            std::cout << "multiplication2: " << std::endl;
//            utils::printMatrix(multiplication2);
                auto solution = utils::sumMatrixes(currentSolutionMatrix, multiplication2);
//            std::cout << "solution: " << std::endl;
//            utils::printMatrix(solution);
                permutationMatrix = utils::normalizeMatrix(solution);
//            std::cout << "permutationMatrix: " << std::endl;
//            utils::printMatrix(permutationMatrix);
            }

            for (int i = 0; i < permutationMatrixes.size(); ++i)
            {
                permutations[i].setCoordinates(utils::generateVector(permutationMatrixes[i]));
                permutations[i].calculateValue();
            }

            if (utils::recalculateActualSolution(currentSolution, permutations))
            {
                dk = currentIteration + 1;
            } else
            {
                ++noChange;
                ++generateNew;
            }

//            std::cout << "Aktualne rozwiazanie: " << std::endl;
//            std::cout << currentSolution;
//            std::cout << "Aktualne permutacje: " << std::endl;
//            for (int i = 0; i < utils::NUMBER_OF_SEARCH_POINTS; ++i)
//            {
//                std::cout << permutations[i];
//            }
//            std::cout << std::endl;
//            std::cout << std::endl;

            if (noChange == 25)
            {
                std::cout << std::endl;
                std::cout << "Iteracja: " << currentIteration << std::endl;
                std::cout << "Aktualne rozwiązanie: " << std::endl << currentSolution << std::endl;
                std::cout << std::endl;

                noChange = 0;
                std::cout << currentSolution;

                currentSolution.regenerateSolution();
                std::cout << "Przegenerowało" << std::endl;
                utils::recalculateActualSolution(currentSolution, permutations);

                std::cout << currentSolution;
            }
            if (generateNew == 50)
            {
                generateNew = 0;
                permutations = utils::generateStartPermutations(currentSolution.getCoordinates(), g, A, B);
            }
//            rotationMatrix = spiralOptimization.calculateRotationMatrix(dimention - 1);
            ++currentIteration;
        }
        std::cout << "Końcowe rozwiazanie: " << std::endl;
//        std::cout << "step: " << step << std::endl;

        std::cout << currentSolution;
//    }


}