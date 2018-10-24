/**
* @file
 * @author
 * @author Elin Fritiofsson
 * @author Fredrik Arhusiander
 * @date 23 october 2018
 * @version 0.1
 * @brief Contains all the tests for the Cell class constructor
*/

#include <catch.hpp>
#include <iostream>
#include "../include/Cell_Culture/Cell.h"

SCENARIO("We create a Cell object"){

    //TESTING CONSTRUCTOR
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
        THEN("It should not yet be alive"){
            REQUIRE_FALSE(cell.isAlive());
        }
        // The following two only need testing once since they are initially the same
        // for all Cell objects, and can only change after initialization
        THEN("The screen character should be #"){
            REQUIRE(cell.getCellValue() == '#');
        }
        THEN("It should have next action set to DO_NOTHING") {
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }

        WHEN("it is set to be dead next generation"){
            cell.setIsAliveNext(false);
            THEN("it should be dead next"){
                REQUIRE_FALSE(cell.isAliveNext());
            }
            WHEN("it is reset to be alive next generation"){
                cell.setIsAliveNext(true);
                THEN("it should again be alive next"){
                    REQUIRE(cell.isAliveNext());
                }
            }
        }

        //TESTING setNextColor() AND setNextCellValue()
        WHEN("its next update character is set to 'M'"){
            cell.setNextCellValue('M');
            AND_WHEN("its next color is set to cyan"){
                cell.setNextColor(COLOR::CYAN);
                AND_THEN("the cells next action is set to GIVE_CELL_LIFE instead of DO_NOTHING so that the updateState() switch is activated"){
                    cell.setNextGenerationAction(GIVE_CELL_LIFE);
                    AND_THEN("the cells state is updated so the color and value are set")
                        cell.updateState();
                        AND_THEN("the cell is updated again to its 'next' state"){
                            cell.updateState();
                            THEN("its next cell value should be M"){
                                REQUIRE(cell.getCellValue() == 'M');
                            }
                            AND_THEN("its color should be cyan"){
                                REQUIRE(cell.getColor() == COLOR::CYAN);
                            }
                        }

                }



            }

        }

        //TESTING updateState()
        WHEN("the nextGenerationAction is set to DO_NOTHING"){
            cell.setNextGenerationAction(DO_NOTHING);
            THEN("update cell should not change the color"){
                COLOR oldColor = cell.getColor();
                char oldValue = cell.getCellValue();
                int formerAge = cell.getAge();
                cell.updateState();
                REQUIRE(oldColor == cell.getColor());
                AND_THEN("update cell should not have changed the value either"){
                    REQUIRE(oldValue == cell.getCellValue());
                }
                AND_THEN("the age should also be the same"){
                    REQUIRE(formerAge == cell.getAge());
                }
                AND_WHEN("the nextGenerationAction is set to IGNORE_CELL") {
                    cell.setNextGenerationAction(IGNORE_CELL);
                    AND_WHEN("updateState() is run"){
                        cell.updateState();
                        THEN("age should have incremented by 1 if the cell is alive"){
                            if(cell.isAlive()){
                                REQUIRE(formerAge+1 == cell.getAge());
                            }
                        }
                        AND_THEN("value should be the same as before"){
                            REQUIRE(oldValue == cell.getCellValue());

                        }

                        AND_THEN("color should also be the same"){
                            REQUIRE(oldColor == cell.getColor());
                        }
                    }
                    AND_WHEN("we change the update color"){
                        cell.setNextColor(COLOR::BLACK);
                        AND_WHEN("we also set the next update value"){
                            cell.setNextCellValue('X');
                            THEN("after the next update. nextGenerationAction should firsthave been reset to DO_NOTHING"){
                                cell.updateState();
                                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
                                AND_THEN("the color should have changed"){
                                    REQUIRE(cell.getColor() == COLOR::BLACK);
                                }
                                AND_THEN("the value should have changed"){
                                    REQUIRE(cell.getCellValue() == 'X');
                                }
                            }

                        }
                    }


                }
                AND_WHEN("nextGenerationAction is set to KILL_CELL"){
                    cell.setNextGenerationAction(KILL_CELL);
                    AND_WHEN("updateState() is run"){
                        cell.updateState();
                        THEN("the cell should not be alive"){
                            REQUIRE_FALSE(cell.isAlive());

                        }
                        AND_THEN("the cells age should be 0"){
                            REQUIRE(cell.getAge() == 0);
                        }
                        AND_THEN("value should be the same as before"){
                            REQUIRE(oldValue == cell.getCellValue());

                        }
                        AND_THEN("color should also be the same"){
                            REQUIRE(oldColor == cell.getColor());
                        }
                    }
                }

                AND_WHEN("nextGenerationAction is set to GIVE_CELL_LIFE"){
                    cell.setNextGenerationAction(GIVE_CELL_LIFE);
                    AND_WHEN("updateState() is run"){
                        cell.updateState();
                        THEN("the cell should be alive"){
                            REQUIRE(cell.isAlive());

                        }
                        AND_THEN("the cells age should be 1"){
                            REQUIRE(cell.getAge() == 1);
                        }
                        AND_THEN("value should be the same as before"){
                            REQUIRE(oldValue == cell.getCellValue());

                        }
                        AND_THEN("color should also be the same"){
                            REQUIRE(oldColor == cell.getColor());
                        }
                    }
                    AND_WHEN("a rim cell is configured in the same way"){
                        Cell cell2(true, GIVE_CELL_LIFE);
                        AND_WHEN("updateState() is run"){
                            cell2.updateState();
                            THEN("the cell should not be alive"){
                                REQUIRE_FALSE(cell.isAlive());

                            }
                            AND_THEN("the cells age should not have been incremented be 0"){
                                REQUIRE(cell.getAge() == 0);
                            }
                        }
                    }
                }
            }
        }

    }


    GIVEN("A cell object with action = GIVE_CELL_LIFE"){
        Cell cell(false, GIVE_CELL_LIFE);
        THEN("it should be a non-rim cell"){
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("It should be alive"){
            REQUIRE(cell.isAlive());
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

    GIVEN("A Cell object with action = KILL_CELL") {
        Cell cell(false, KILL_CELL);
        THEN("it should be a non-rim cell"){
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("It should be dead"){
            REQUIRE_FALSE(cell.isAlive());
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
        THEN("It should not yet be alive"){
            REQUIRE_FALSE(cell.isAlive());
        }
        THEN("The member color should be STATE_COLORS.DEAD") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }
        THEN("The age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
    }
}
