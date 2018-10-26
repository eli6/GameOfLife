/**
 * @file
 * @author Fredrik Arhuiander
 * @date 2018-10-25
 * @version 0.1
 * @brief Contains tests for Population.h
 */

#include "catch.hpp"
#include "Cell_Culture/Population.h"
#include <typeinfo>

SCENARIO("A population of cells") {
    GIVEN("We create a population") {
        Population population;
        /*
         * Testing initiatePopulation()
         */
        WHEN("We initiate the population with the rule 'conway'") {
            population.initiatePopulation("conway");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }

            /*
             * Testing calculateNewGeneration()
             */
            THEN("The member generation should be set to 1") {
                REQUIRE(population.calculateNewGeneration() == 1);
                AND_THEN("When we call it again it should be incremented by 1") {
                    REQUIRE(population.calculateNewGeneration() == 2);
                }
            }
            AND_WHEN("We find a Cell that is not alive and has next generation action set to GIVE_CELL_LIFE") {
                int row = 0;
                int column = 0;
                Cell* testCell = nullptr; // create a pointer to a Cell object
                while(!(row <= WORLD_DIMENSIONS.HEIGHT + 1 | column <= WORLD_DIMENSIONS.WIDTH + 1)) { // stays within world borders
                    testCell = &population.getCellAtPosition(Point{column, row}); // get reference to a cell
                    if(!testCell->isRimCell() && !testCell->isAlive() && testCell->getNextGenerationAction() == GIVE_CELL_LIFE)
                        break; // break if criteria is met
                    row++;
                    column++;
                }
                /*
                 * @bug false is returned
                 */
                AND_WHEN("We call the function") {
                    population.calculateNewGeneration();
                    THEN("The cell should be alive") {
                        REQUIRE(testCell->isAlive());
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

            /*
             * getTotalCellPopulation()
             */
            THEN("The cellpopulation should be the same as the world dimensions") {
                REQUIRE(population.getTotalCellPopulation() == (WORLD_DIMENSIONS.HEIGHT +2) * (WORLD_DIMENSIONS.WIDTH +2) );
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
                        THEN("There should be a cell population") {
                            REQUIRE(population.getTotalCellPopulation() > 0);
                        }
                    }
                }
            }
        }
    }
}
