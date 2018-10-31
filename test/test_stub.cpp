/**
* @file
 * @author Elin Fritiofsson
 * @date 31 october 2018
 * @version 0.1
 * @brief Defines CATCH_CONFIG_MAIN separately to shorten compile time.
*/

#include "catch2.hpp"
#include "../include/Support/MainArgumentsParser.h"

SCENARIO("testing runParser"){
    GIVEN("a parser object"){
        MainArgumentsParser mParser;

        WHEN("we create our own argv array and pass it to runParser()"){
            char arg0[] = {"GameOfLife"};
            char arg1[] = {"-f"};
            char arg2[] = {"filename.txt"};
            char arg3[] = {"-g"};
            char arg4[] = {"3"};
            char arg5[] = {"-s"};
            char arg6[] = {"20x10"};
            char arg7[] = {"-er"};
            char arg8[] = {"vonNeumann"};
            char arg9[] = {"-or"};
            char arg10[] = {"erik"};

            char *argv[] = {&arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], &arg5[0], &arg6[0], &arg7[0], &arg8[0], &arg9[0], &arg10[0], NULL};

            std::cout << *arg6 << std::endl;

            mParser.runParser(argv, 11);

            THEN("filename should be set to filename.txt"){
                REQUIRE(fileName == "filename.txt");
            }

            //works but program crashes if the value can't be converted to string. should be a bug in GenerationsArgument
            THEN("generations should be 3"){
                REQUIRE(mParser.getAppValues().maxGenerations == 3);
            }

            THEN("world dimensions should be 20x10"){
                REQUIRE(WORLD_DIMENSIONS.WIDTH == 20);
                REQUIRE(WORLD_DIMENSIONS.HEIGHT == 10);
            }

            THEN("even generation should be vonNeumann"){
                REQUIRE(mParser.getAppValues().evenRuleName == "vonNeumann");
            }

            THEN("odd generation should be erik"){
                REQUIRE(mParser.getAppValues().oddRuleName == "erik");
            }
        }

    }
}

