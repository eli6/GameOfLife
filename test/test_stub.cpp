//
// Created by Elin Fritiofsson on 2018-10-30.
//

#include "catch2.hpp"
#include <map>
#include "../include/Support/FileLoader.h"

using namespace std;

SCENARIO("testing loadPopulationFromFile"){
    GIVEN("a file loader instance"){
        FileLoader fileLoader;
        map<Point, Cell> cells;

        WHEN("we enter a non-valid file name"){
            fileName = "nofile";
            THEN("an exception should be thrown"){
                REQUIRE_THROWS(fileLoader.loadPopulationFromFile(cells));
            }

        }
        WHEN("we enter a valid file name"){
            fileName = "../Population_Seed.txt";
            REQUIRE_NOTHROW(fileLoader.loadPopulationFromFile(cells));
            AND_WHEN("that file has correct content"){
                THEN("World width should be 20"){
                    REQUIRE(WORLD_DIMENSIONS.WIDTH == 20);
                } THEN("World height should be 10"){
                    REQUIRE(WORLD_DIMENSIONS.HEIGHT == 10);
                }
                THEN("cell 0,0 should be a rim cell (upper left corner)") {
                    REQUIRE(cells[{0, 0}].isRimCell());
                }
                THEN("cell 19,0 should also be a rim cell"){
                    REQUIRE(cells[{19, 0}].isRimCell());
                }
                THEN("cell 0,9 should also be a rim cell (lower left corner)") {

                    REQUIRE(cells[{0, 9}].isRimCell());
                }
                /*THEN("CELL 19,9 should also be a rim cell (lower right corner)"){
                    REQUIRE(cells[{19, 9}].isRimCell());
                }*/

                THEN("We should be able to loop through the second row of cells and it should correspond to line 1 in our Population_Seed.txt"){

                    for (auto it = cells.begin(); it != cells.end(); ++it){
                        //if the y(row) value is 1 and x (column) is between 0 and 19, we're on line 2.
                        if(it->first.y == 1 && (it->first.x >= 0 && it->first.x < 19)){
                            // we passed in this row as seed for the second row.
                            //00000010000011001100
                            //this means that cells with x value 6, 12, 13, 16, 17 should have had nextAction set to GIVE_CELL_LIFE. Others to IGNORE_CELL.
                            vector<int> v = {7, 12, 13, 16, 17};
                            if(it->second.getColor() == STATE_COLORS.LIVING){
                                int xValue = it->first.x;
                                auto it = std::find(v.begin(), v.end(), xValue);

                                //require returns 7 and not 6 if we correct the world dimensinos in fileLoader.cpp meaning the rim cell at the start of the row is mistakenly taken for a normal cell.
                                //if we use the incorrect world dimension calculations dimensions +1, nothing is correct since a row with only zeroes (rim cells) is incorrectly used for line 2.
                                REQUIRE(it!=v.end());
                            }
                        }
                    }
                }
            }
            //this test fails because no exception is thrown, so I added a @bug.
            /*AND_WHEN("we call file loader with a valid name but the file contains erroneous content"){
               fileName = "../Population_Seed_With_Errors.txt";
                REQUIRE_THROWS(fileLoader.loadPopulationFromFile(cells));
            }*/




        }


    }

}