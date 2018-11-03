
/*
 * @file test-gameoflife.cpp
 * @author Fredrik Arhusiander
 * @date 2018-11-01
 * @version 0.1
 */

#include "catch2.hpp"
#include "GameOfLife.h"


SCENARIO("Testing the class GameOfLife") {

    /*
     * Testing constructor
     */
    GIVEN("A standard GameOfLife object") {
        int nrGenerations = 10;
        GameOfLife gol(nrGenerations, "conway", "conway");
        THEN("There should be a population of cells") {
            REQUIRE(gol.getPopulation().getTotalCellPopulation() > 0);
        }


        /*
         * Testing runSimulation()
         */
        THEN("It should run as many generations as set, so that after it stops and we calculate one"
             " more generation, the value of the returned integer should be the original nrGenerations + 1") {
            gol.runSimulation();
            REQUIRE(gol.getPopulation().calculateNewGeneration() == nrGenerations +1);
        }
    }
    GIVEN("We create a GameOfLife object with an incorrect nrOfGenerations value") {
        GameOfLife gol(-10, "conway", "conway");
        THEN("runSimulation() should throw an exception") {
            REQUIRE_THROWS(gol.runSimulation());
        }
    }
    GIVEN("We create a GameOfLife object with incorrect rule names") {
        GameOfLife gol(10, "fredrik", "elin");
        THEN("runSimulation() should throw an exception") {
            REQUIRE_THROWS(gol.runSimulation());
        }
    }
}