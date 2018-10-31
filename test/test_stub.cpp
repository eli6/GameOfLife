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

            char *argv[] = {&arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], &arg5[0], &arg6[0], &arg7[0], &arg8[0], &arg9[0], &arg10[0],
                            nullptr};

            ApplicationValues appValues = mParser.runParser(argv, 11);

            THEN("filename should be set to filename.txt"){
                REQUIRE(fileName == "filename.txt");
            }

            //works but program crashes if the value can't be converted to string. should be a bug in GenerationsArgument
            THEN("generations should be 3"){
                REQUIRE(appValues.maxGenerations == 3);
            }

            THEN("world dimensions should be 20x10"){
                REQUIRE(WORLD_DIMENSIONS.WIDTH == 20);
                REQUIRE(WORLD_DIMENSIONS.HEIGHT == 10);
            }

            THEN("even generation should be vonNeumann"){
                REQUIRE(appValues.evenRuleName == "vonNeumann");
            }

            THEN("odd generation should be erik"){
                REQUIRE(appValues.oddRuleName == "erik");
            }
        }

        WHEN("we don't specify all rules in argv, runParser() should set correct defaults"){

            WHEN("we only specify the odd rule") {
                char arg0[] = {"GameOfLife"};
                char arg1[] = {"-or"};
                char arg2[] = {"erik"};


                char *argv[] = {&arg0[0], &arg1[0], &arg2[0], nullptr};

                ApplicationValues appValues = mParser.runParser(argv, 3);

                THEN("odd generation should be erik") {
                    REQUIRE(appValues.oddRuleName == "erik");
                }

                THEN("even rule name should have defaulted to conway") {
                    REQUIRE(appValues.evenRuleName == "conway");
                }
            }
            WHEN("we only specify the even rule"){
                char arg0[] = {"GameOfLife"};
                char arg1[] = {"-er"};
                char arg2[] = {"erik"};


                char *argv[] = {&arg0[0], &arg1[0], &arg2[0], nullptr};

                ApplicationValues appValues = mParser.runParser(argv, 3);

                THEN("odd rule should have been set to the same, ie. erik") {
                    REQUIRE(appValues.oddRuleName == "erik");
                }

                THEN("even rule name should be erik") {
                    REQUIRE(appValues.evenRuleName == "erik");
                }
            }

            WHEN("we dont specify any rule names as all"){
                char arg0[] = {"GameOfLife"};


                char *argv[] = {&arg0[0], nullptr};

                ApplicationValues appValues = mParser.runParser(argv, 1);

                THEN("odd rule should not have defaulted to conway") {
                    REQUIRE(appValues.oddRuleName == "conway");
                }

                THEN("so should the even rule name") {
                    REQUIRE(appValues.evenRuleName == "conway");
                }
            }

            WHEN("we specify some nonsense options as wekk"){

                char arg0[] = {"GameOfLife"};
                char arg1[] = {"-xy"};
                char arg2[] = {"erik"};
                char arg3[] = {"-f"};
                char arg4[] = {"minfil.txt"};
                char arg5[] = {"-jlfkjsdkf"};
                char arg6[] = {"kul"};

                char *argv[] = {&arg0[0], &arg1[0], &arg2[0], &arg3[0],&arg4[0], &arg5[0], &arg6[0], nullptr};

                ApplicationValues appValues = mParser.runParser(argv, 7);

                THEN("The file value should still be read"){
                    REQUIRE(fileName == "minfil.txt");
                }


            }

        }

    }
}

