/**
* @file
 * @author Elin Fritiofsson
 * @date 23 october 2018
 * @version 0.1
 * @brief Contains all our tests.
*/

#include <catch.hpp>
#include <iostream>
#include "../include/Cell_Culture/Cell.h"

SCENARIO("We create a Cell object"){
    GIVEN("a default Cell object"){
        Cell cell;
        THEN("it should be a non-rim cell and have action set to nothing"){
            REQUIRE_FALSE(cell.isRimCell());
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }
        THEN("As default CellDetails are also set: It should have a dead color, age 0 and screen character #"){
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            REQUIRE(cell.getAge() == 0);
            REQUIRE(cell.getCellValue() == '#');
        }

    }

    GIVEN("a cell object with action = GIVE_CELL_LIFE"){
        Cell cell(false, GIVE_CELL_LIFE);
        THEN("it should be a non-rim cell and have action reset to DO_NOTHING after object creation"){
            REQUIRE_FALSE(cell.isRimCell());
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }
        THEN("As default CellDetails are also set: It should have a living color, age 1 and screen character #"){
            REQUIRE(cell.getColor() == STATE_COLORS.LIVING);
            REQUIRE(cell.getAge() == 1);
            REQUIRE(cell.getCellValue() == '#');
        }
    }


}