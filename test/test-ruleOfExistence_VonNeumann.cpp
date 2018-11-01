/**
* @file Cell.h
 * @author
 * @author Elin Fritiofsson
 * @date 23 october 2018
 * @version 0.1
 * @brief Contains all the tests for the Cell class constructor
*/

#include "catch2.hpp"
#include <iostream>
#include "../include/GoL_Rules/RuleOfExistence_VonNeumann.h"


/***********************************
* TESTING CONSTRUCTOR WITH DIFFERENT PARAMETERS
***********************************/
SCENARIO("Testing von Neumann constructor"){
    GIVEN("a small cell population"){
        Point point1 = {1,1};
        Point point2 = {0,0};
        Cell cell1(false);
        Cell cell2(true);
        map<Point,Cell> cells;

        cells[point1] = cell1;
        cells[point2] = cell2;

        WHEN("we initialize our rule with these cells"){
            auto vonNeumann = new RuleOfExistence_VonNeumann(cells);
            THEN("we should be able to retrive the first, non-rim cell"){
                REQUIRE_FALSE(vonNeumann->getCellAtPosition(point1).isRimCell());
            }
            THEN("we should also be able to retrieve the second, which is a rim cell"){
                REQUIRE(vonNeumann->getCellAtPosition(point2).isRimCell());

            }
            THEN("it should have the right population limits set"){
                REQUIRE(vonNeumann->getPopLimits().UNDERPOPULATION == 2);
                REQUIRE(vonNeumann->getPopLimits().OVERPOPULATION == 3);
                REQUIRE(vonNeumann->getPopLimits().RESURRECTION == 3);

            }

            THEN("it should have directions set to all directions"){

                //vonNeumann only detects 4 directions
                REQUIRE(vonNeumann->getDirections().size() == 4);


            }

            THEN("its rule name should be 'von_neumann'"){
                REQUIRE (vonNeumann->getRuleName() == "von_neumann");
            }
        }
    }
}




