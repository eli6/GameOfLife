/**
 * @file
 * @author Fredrik Arhuiander
 * @date 2018-10-25
 * @version 0.1
 * @brief Contains tests for Population.h
 */

#include "catch2.hpp"
#include "Cell_Culture/Population.h"
#include <typeinfo>

SCENARIO("A population of cells") {
    GIVEN("We create a population") {
        Population population;

        /*
         * Testing constructor
         */
        THEN("There shouln't be a population of cells yet and the rules should not be set") {
            REQUIRE(population.getTotalCellPopulation() == 0);
            REQUIRE(population.getEvenRule() == nullptr);
            REQUIRE(population.getOddRule() == nullptr);
        }

        /*
         * Testing initiatePopulation()
         */
        WHEN("We initiate the population from file with the rule 'conway'") {
            fileName = "../Population_Seed.txt";
            population.initiatePopulation("conway");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }
            THEN("Both rules should be set to 'conway'") {
                REQUIRE(population.getEvenRule()->getRuleName() == "conway");
                REQUIRE(population.getOddRule()->getRuleName() == "conway");
            }
            fileName = ""; // reset fileName
        }

        WHEN("We initiate the population randomly with the rule 'conway'") {
            population.initiatePopulation("conway");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }
            THEN("Both rules should be set to 'conway'") {
                REQUIRE(population.getEvenRule()->getRuleName() == "conway");
                REQUIRE(population.getOddRule()->getRuleName() == "conway");
            }

            /*
             * Testing calculateNewGeneration()
             */
            THEN("The member generation should be set to 1") {
                int newGen = population.calculateNewGeneration();
                REQUIRE(newGen == 1);
                AND_THEN("When we call it again it should be incremented by 1") {
                    REQUIRE(population.calculateNewGeneration() == 2);
                }

                AND_WHEN("We find a Cell that is not alive and has next generation action set to GIVE_CELL_LIFE") {
                    int row = 0;
                    int column = 0;
                    Cell* testCell = nullptr; // create a pointer to a Cell object
                    int height = WORLD_DIMENSIONS.HEIGHT;
                    int width = WORLD_DIMENSIONS.WIDTH;
                    while(row < height && column < width) { // stays within world borders
                        testCell = &population.getCellAtPosition(Point{column, row}); // get reference to a cell
                        // check so that cell is not rim cell, it's not alive, and the next generation action is set to give cell life
                        if(!testCell->isRimCell() && testCell->getColor() == STATE_COLORS.DEAD && testCell->getNextGenerationAction() == GIVE_CELL_LIFE) {
                            break; // break if criteria is met
                        } else if(column != width-1) // increment column until end of width
                            column++;
                        else {
                            column = 0; // if last column is reached, set it to 0 and begin from next row
                            row++;
                        }
                    }

                    AND_WHEN("We call the function") {
                        population.calculateNewGeneration();
                        THEN("The cell should be alive") {
                            REQUIRE(testCell->getColor() == STATE_COLORS.LIVING);
                        }
                    }

                    /*
                     *  Testing getCellAtPosition()
                     */
                    AND_WHEN("We update state and call getCellAtPosition()") {
                        testCell->updateState();
                        THEN("We should get a Cell that is alive at the same position") {
                            REQUIRE(population.getCellAtPosition(Point{column,row}).isAlive());
                        }
                    }
                }

            }


            /*
             * getTotalCellPopulation()
             */
            THEN("The cellpopulation should be the same as the world dimensions") {
                REQUIRE(population.getTotalCellPopulation() == WORLD_DIMENSIONS.HEIGHT * WORLD_DIMENSIONS.WIDTH);
            }


        }
        /*
         * Testing to initiate with different rule name combinations
         */
        WHEN("We initiate the population with the rule 'erik'") {
            population.initiatePopulation("erik");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }
        }
        WHEN("We initiate the population with the rule 'von_neumann'") {
            population.initiatePopulation("von_neumann");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }
        }
        WHEN("We initiate population with two rule names") {
            vector<string> v{"conway", "erik", "von_neumann"};
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(i!=j) { // to only test when the rule names differ
                        population.initiatePopulation(v[i], v[j]);
                        THEN("There should be a cell population with the rules " + v[i] + " and " + v[j]) {
                            REQUIRE(population.getTotalCellPopulation() > 0);
                        }
                    }
                }
            }
        }
    }
}
