/**
* @file
 * @author
 * @author Elin Fritiofsson
 * @date 23 october 2018
 * @version 0.1
 * @brief Contains all the tests for the Cell class constructor
*/

#include "catch2.hpp"
#include <iostream>
#include "../include/GoL_Rules/RuleOfExistence_Erik.h"


/***********************************
* TESTING CONSTRUCTOR WITH DIFFERENT PARAMETERS
***********************************/

SCENARIO("Testing constructor for Erik"){
    GIVEN("a small cell population"){
        Point point1 = {1,1};
        Point point2 = {0,0};
        Cell cell1(false);
        Cell cell2(true);
        map<Point,Cell> cells;

        cells[point1] = cell1;
        cells[point2] = cell2;

        WHEN("we initialize our rule with these cells"){
            auto erik = new RuleOfExistence_Erik(cells);
            THEN("we should be able to retrive the first, non-rim cell"){
                REQUIRE_FALSE(erik->getCellAtPosition(point1).isRimCell());
            }
            THEN("we should also be able to retrieve the second, which is a rim cell"){
                REQUIRE(erik->getCellAtPosition(point2).isRimCell());

            }
            THEN("it should have the right population limits set"){
                REQUIRE(erik->getPopLimits().UNDERPOPULATION == 2);
                REQUIRE(erik->getPopLimits().OVERPOPULATION == 3);
                REQUIRE(erik->getPopLimits().RESURRECTION == 3);

            }

            THEN("it should have directions set to all directions"){

                REQUIRE(erik->getDirections().size() == 8);


            }

            THEN("its rule name should be 'erik'"){
                REQUIRE (erik->getRuleName() == "erik");
            }
        }
    }
}




/***********************************
* TESTING EXECUTE RULE AND DEPENDENT FUNCTIONS
***********************************/

