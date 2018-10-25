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

        Cell aliveCell1;
        Cell aliveCell2;
        Cell aliveCell3;
        Cell rimCell;
        map<Point, Cell> cells;



        //we generate a small 4x4 cell population to test executeRule()
        for (int row = 0; row <= 3; row++) {

            for (int column = 0; column <= 3; column++) {
                // if cell is a rim cell
                if (column == 0 || row == 0 || column == 3 || row == 3) {

                    cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                }
                else { // If cell is an ordinary cell
                    //all cells except rim cells are alive.
                    cells[Point{column, row}] = Cell(false, GIVE_CELL_LIFE); // create a ordinary living cell

                }
            }
        }

        auto *conway = new RuleOfExistence_Conway(cells);
        conway->executeRule();

        //each cell should have 3 alive neighbors:

    }

}