/***********************************
* TESTING EXECUTE RULE AND DEPENDENT FUNCTIONS
***********************************/
SCENARIO("Testing executeRule() for vonNeumann") {
    GIVEN("a VonNeumann Rule of Existence") {


        //We declare the objects needed for testing
        // we need 8 points to create the 8 neighbors

        //we create 8 scenarios with j+1 number of living cells.
        WHEN("we create a test cell population of 5x5 cells and create 1-8 neighbours for the middle cell in a for loop") {
            for (int j = 0; j < 9; j++) {
                map<Point, Cell> cells;
                //int living = 0;

                //count how many living cells we produce since we want to test 1-8 living cells in our matrix
                int counter = 0;

                int neighboursToCount = 0;

                //we generate a small 5x5 cell population
                for (int row = 0; row <= 4; row++) {
                    for (int column = 0; column <= 4; column++) {


                        if (column == 0 || row == 0 || column == 4 ||
                            row == 4) {  // if cell should be a rim cell, create a rim cell
                            cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                        } else if (counter <= j) { // If cell is an ordinary cell
                            cells[Point{column, row}] = Cell(false,
                                                             GIVE_CELL_LIFE); // create a ordinary living cell

                            //increment the counter for number of living cells we have in this run (we want to stop at j living cells).
                            counter++;

                            if(counter != 1 && counter%2 == 0){
                                neighboursToCount++;
                            }

                        } else {
                            //if we already have our j living neighbours in this iteration, create a dead neighbour instead.
                            cells[Point{column, row}] = Cell(false, KILL_CELL);
                        }
                    }


                }




                //we wrap this in a DYNAMIC_SECTION so that it can be looped.
                DYNAMIC_SECTION("Looped section " << j) {
                    AND_WHEN(
                            "we initiate a new RuleOfExistence_VonNeumann instance with the above cells and get the position of the cell int he middle") {
                        auto *vonNeumann = new RuleOfExistence_VonNeumann(cells);

                        //TESTING counting of neighbors using cell in the middle of matrix.
                        Point middleCellPosition = {2, 2};
                        int neighbours = 0;

                        THEN("the middle cell should have between 1 and 4 neighbours, one more detected neighbour is created for every even j value. diagonal cells should not be detected as living neighbours") {
                            //if we have produced less than 5 cells, all those cells are the middle cell's living neighbors
                            neighbours = vonNeumann->countAlive(middleCellPosition);
                            REQUIRE(neighbours == neighboursToCount);


                            //depending on this neighbour value, the correct action should be taken.
                            AND_THEN(
                                    "the correct action should be taken for the middle cell depending on number of living neighbours") {
                                if (neighbours < vonNeumann->getPopLimits().UNDERPOPULATION) {

                                    THEN("getAction should return KILL_CELL") {
                                        REQUIRE(vonNeumann->getAction(neighbours, true) == KILL_CELL);
                                        AND_WHEN("we set the action for the middle cell and update the state") {
                                            Cell cell = vonNeumann->getCellAtPosition(middleCellPosition);
                                            cell.setNextGenerationAction(KILL_CELL);
                                            cell.updateState();
                                            THEN("the cell should be dead") {
                                                REQUIRE_FALSE(cell.isAlive());
                                            }
                                        }

                                    }
                                } else if (neighbours > vonNeumann->getPopLimits().OVERPOPULATION) {
                                    THEN("getAction should return KILL_CELL") {
                                        REQUIRE(vonNeumann->getAction(neighbours, true) == KILL_CELL);
                                        AND_WHEN("we set the action for the middle cell and update the state") {
                                            Cell cell = vonNeumann->getCellAtPosition(middleCellPosition);
                                            cell.setNextGenerationAction(KILL_CELL);
                                            cell.updateState();
                                            THEN("the cell should be dead") {
                                                REQUIRE_FALSE(cell.isAlive());
                                            }
                                        }

                                    }

                                } else if (neighbours == vonNeumann->getPopLimits().RESURRECTION) {

                                    THEN("getAction should return GIVE_CELL_LIFE if our cell is dead, otherweise it should return GIVE CELL LIFE") {
                                        Cell cell = vonNeumann->getCellAtPosition(middleCellPosition);
                                        if (cell.isAlive()) {
                                            REQUIRE(vonNeumann->getAction(neighbours, true) == IGNORE_CELL);

                                        } else {
                                            REQUIRE(vonNeumann->getAction(neighbours, false) == GIVE_CELL_LIFE);
                                            AND_WHEN("we set the action for the middle cell and update the state") {
                                                cell.setNextGenerationAction(GIVE_CELL_LIFE);
                                                cell.updateState();
                                                THEN("the cell should be alive") {
                                                    REQUIRE(cell.isAlive());
                                                }
                                            }
                                        }


                                    }

                                }
                            }


                        }

                    }
                }
            }
        }

    }
}

SCENARIO("testing rim cell detection in vonNeumann"){
    GIVEN("a small test population of 3x3") {

        for (int j = 0; j < 9; j++) {
            map<Point, Cell> cells;
            //int living = 0;

            //count how many living cells we produce since we want to test 1-8 living cells in our matrix
            int counter = 0;
            //we generate a small 3x3 cell population
            for (int row = 0; row <= 2; row++) {
                for (int column = 0; column <= 2; column++) {


                    if (column == 0 || row == 0 || column == 2 ||
                        row == 2) {  // if cell should be a rim cell, create a rim cell
                        cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                    } else if (counter <= j) { // If cell is an ordinary cell
                        cells[Point{column, row}] = Cell(false,
                                                         GIVE_CELL_LIFE); // create a ordinary living cell

                        //increment the counter for number of living cells we have in this run (we want to stop at j living cells).
                        counter++;

                    } else {
                        //if we already have our j living neighbours in this iteration, create a dead neighbour instead.
                        cells[Point{column, row}] = Cell(false, KILL_CELL);
                    }
                }


            }

            DYNAMIC_SECTION("Looped section " << j) {
                WHEN("we initiate a new vonNeumann object with this population") {
                    auto vonNeumann = new RuleOfExistence_VonNeumann(cells);
                    //store the middle cell position
                    Point middleCellPosition = {1, 1};

                    AND_WHEN("we loop through the different neighbour scenarios (1-8 neighbours") {
                        THEN("the middle cell should always have 0 living neighbours, since all are rim cells") {
                            REQUIRE(vonNeumann->countAlive(middleCellPosition) == 0);

                        }
                    }
                }

            }
        }

    }
}









