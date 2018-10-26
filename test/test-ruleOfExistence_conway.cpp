/**
* @file Cell.h
 * @author
 * @author Elin Fritiofsson
 * @author Fredrik Arhusiander
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


SCENARIO("Testing executeRule()"){
    GIVEN("a Conway Rule of Existence"){

        //We declare the objects needed for testing
        // we need 8 points to create the 8 neighbors

        //TODO reformulate using catch.

        map<Point, Cell> cells;

        int living = 0;

        //we create 8 scenarios with j+1 number of living cells.
        for(int j=0; j < 8; j++) {
            //count how many living cells we produce since we want to test 1-8 living cells in our matrix
            int counter = 0;
            //we generate a small 5x5 cell population to test executeRule()
            for (int row = 0; row <= 4; row++) {
                for (int column = 0; column <= 4; column++) {

                    // if cell is a rim cell
                    if (column == 0 || row == 0 || column == 4 || row == 4) {
                        cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                    } else if(counter <= j){ // If cell is an ordinary cell
                        cells[Point{column, row}] = Cell(false, GIVE_CELL_LIFE); // create a ordinary living cell

                        //increment the counter for number of living cells we have in this run (we want to stop at j living cells).
                        counter++;

                    } else {
                        cells[Point{column, row}] = Cell(false, KILL_CELL);
                    }
                }



            }

            auto *conway = new RuleOfExistence_Conway(cells);


            for (auto it=cells.begin(); it!=cells.end(); ++it) {

                //TODO test this using cell in the middle and generate 1-8 neighbors.
                //using my test function to count neighbors (but we havent tested the function!!)
                int aliveNeighbors = conway->countAlive(it->first);
                Cell cell;

                //TODO test this somehow.
                //using test function to get a cell again (this also isn't tested)
                cell = conway->getCellAtPosition(it->first);

                //now we dont want any rim cells to be alive
                if(cell.isRimCell()){
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


