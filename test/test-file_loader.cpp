


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
                    //This fails
                THEN("CELL 19,9 should also be a rim cell (lower right corner)"){
                    REQUIRE(cells[{19, 9}].isRimCell());
                }

                THEN("We should be able to loop through the second row of cells and it should correspond to line 1 in our Population_Seed.txt"){

                    // we passed in this row as seed for the second row.
                    //00000010000011001100
                    //this means that cells with x value 6, 12, 13, 16, 17 should have had nextAction set to GIVE_CELL_LIFE. Others to IGNORE_CELL.
                    vector<int> v = {6, 12, 13, 16, 17};

                    for (auto it = cells.begin(); it != cells.end(); ++it){
                        //if the y(row) value is 1 and x (column) is between 0 and 19, we're on line 2.
                        if(it->first.y == 1 && (it->first.x >= 0 && it->first.x <= 19)){

                            //we store the x value for simplicity
                            int xValue = it->first.x;
                            vector<int>::iterator p;

                            //we see if we can find that x value in our vector above.
                            p = std::find(v.begin(), v.end(), xValue);

                            //if we are on one of the cells in the vector v (that should be living)
                            if(p != v.end()){
                                //test below fails
                                //if we put first.y == 2 in the if clause above, we get living cells on position 7, 13, 14, etc.. theyr shifted one to the right meaning the rim cell at the left is counted as a normal cell.
                                //in this test: a row with only zeroes (rim cells) is incorrectly used for line 2.

                                //it should have color living.
                                REQUIRE(it->second.getColor() == STATE_COLORS.LIVING);
                            }


                        }
                    }
                }
            }
        }
        AND_WHEN("we call file loader with a valid name but the file contains erroneous content"){
            fileName = "../Population_Seed_With_Errors.txt";
            REQUIRE_THROWS(fileLoader.loadPopulationFromFile(cells));
        }




    }


}


