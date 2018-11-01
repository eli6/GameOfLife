
/**
* @file
 * @author Fredrik Arhusiander
 * @date 1 November 2018
 * @version 0.1
 * @brief Contains all the tests for the class MainArguments
*/

#include "catch2.hpp"
#include "Support/MainArguments.h"

SCENARIO("Testing the class BaseArgument and its derived classes") {

    // Testing HelpArgument
    GIVEN("We create an instance of HelpArgument") {
        HelpArgument harg;
        THEN("argValue should be set to '-h' ") {
            REQUIRE(harg.getValue() == "-h");
        }
        WHEN("We create an instance of ApplicationValues") {
            ApplicationValues av;
            THEN("runSimulation should be set to 'false' when it's passed as an argument to execute()") {
                char* dummy = nullptr;  // dummy char* to pass to execute()
                harg.execute(av, dummy);
                REQUIRE_FALSE(av.runSimulation);
            }
        }
    }

    // Testing GenerationsArgument
    GIVEN("We create an instance of GenerationsArgument") {
        GenerationsArgument garg;
        THEN("argValue should be set to '-g' ") {
            REQUIRE(garg.getValue() == "-g");
        }
        WHEN("We create an instance of ApplicationValues") {
            ApplicationValues av;
            char* ch = nullptr;

            // test no arg
            THEN("Calling execute() with a nullptr argument should set runSimulation to 'false' ") {
                garg.execute(av, ch);
                REQUIRE_FALSE(av.runSimulation);
            }

            // test good arg
            THEN("Calling execute() with a correct argument should set generations to that value") {
                char str[] = {"50"};
                ch = str;

                garg.execute(av, ch);
                REQUIRE(av.maxGenerations == 50);
            }

            // test bad arg
            THEN("Calling execute() with an incorrect argument should throw an exception") {
                char* dummy = "dummy";
                REQUIRE_THROWS(garg.execute(av, dummy));
            }

        }
    }
/*
    // Testing WorldsizeArgument
    GIVEN("We create an instance of WorldsizeArgument") {
        WorldsizeArgument warg;
        THEN("argValue should be set to '-s' ") {
            REQUIRE(warg.getValue() == "-s");
        }
        WHEN("We create an instance of ApplicationValues") {
            ApplicationValues av;

            // test no arg
            THEN("Calling execute() with no char* argument should set runSimulation to 'false' ") {
                warg.execute(av);
                REQUIRE_FALSE(av.runSimulation);
            }

            // test good arg
            THEN("Calling execute() with a correct argument should set the world dimensions") {
                garg.execute(av, Dimensions{50,100});
                REQUIRE(av.generations == 50);
            }

            // test bad arg
            THEN("Calling execute() with an incorrect argument should throw an exception") {
                char* dummy = "dummy";
                REQUIRE_THROWS(garg.execute(av, dummy));
            }

        }
    }*/


}