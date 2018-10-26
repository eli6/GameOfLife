/**
 * @file
 * @author Fredrik Arhuiander
 * @date 2018-10-25
 * @version 0.1
 * @brief Contains tests for Population.h
 */

#include "catch.hpp"
#include "Cell_Culture/Population.h"

SCENARIO("A population of cells") {
    /*
     * Testing initiatePopulation()
     */
    GIVEN("We create a population") {
        Population population;
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
