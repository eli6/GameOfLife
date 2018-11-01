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
#include "../include/GoL_Rules/RuleOfExistence_Conway.h"


/***********************************
* TESTING CONSTRUCTOR WITH DIFFERENT PARAMETERS
***********************************/
SCENARIO("Testing constructor"){
    GIVEN("a small cell population"){
        Point point1 = {1,1};
        Point point2 = {0,0};
        Cell cell1(false);
        Cell cell2(true);
        map<Point,Cell> cells;

        cells[point1] = cell1;
        cells[point2] = cell2;

        WHEN("we initialize our rule with these cells"){
            auto conway = new RuleOfExistence_Conway(cells);
            THEN("we should be able to retrive the first, non-rim cell"){
                REQUIRE_FALSE(conway->getCellAtPosition(point1).isRimCell());
            }
            THEN("we should also be able to retrieve the second, which is a rim cell"){
                REQUIRE(conway->getCellAtPosition(point2).isRimCell());

            }
            THEN("it should have the right population limits set"){
                REQUIRE(conway->getPopLimits().UNDERPOPULATION == 2);
                REQUIRE(conway->getPopLimits().OVERPOPULATION == 3);
                REQUIRE(conway->getPopLimits().RESURRECTION == 3);

            }

            THEN("it should have directions set to all directions"){

                REQUIRE(conway->getDirections().size() == 8);


            }

            THEN("its rule name should be 'conway'"){
                REQUIRE (conway->getRuleName() == "conway");
            }
        }
    }
}




/***********************************
* TESTING EXECUTE RULE AND DEPENDENT FUNCTIONS
***********************************/
SCENARIO("Testing executeRule()") {
    GIVEN("a Conway Rule of Existence") {


        //We declare the objects needed for testing
        // we need 8 points to create the 8 neighbors

        //we create 8 scenarios with j+1 number of living cells.
        WHEN("we create a test cell population of 5x5 cells and create 1-8 neighbours for the middle cell in a for loop") {
            for (int j = 0; j < 9; j++) {
                map<Point, Cell> cells;
                //int living = 0;

                //count how many living cells we produce since we want to test 1-8 living cells in our matrix
                int counter = 0;
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

                        } else {
                            //if we already have our j living neighbours in this iteration, create a dead neighbour instead.
                            cells[Point{column, row}] = Cell(false, KILL_CELL);
                        }
                    }


                }




                //we wrap this in a DYNAMIC_SECTION so that it can be looped.
                DYNAMIC_SECTION("Looped section " << j) {
                    AND_WHEN(
                            "we initiate a new RuleOfExistence_Conway instance with the above cells and get the position of the cell int he middle") {
                        auto *conway = new RuleOfExistence_Conway(cells);

                        //TESTING counting of neighbors using cell in the middle of matrix.
                        Point middleCellPosition = {2, 2};
                        int neighbours = 0;

                        //only this is specifc to conway-directions, other rules may only detect 4 out of 8 neighbors.
                        THEN("the middle cell should have j or j-1 neighbours") {
                            //if we have produced less than 5 cells, all those cells are the middle cell's living neighbors
                            if (counter < 5) {
                                neighbours = conway->countAlive(middleCellPosition);
                                REQUIRE(neighbours == counter);

                            } else {
                                neighbours = conway->countAlive(middleCellPosition);
                                //if we have produced 5 living cells, the middle cell is one of them and won't be counted by "countAlive", so we subtract it from the counter.
                                REQUIRE(neighbours == counter - 1);
                            }


                            //depending on this neighbour value, the correct action should be taken.
                            AND_THEN(
                                    "the correct action should be taken for the middle cell depending on number of living neighbours") {
                                if (neighbours < conway->getPopLimits().UNDERPOPULATION) {

                                    THEN("getAction should return KILL_CELL") {
                                        REQUIRE(conway->getAction(neighbours, true) == KILL_CELL);
                                        AND_WHEN("we set the action for the middle cell and update the state") {
                                            Cell cell = conway->getCellAtPosition(middleCellPosition);
                                            cell.setNextGenerationAction(KILL_CELL);
                                            cell.updateState();
                                            THEN("the cell should be dead") {
                                                REQUIRE_FALSE(cell.isAlive());
                                            }
                                        }

                                    }
                                } else if (neighbours > conway->getPopLimits().OVERPOPULATION) {
                                    THEN("getAction should return KILL_CELL") {
                                        REQUIRE(conway->getAction(neighbours, true) == KILL_CELL);
                                        AND_WHEN("we set the action for the middle cell and update the state") {
                                            Cell cell = conway->getCellAtPosition(middleCellPosition);
                                            cell.setNextGenerationAction(KILL_CELL);
                                            cell.updateState();
                                            THEN("the cell should be dead") {
                                                REQUIRE_FALSE(cell.isAlive());
                                            }
                                        }

                                    }

                                } else if (neighbours == conway->getPopLimits().RESURRECTION) {

                                    THEN("getAction should return GIVE_CELL_LIFE if our cell is dead, otherweise it should return GIVE CELL LIFE") {
                                        Cell cell = conway->getCellAtPosition(middleCellPosition);
                                        if (cell.isAlive()) {
                                            REQUIRE(conway->getAction(neighbours, true) == IGNORE_CELL);

                                        } else {
                                            REQUIRE(conway->getAction(neighbours, false) == GIVE_CELL_LIFE);
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

SCENARIO("testing rim cell detection"){
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
                WHEN("we initiate a new conway object with this population") {
                    auto conway = new RuleOfExistence_Conway(cells);
                    //store the middle cell position
                    Point middleCellPosition = {1, 1};

                    AND_WHEN("we loop through the different neighbour scenarios (1-8 neighbours") {
                         THEN("the middle cell should always have 0 living neighbours, since all are rim cells") {
                                REQUIRE(conway->countAlive(middleCellPosition) == 0);

                            }
                        }
                    }

            }
        }

    }
}









