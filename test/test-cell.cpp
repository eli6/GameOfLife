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


SCENARIO("We create a Cell object using different constructor parameters") {

    /***********************************
    * TESTING CONSTRUCTOR WITH DIFFERENT PARAMETERS
    ***********************************/

    //TESTING DEFAULT CONSTRUCTOR
    GIVEN("A default Cell object") {
        Cell cell;
        THEN("it should be a non-rim cell") {
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
        THEN("The screen character should be #") {
            REQUIRE(cell.getCellValue() == '#');
        }
        THEN("It should have next action set to DO_NOTHING") {
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }
    } //END OF CONSTRUCTOR TEST

    //TESTING CONSTRUCTOR WITH ACTION=GIVE_CELL_LIFE
    GIVEN("A cell object with action = GIVE_CELL_LIFE") {
        Cell cell(false, GIVE_CELL_LIFE);
        THEN("it should be a non-rim cell") {
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("It should be alive") {
            REQUIRE(cell.isAlive());
        }
        THEN("The member color should be STATE_COLORS.LIVING") {
            REQUIRE(cell.getColor() == STATE_COLORS.LIVING);
        }

        THEN("The age should be 1") {
            REQUIRE(cell.getAge() == 1);
        }
    }

    //TESTING CONSTRUCTOR WITH ACTION=IGNORE_CELL
    GIVEN("A Cell object with action = IGNORE_CELL") {
        Cell cell(false, IGNORE_CELL);
        THEN("it should be a non-rim cell") {
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("The member color should be STATE_COLORS.DEAD") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }
        THEN("The age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
    }

    //TESTING CONSTRUCTOR WITH ACTION=KILL_CELL
    GIVEN("A Cell object with action = KILL_CELL") {
        Cell cell(false, KILL_CELL);

        THEN("It should be dead") {
            REQUIRE_FALSE(cell.isAlive());
        }
        THEN("The member color should be STATE_COLORS.DEAD") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }
        THEN("The age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
    }
    //TESTING CONSTRUCTOR WITH isRimCell SET TO TRUE.
    GIVEN("A rim cell") {
        Cell cell(true);
        THEN("it should be a rim cell") {
            REQUIRE(cell.isRimCell());
        }
        THEN("It should not yet be alive") {
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

    /***********************************
     * TESTING OF OTHER PUBLIC MEMBER FUNCTIONS
     ***********************************/

    //to be tested
   // THEN("It should not yet be alive") {
     //   REQUIRE_FALSE(cell.isAlive());
    //}
SCENARIO("We test that correct values are set for the next generation") {
    //TESTING "NEXT GENERATION" VALUES
    GIVEN("a default cell") {
        Cell cell;

        //TESTING setIsAliveNext() and isAliveNext()
        WHEN("it is set to be dead next generation") {
            cell.setIsAliveNext(false);
            THEN("it should be dead next") {
                REQUIRE_FALSE(cell.isAliveNext());
            }
            WHEN("it is reset to be alive next generation") {
                cell.setIsAliveNext(true);
                THEN("it should again be alive next") {
                    REQUIRE(cell.isAliveNext());
                }
            }
        }

        //TESTING setNextColor() AND setNextCellValue()
        WHEN("its next update character is set to 'M'") {
            cell.setNextCellValue('M');
            AND_WHEN("its next color is set to cyan") {
                cell.setNextColor(COLOR::CYAN);
                AND_WHEN(
                        "the cells next action is set to GIVE_CELL_LIFE instead of DO_NOTHING so that the updateState() switch is activated") {
                    cell.setNextGenerationAction(GIVE_CELL_LIFE);
                    AND_THEN("the cells state is updated so the color and value are set")cell.updateState();
                    AND_THEN("the cell is updated again to its 'next' state") {
                        cell.updateState();
                        THEN("its next cell value should be M") {
                            REQUIRE(cell.getCellValue() == 'M');
                        }
                        THEN("its color should be cyan") {
                            REQUIRE(cell.getColor() == COLOR::CYAN);
                        }
                    }

                }


            }

        }
    }
}

/***********************************
 * TESTING OF updateState()
 ***********************************/


SCENARIO("We test that updateState() change the cell as expected") {

    GIVEN("a default cell") {
        Cell cell;

        //save cells current color, value and age before we run the tests, for comparison after updateState().
        COLOR oldColor = cell.getColor();
        char oldValue = cell.getCellValue();
        int formerAge = cell.getAge();


        //TESTING updateState() based on different "nextGenerationAction" values.
        WHEN("the nextGenerationAction is set to DO_NOTHING") { //testing action DO_NOTHING
            cell.setNextGenerationAction(DO_NOTHING);


            THEN("update cell should not change the color") {
                //update the cells state.
                cell.updateState();
            }
            //action was set to do nothing, so color, value and age should be the same as before.
            THEN("cells color should be the same") {
                REQUIRE(oldColor == cell.getColor());
            }

            THEN("the cells value should be the same as well") {
                REQUIRE(oldValue == cell.getCellValue());
            }

            THEN("the age should also be the same") {
                REQUIRE(formerAge == cell.getAge());
            }

        }

        AND_WHEN("the nextGenerationAction is set to IGNORE_CELL") {  //testing action IGNORE_CELL
            cell.setNextGenerationAction(IGNORE_CELL);
            AND_WHEN("updateState() is run") {
                cell.updateState();
                THEN("age should have incremented by 1 if the cell is alive") {
                    if (cell.isAlive()) {
                        REQUIRE(formerAge + 1 == cell.getAge());
                    }
                }
                THEN("value should be the same as before") {
                    REQUIRE(oldValue == cell.getCellValue());

                }

                THEN("color should also be the same") {
                    REQUIRE(oldColor == cell.getColor());
                }
            }

            AND_WHEN("we change the update color and set the next value") {
                cell.setNextColor(COLOR::BLACK);
                cell.setNextCellValue('X');
                AND_WHEN("updateState() is run") {
                    cell.updateState();
                    THEN("after the next update. nextGenerationAction should firsthave been reset to DO_NOTHING"){
                        REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
                    }
                    THEN("the color should have changed to black") {
                        REQUIRE(cell.getColor() == COLOR::BLACK);
                    }
                    THEN("the value should have changed") {
                        REQUIRE(cell.getCellValue() == 'X');
                    }

                }

            }
        }


        AND_WHEN("nextGenerationAction is set to KILL_CELL") { //TESTING ACTION KILL_CELL
            cell.setNextGenerationAction(KILL_CELL);
            AND_WHEN("updateState() is run") {
                cell.updateState();
                THEN("the cell should not be alive") {
                    REQUIRE_FALSE(cell.isAlive());

                }
                THEN("the cells age should be 0") {
                    REQUIRE(cell.getAge() == 0);
                }
                THEN("value should be the same as before") {
                    REQUIRE(oldValue == cell.getCellValue());

                }
                THEN("color should also be the same") {
                    REQUIRE(oldColor == cell.getColor());
                }
            }
        }

        AND_WHEN("nextGenerationAction is set to GIVE_CELL_LIFE") { //testing action GIVE_CELL_LIFE
            cell.setNextGenerationAction(GIVE_CELL_LIFE);
            AND_WHEN("updateState() is run") {
                cell.updateState();
                THEN("the cell should be alive") {
                    REQUIRE(cell.isAlive());

                }
                THEN("the cells age should be 1") {
                    REQUIRE(cell.getAge() == 1);
                }
                THEN("value should be the same as before") {
                    REQUIRE(oldValue == cell.getCellValue());

                }
                THEN("color should also be the same") {
                    REQUIRE(oldColor == cell.getColor());
                }
            }

        }
        AND_WHEN("a rim cell is configured with next generation action GIVE_CELL_LIFE") { //testing rim cell with action GIVE_CELL_LIFE
            Cell cell2(true, GIVE_CELL_LIFE);
            AND_WHEN("updateState() is run") {
                cell2.updateState();
                THEN("the cell should not be alive because it is a rim cell") {
                    REQUIRE_FALSE(cell.isAlive());
                }
                THEN("the cells age should not have been incremented be 0") {
                    REQUIRE(cell.getAge() == 0);
                }
            }
        }
    }
}

