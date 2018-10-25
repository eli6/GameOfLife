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
            // Testing calculateNewGeneration()
            THEN("The member generation should be set to 1") {
                REQUIRE(population.calculateNewGeneration() == 1);
            }
        }
        WHEN("We initiate the population with the rule 'erik'") {
            population.initiatePopulation("erik");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }
        }
        WHEN("We initiate the population with the rule 'von_neumann'") {
            population.initiatePopulation("on_neumann");
            THEN("There should be a cell population") {
                REQUIRE(population.getTotalCellPopulation() > 0);
            }
        }
    }
}