SCENARIO("Testing executeRule() for Erik") {
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
                            "we initiate a new RuleOfExistence_Erik instance with the above cells and get the position of the cell int he middle") {
                        auto *erik = new RuleOfExistence_Erik(cells);

                        //TESTING counting of neighbors using cell in the middle of matrix.
                        Point middleCellPosition = {2, 2};
                        int neighbours = 0;

                        //only this is specifc to erik-directions, other rules may only detect 4 out of 8 neighbors.
                        THEN("the middle cell should have j or j-1 neighbours") {
                            //if we have produced less than 5 cells, all those cells are the middle cell's living neighbors
                            if (counter < 5) {
                                neighbours = erik->countAlive(middleCellPosition);
                                REQUIRE(neighbours == counter);

                            } else {
                                neighbours = erik->countAlive(middleCellPosition);
                                //if we have produced 5 living cells, the middle cell is one of them and won't be counted by "countAlive", so we subtract it from the counter.
                                REQUIRE(neighbours == counter - 1);
                            }


                            //depending on this neighbour value, the correct action should be taken.
                            AND_THEN(
                                    "the correct action should be taken for the middle cell depending on number of living neighbours") {
                                if (neighbours < erik->getPopLimits().UNDERPOPULATION) {

                                    THEN("getAction should return KILL_CELL") {
                                        REQUIRE(erik->getAction(neighbours, true) == KILL_CELL);
                                        AND_WHEN("we set the action for the middle cell and update the state") {
                                            Cell cell = erik->getCellAtPosition(middleCellPosition);
                                            cell.setNextGenerationAction(KILL_CELL);
                                            cell.updateState();
                                            THEN("the cell should be dead") {
                                                REQUIRE_FALSE(cell.isAlive());
                                            }
                                        }

                                    }
                                } else if (neighbours > erik->getPopLimits().OVERPOPULATION) {
                                    THEN("getAction should return KILL_CELL") {
                                        REQUIRE(erik->getAction(neighbours, true) == KILL_CELL);
                                        AND_WHEN("we set the action for the middle cell and update the state") {
                                            Cell cell = erik->getCellAtPosition(middleCellPosition);
                                            cell.setNextGenerationAction(KILL_CELL);
                                            cell.updateState();
                                            THEN("the cell should be dead") {
                                                REQUIRE_FALSE(cell.isAlive());
                                            }
                                        }

                                    }

                                } else if (neighbours == erik->getPopLimits().RESURRECTION) {

                                    THEN("getAction should return GIVE_CELL_LIFE if our cell is dead, otherweise it should return GIVE CELL LIFE") {
                                        Cell cell = erik->getCellAtPosition(middleCellPosition);
                                        if (cell.isAlive()) {
                                            REQUIRE(erik->getAction(neighbours, true) == IGNORE_CELL);

                                        } else {
                                            REQUIRE(erik->getAction(neighbours, false) == GIVE_CELL_LIFE);
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

SCENARIO("testing rim cell detection for Erik"){
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
                WHEN("we initiate a new erik object with this population") {
                    auto erik = new RuleOfExistence_Erik(cells);
                    //store the middle cell position
                    Point middleCellPosition = {1, 1};

                    AND_WHEN("we loop through the different neighbour scenarios (1-8 neighbours") {
                        THEN("the middle cell should always have 0 living neighbours, since all are rim cells") {
                            REQUIRE(erik->countAlive(middleCellPosition) == 0);

                        }
                    }
                }

            }
        }

    }
}



SCENARIO("TESTING for prime elders and different age colors depending on cell age") {
    GIVEN("a cell in a map") {

        map<Point, Cell> cells;

        //we generate a small 5x5 cell population where everyone is alive exept rim cells
        for (int row = 0; row <= 4; row++) {
            for (int column = 0; column <= 4; column++) {


                if (column == 0 || row == 0 || column == 4 ||
                    row == 4) {  // if cell should be a rim cell, create a rim cell
                    cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                } else { // If cell is an ordinary cell
                    cells[Point{column, row}] = Cell(false,
                                                     GIVE_CELL_LIFE); // create a ordinary living cell

                }
            }
        }

        WHEN("we initiate an erik rule object with this map") {
            auto erik = new RuleOfExistence_Erik(cells);

            AND_WHEN("we make all cells age 5 generationS") {
                for (int i = 0; i < 4; i++) {
                    for (auto it = cells.begin(); it != cells.end(); it++) {
                        if (!it->second.isRimCell()) {
                            it->second.setNextGenerationAction(IGNORE_CELL);
                            it->second.updateState();

                        }

                    }


                }

                AND_WHEN("we get the middle cell and erikfy it") {

                    Cell cell = erik->getCellAtPosition({2, 2});

                    //erikfyCell will set nextColor to cyan now that the cell is 5 gen old
                    erik->erikfyCell(cell, IGNORE_CELL);

                    //we update state to reach the next state. cell is now 6 gen old
                    cell.updateState();

                    //now the current color should be cyan
                    THEN("it should have a cyan color") {
                        REQUIRE(cell.getColor() == COLOR::CYAN);
                    }
                }

            }

            AND_WHEN("we make the cells age 11 generations") {
                for (int i = 0; i < 9; i++) {
                    for (auto it = cells.begin(); it != cells.end(); it++) {
                        if (!it->second.isRimCell()) {
                            it->second.setNextGenerationAction(IGNORE_CELL);
                            it->second.updateState();

                        }

                    }


                }
                AND_WHEN("we get the middle cell and erikfy it") {

                    Cell cell = erik->getCellAtPosition({2, 2});

                    //erikfyCell will set nextColor to cyan now that the cell is 5 gen old
                    erik->erikfyCell(cell, IGNORE_CELL);

                    //we update state to reach the next state. cell is now 6 gen old
                    cell.updateState();

                    THEN("It should have the value E") {
                        REQUIRE(cell.getCellValue() == 'E');
                    }

                    THEN("it should still have a cyan color") {
                        REQUIRE(cell.getColor() == COLOR::CYAN);
                    }

                    THEN("it will be a prime elder since that position is vacant") {
                        REQUIRE(cell.getColor() == STATE_COLORS.ELDER);
                    }

                    AND_WHEN("we make another cell age even more, then erikfy it and update both cells") {

                        //let cell at 2,3 age one more year
                        Cell cell2 = erik->getCellAtPosition({2, 3});
                        cell2.setNextGenerationAction(IGNORE_CELL);
                        cell2.updateState();

                        erik->erikfyCell(cell2, IGNORE_CELL);

                        //update new prime elder-to-be
                        cell2.updateState();

                        //update old prime elder
                        cell.updateState();

                        THEN("it will be a prime elder since it is older than the former prime elder") {
                            REQUIRE(cell2.getColor() == STATE_COLORS.ELDER);
                        }

                        THEN("our old prime elder will be old again") {
                            REQUIRE(cell.getColor() == STATE_COLORS.OLD);
                        }

                        AND_WHEN("we kill our first cell") {
                            erik->erikfyCell(cell, KILL_CELL);
                            cell.updateState();

                            THEN("it should have the value '#' again") {
                                REQUIRE(cell.getCellValue() == '#');
                            }
                        }

                        AND_WHEN("we kill our prime elder") {
                            erik->erikfyCell(cell2, KILL_CELL);
                            cell2.updateState();
                            THEN("prime elder should be a nullptr again") {
                                REQUIRE(erik->getPrimeElder() == nullptr);
                            }
                        }


                    }
                }

            }
        }
    }
}










