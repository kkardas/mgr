#include "RandomValuesGenerator.h"
#include "SpiralOptimization.h"
#include "PMX.h"
#include "MPMX.h"
#include "MPX.h"
#include "OX1.h"
#include <algorithm>
#include <fstream>
//#include <bits/shared_ptr.h>
#include <memory>
#include <string>

int main()
{
    auto inputDataArray = {"Testy/Bur26a.txt", "Testy/Bur26b.txt", "Testy/Bur26c.txt", "Testy/Bur26d.txt",
                           "Testy/Bur26e.txt", "Testy/Bur26f.txt", "Testy/Bur26g.txt", "Testy/Bur26h.txt",
                           "Testy/Chr22a.txt", "Testy/Chr22b.txt", "Testy/Esc32a.txt", "Testy/Esc32b.txt",
                           "Testy/Esc32c.txt", "Testy/Esc32d.txt", "Testy/Esc32e.txt", "Testy/Esc32g.txt",
                           "Testy/Esc32h.txt", "Testy/Esc64a.txt", "Testy/Kra30a.txt", "Testy/Kra30b.txt", "Testy/Lipa30a.txt",
                           "Testy/Lipa30b.txt", "Testy/Lipa40a.txt", "Testy/Lipa40b.txt", "Testy/Lipa50a.txt",
                           "Testy/Lipa50b.txt", "Testy/Lipa60a.txt", "Testy/Lipa60b.txt", "Testy/Sko42.txt",
                           "Testy/Sko49.txt", "Testy/Sko56.txt", "Testy/Ste36a.txt", "Testy/Ste36b.txt",
                           "Testy/Ste36c.txt","Testy/Tho30.txt","Testy/Tho40.txt","Testy/Wil50.txt"};
    auto input = {"Testy/Tho40.txt"};
    for (auto & in: input)
    {
        auto inputData = "Testy/Esc32a.txt";
        auto outputFile = "wykres.txt";
        std::ofstream output{outputFile};

        auto csvFile = "file.csv";
        std::ofstream csvOut{csvFile};

        std::random_device rd{};

        std::array<int, 3> posiew{50, 100, 200};
        std::array<double, 3> h{0.7, 0.85, 0.95};

        std::mt19937 g(posiew[0]);
//    std::mt19937 g(rd);
        auto randomValuesGenerator = RandomValuesGenerator(g);
        auto spiralOptimization = SpiralOptimization(randomValuesGenerator);

        std::vector<long> solutions;

        int iterationNumber{0};
        std::vector<std::vector<int>> A, B;
        int dimention = utils::DIMENTIONS;

        utils::readFromFile(in, dimention, B, A);

//    utils::printMatrix<int>(A);
//    std::cout << std::endl;
//    utils::printMatrix<int>(B);
        std::shared_ptr<Cross> cross = std::make_shared<MPMX>();
        std::mt19937 gen(rd());

        auto permutationZero = utils::generatePermutationZero(dimention);

        std::mt19937 g1(posiew[0]);
        auto currentSolution1 = Permutation(permutationZero, g, A, B);
        auto permutations1 = utils::generateStartPermutations(permutationZero, g, A, B);

        std::mt19937 g2(posiew[1]);
        auto currentSolution2 = Permutation(permutationZero, g2, A, B);
        auto permutations2 = utils::generateStartPermutations(permutationZero, g, A, B);

        std::mt19937 g3(posiew[2]);
        auto currentSolution3 = Permutation(permutationZero, g3, A, B);
        auto permutations3 = utils::generateStartPermutations(permutationZero, g, A, B);

        std::vector<std::vector<Permutation>> permutationsBase;
        permutationsBase.push_back(permutations1);
        permutationsBase.push_back(permutations2);
        permutationsBase.push_back(permutations3);
        std::vector<Permutation> currentSolutionsBase;
        currentSolutionsBase.push_back(currentSolution1);
        currentSolutionsBase.push_back(currentSolution2);
        currentSolutionsBase.push_back(currentSolution3);
        long bestSolution = 0;
        auto bestIter = 0;
        for (int w = 0; w < 3; ++w) {
            for (int e = 0; e < 3; ++e) {
                for (int q = 0; q < 3; ++q) {
                    auto rotationMatrix = spiralOptimization.calculateRotationMatrix(dimention);
                    int currentIteration = 0;
                    int dk = 0;
                    int noChange = 0;
                    int generateNew = 0;

                    auto permutations = permutationsBase[q];
                    auto currentSolution = currentSolutionsBase[q];

                    utils::recalculateActualSolution(currentSolution, permutations);

                    std::mt19937 gen2(posiew[e]);

                    while (currentIteration < utils::NUMBER_OF_ITERATIONS) {
                        double r = 0.0;

                        if (currentIteration >= dk && currentIteration <= dk + 2 * dimention - 1) {
                            r = 1;
                        } else if (currentIteration >= dk + 2 * dimention) {
                            r = h[w];
                        }

                        auto currentSolutionMatrix = utils::generateMatrix(currentSolution);

                        std::vector<utils::Matrix> permutationMatrixes;

                        for (auto &permutation: permutations) {
                            if (permutation.getFunctionValue() == currentSolution.getFunctionValue()) {
                                permutation = Permutation(permutationZero, g, A, B);
                            }
                            permutationMatrixes.push_back(utils::generateMatrix(permutation));
                        }

                        for (auto &permutationMatrix: permutationMatrixes) {
                            auto difference = utils::substractMatrixes(permutationMatrix, currentSolutionMatrix);
                            auto multiplication = utils::multiplyTwoMatrixes(rotationMatrix, difference);
                            auto multiplication2 = utils::multiplyConstAndMatrix(r, multiplication);
                            auto solution = utils::sumMatrixes(currentSolutionMatrix, multiplication2);
                            permutationMatrix = utils::normalizeMatrix(solution);
                        }

                        for (int i = 0; i < permutationMatrixes.size(); ++i) {
                            permutations[i].setCoordinates(utils::generateVector(permutationMatrixes[i]));
                            permutations[i].calculateValue();
                        }

                        if (utils::recalculateActualSolution(currentSolution, permutations)) {
                            iterationNumber = currentIteration;
                            dk = currentIteration + 1;
                        } else {
                            ++noChange;
                            ++generateNew;
                        }

                        output << permutations[0].getFunctionValue() << " " << currentSolution.getFunctionValue();
                        output << std::endl;

                        for (int i = 0; i < utils::NUMBER_OF_SEARCH_POINTS; ++i) {
                            csvOut << permutations[i].getFunctionValue() << ',';
                        }
                        csvOut << std::endl;


                        if (noChange == 25 && utils::OPT2_ALGORITHM) {
                            noChange = 0;

                            for (auto &permutation: permutations) {
                                permutation.bestOpt2Algorithm();
                            }

                            if (utils::recalculateActualSolution(currentSolution, permutations)) {
                                iterationNumber = currentIteration;
                            }
                        }
                        if (generateNew == 50 && utils::GENERATE_NEW_PERMUTATIONS) {
                            generateNew = 0;
                            permutations = utils::generateStartPermutations(currentSolution.getCoordinates(), g, A, B);
                        }
                        if (noChange % 10 == 0) {

                            std::uniform_int_distribution<> dis(0,
                                                                static_cast<int>(permutations[0].getCoordinates().size() -
                                                                                 1));

                            auto a = dis(gen2);
                            auto b = dis(gen2);
                            while (a == b) {
                                b = dis(gen2);
                            }
                            spiralOptimization.swapRowsAndCols(rotationMatrix, a, b);
//                rotationMatrix = spiralOptimization.calculateRotationMatrix(dimention - 1);
                        }
                        ++currentIteration;
                        if (bestSolution == 0 || bestSolution > currentSolution.getFunctionValue())
                        {
                            bestSolution = currentSolution.getFunctionValue();
                            bestIter = iterationNumber;
                        }
                    }
                    std::cout << currentSolution.getFunctionValue() << " ";

//            std::cout << "Końcowe rozwiazanie: " << std::endl;
//            std::cout << "h: " << h[w] << " posiew: " << posiew[q] << std::endl;
//            std::cout << currentSolution << std::endl;
//            std::cout << "Osiągnięte w iteracji: " << iterationNumber << std::endl;
                }
            }
        }
        std::cout << std::endl << "problem: " << in << std::endl << "best: " << bestSolution << " w iteracji: " << bestIter << std::endl;
    }


















//    if (utils::NO_MATRIX_VERSION) {
//        auto currentIteration = 0;
//        auto permutationZero = utils::generatePermutationZero(dimention);
//
//        auto currentSolution = Permutation(permutationZero, g, A, B);
//        auto permutations = utils::generateStartPermutations(permutationZero, g, A, B);
//
//        utils::recalculateActualSolution(currentSolution, permutations);
//        auto size = static_cast<int>(permutations[0].getCoordinates().size());
//
//        while (currentIteration < utils::NUMBER_OF_ITERATIONS) {
//
//            for (auto &permutation : permutations) {
//                auto hammingDistance = utils::calculateHammingDistance(currentSolution, permutation);
//
//                if (0 == hammingDistance)
//                {
//                    permutation = Permutation(permutationZero, g, A, B);
//                    hammingDistance = utils::calculateHammingDistance(currentSolution, permutation);
//                }
//
//                auto amountToInject = utils::calculateAmountToInject(hammingDistance, size);
////                auto amountToInject = static_cast<int>(permutations[0].getCoordinates().size() - hammingDistance);
//
//                std::uniform_int_distribution<> dis(0,
//                    static_cast<int>(permutations[0].getCoordinates().size()) - amountToInject -1);
//
//                if (amountToInject == 0)
//                    amountToInject = 1;
//
//                auto indexToStartInjecting = dis(gen);
//
//                cross->inject(currentSolution, permutation, indexToStartInjecting, amountToInject);
//
//                permutation.opt2Algorithm();
//
//                permutation.calculateValue();
//            }
//
//            utils::recalculateActualSolution(currentSolution, permutations);
//
//            ++currentIteration;
//
//            output << permutations[0].getFunctionValue() << " " << currentSolution.getFunctionValue();
//            output << std::endl;
//
//            std::cout << std::endl;
//            std::cout << "Iteracja: " << currentIteration << std::endl;
//            std::cout << "Aktualne rozwiązanie: " << std::endl << currentSolution << std::endl;
//            std::cout << std::endl;
//        }
//        std::cout << "Końcowe rozwiazanie: " << std::endl;
//        std::cout << currentSolution << std::endl;
//    }
//    csvOut.close();
//    output.close();
}