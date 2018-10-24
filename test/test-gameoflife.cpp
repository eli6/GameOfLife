/**
* @file
 * @author Elin Fritiofsson
 * @date 23 october 2018
 * @version 0.1
 * @brief Contains all the tests for the Cell class constructor
*/

#include <catch.hpp>
#include <iostream>
#include "../include/Cell_Culture/Cell.h"

SCENARIO("We create a Cell object"){
    GIVEN("A default Cell object"){
        Cell cell;
        THEN("it should be a non-rim cell"){
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("The member color should be STATE_COLORS.DEAD") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }
        THEN("The age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
        // The following two only need testing once since they are initially the same
        // for all Cell objects, and can only change after initialization
        THEN("The screen character should be #"){
            REQUIRE(cell.getCellValue() == '#');
        }
        THEN("It should have next action set to DO_NOTHING") {
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }
    }

    GIVEN("A cell object with action = GIVE_CELL_LIFE"){
        Cell cell(false, GIVE_CELL_LIFE);
        THEN("it should be a non-rim cell"){
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("The member color should be STATE_COLORS.LIVING") {
            REQUIRE(cell.getColor() == STATE_COLORS.LIVING);
        }
        THEN("The age should be 1") {
            REQUIRE(cell.getAge() == 1);
        }
    }

    GIVEN("A Cell object with action = IGNORE_CELL") {
        Cell cell(false, IGNORE_CELL);
        THEN("it should be a non-rim cell"){
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("The member color should be STATE_COLORS.DEAD") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }
        THEN("The age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
    }

    GIVEN("A rim cell") {
        Cell cell(true);
        THEN("it should be a rim cell"){
            REQUIRE(cell.isRimCell());
        }
        THEN("The member color should be STATE_COLORS.DEAD") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }
        THEN("The age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
    }
}
