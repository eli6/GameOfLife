/**
 * @file
 * @author Fredrik Arhuiander
 * @date 2018-10-25
 * @version 0.1
 * @brief Contains tests for Population.h
 */

#include "catch.hpp"

SCENARIO("A population of cells") {
    /*
     * Testing constructor
     */
    GIVEN("We create a population") {
        Population population;
        THEN("The member generation should be set to 0") {
            REQUIRE(population.calculateNewGeneration() == 1) //frågan är, går det att köra denna?
        }

        /*
         * Testing initiatePopulation()
         */
        WHEN("We initiate the population with the rule 'conway'") {
            population.initiatePopulation(conway)
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0)
            }
        }
        WHEN("We initiate the population with the rule 'erik'") {
            population.initiatePopulation(erik)
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0)
            }
        }
        WHEN("We initiate the population with the rule 'von_neumann'") {
            population.initiatePopulation(von_neumann)
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0)
            }
        }
    }
}
