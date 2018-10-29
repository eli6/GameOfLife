/**
* @file Cell.h
 * @author
 * @author Elin Fritiofsson
 * @date 23 october 2018
 * @version 0.1
 * @brief Contains all the tests for the Cell class constructor
*/

#include <catch.hpp>
#include <iostream>
#include "../include/GoL_Rules/RuleOfExistence_Conway.h"


/***********************************
* TESTING CONSTRUCTOR WITH DIFFERENT PARAMETERS
***********************************/
SCENARIO("Testing constructor"){

}

/***********************************
* TESTING EXECUTE RULE AND DEPENDENT FUNCTIONS
***********************************/
SCENARIO("Testing executeRule()"){
    GIVEN("a Conway Rule of Existence") {

        //We declare the objects needed for testing
        // we need 8 points to create the 8 neighbors

        //TODO reformulate using catch.

        WHEN("we create a test cell population of 5x5 cells and create 1-8 neighbours for the middle cell in a for loop") {

            map<Point, Cell> cells;
            int living = 0;

            //we create 8 scenarios with j+1 number of living cells.
            for (int j = 0; j < 9; j++) {
                //count how many living cells we produce since we want to test 1-8 living cells in our matrix
                int counter = 0;
                //we generate a small 5x5 cell population
                for (int row = 0; row <= 4; row++) {
                    for (int column = 0; column <= 4; column++) {


                        if (column == 0 || row == 0 || column == 4 || row == 4) {  // if cell should be a rim cell, create a rim cell
                            cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                        } else if (counter <= j) { // If cell is an ordinary cell
                            cells[Point{column, row}] = Cell(false, GIVE_CELL_LIFE); // create a ordinary living cell

                            //increment the counter for number of living cells we have in this run (we want to stop at j living cells).
                            counter++;

                        } else {
                            //if we already have our j living neighbours in this iteration, create a dead neighbour instead.
                            cells[Point{column, row}] = Cell(false, KILL_CELL);
                        }
                    }


                }

                AND_WHEN("we initiate a new RuleOfExistence_Conway instance with the above cells and get the position of the cell int he middle") {

                    auto *conway = new RuleOfExistence_Conway(cells);

                    //TODO test that rimCells aren't counted, using a different cell.
                    //TESTING counting of neighbors using cell in the middle of matrix.
                    Point middleCellPosition = {2, 2};

                    THEN("the middle cell should have j or j-1 neighbours") {
                        //if we have produced less than 5 cells, all those cells are the middle cell's living neighbors
                        if (counter < 5) {
                            REQUIRE(conway->countAlive(middleCellPosition) == counter);

                        } else {
                            //if we have produced 5 living cells, the middle cell is one of them, so we subtract it from the neighbor count.
                            REQUIRE(conway->countAlive(middleCellPosition) == counter - 1);
                        }
                    }




                    for (auto it = cells.begin(); it != cells.end(); ++it) {

                        int aliveNeighbors = conway->countAlive(it->first);
                        Cell cell;

                        //TODO test this?.
                        //using test function to get a cell again (this also isn't tested)
                        cell = conway->getCellAtPosition(it->first);

                        //now we dont want any rim cells to be alive
                        if (cell.isRimCell()) {
                            REQUIRE_FALSE(cell.isAlive());
                        }

                        //testing if populationLimits work as expected.
                        //TODO consider if this indirectly just tests getAction.
                        if (!cell.isRimCell()) {
                            if (aliveNeighbors < 2) {
                                cell.setNextGenerationAction(KILL_CELL);
                                cell.updateState();
                                REQUIRE_FALSE(cell.isAlive());
                            }

                            if (aliveNeighbors > 3) {
                                cell.setNextGenerationAction(KILL_CELL);
                                cell.updateState();
                                REQUIRE_FALSE(cell.isAlive());
                            }

                            if (aliveNeighbors == 3) {
                                cell.setNextGenerationAction(GIVE_CELL_LIFE);
                                cell.updateState();
                                REQUIRE(cell.isAlive());
                            }
                        }

                    }
                }

            }

        }
    }

    }


