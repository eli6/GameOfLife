
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
        WHEN("We create an instance of ApplicationValues and a pointer to char") {
            ApplicationValues av;
            char* ch = nullptr;

            // test with nullptr
            THEN("Calling execute() with a nullptr argument should set runSimulation to 'false' ") {
                garg.execute(av, ch);
                REQUIRE_FALSE(av.runSimulation);
                AND_THEN("maxGenerations should still be set to default = 100") {
                    REQUIRE(av.maxGenerations == 100);
                }
            }

            // test with expected argument
            THEN("Calling execute() with an expected argument type should set generations to that value") {
                char str[] = {"50"};
                ch = str;   // creating an expected char* value type
                garg.execute(av, ch);
                REQUIRE(av.maxGenerations == 50);
            }

            // test with unexpected argument
            THEN("Calling execute() with an unexpected argument type should throw an exception") {
                char str[] = {"dummy"};
                ch = str;   // creating an unexpected char* value type
                REQUIRE_THROWS(garg.execute(av, ch));
            }
        }
    }

    // Testing WorldsizeArgument
    GIVEN("We create an instance of WorldsizeArgument") {
        WorldsizeArgument warg;
        THEN("argValue should be set to '-s' ") {
            REQUIRE(warg.getValue() == "-s");
        }
        WHEN("We create an instance of ApplicationValues and a pointer to char") {
            ApplicationValues av;
            char* ch = nullptr;

            // test with nullptr
            THEN("Calling execute() with a nullptr should set runSimulation to 'false' ") {
                warg.execute(av, ch);
                REQUIRE_FALSE(av.runSimulation);
            }

            // test expected argument
            THEN("Calling execute() with an expected argument should set the world dimensions") {
                char dimensions[] = {"50 100"}; // creating an expected argument
                ch = dimensions;
                warg.execute(av, ch);
                REQUIRE(WORLD_DIMENSIONS.WIDTH == 50);
                REQUIRE(WORLD_DIMENSIONS.HEIGHT == 100);
            }

            // test with unexpected argument
            THEN("Calling execute() with an unexpected argument should throw an exception") {
                char dummy[] = {"dummy"}; // creating an unexpected argument
                ch = dummy;
                REQUIRE_THROWS(warg.execute(av, ch));   // fails!
            }

        }
    }

    // Testing FileArgument
    GIVEN("We create an instance of FileArgument") {
        FileArgument farg;
        THEN("argValue should be set to '-f' ") {
            REQUIRE(farg.getValue() == "-f");
        }
        WHEN("We create an instance of ApplicationValues and a pointer to char") {
            ApplicationValues av;
            char *ch = nullptr;

            // test with nullptr
            THEN("Calling execute() with a nullptr argument should set runSimulation to 'false' ") {
                farg.execute(av, ch);
                REQUIRE_FALSE(av.runSimulation);
            }

            // test with string
            THEN("Calling execute() a string should set fileName to that value") {
                char str[] = {"newFileName"};
                ch = str;   // creating an expected char* value type
                farg.execute(av, ch);
                REQUIRE(fileName == "newFileName");
            }
        }
    }

    // Testing EvenRuleArgument
    GIVEN("We create an instance of EvenRuleArgument") {
        EvenRuleArgument earg;
        THEN("argValue should be set to '-er' ") {
            REQUIRE(earg.getValue() == "-er");
        }
        WHEN("We create an instance of ApplicationValues and a pointer to char") {
            ApplicationValues av;
            char *ch = nullptr;

            // test with nullptr
            THEN("Calling execute() with a nullptr argument should set runSimulation to 'false' ") {
                earg.execute(av, ch);
                REQUIRE_FALSE(av.runSimulation);
            }

            // test with string
            THEN("Calling execute() with a string argument should set evenRuleArgument to that value") {
                char str[] = {"evenRule"};
                ch = str;   // creating an expected char* value type
                earg.execute(av, ch);
                REQUIRE(av.evenRuleName == "evenRule");
            }
        }
    }

    // Testing with OddRuleArgument
    GIVEN("We create an instance of OddRuleArgument") {
        OddRuleArgument oarg;
        THEN("argValue should be set to '-or' ") {
            REQUIRE(oarg.getValue() == "-or");
        }
        WHEN("We create an instance of ApplicationValues and a pointer to char") {
            ApplicationValues av;
            char *ch = nullptr;

            // test with nullptr
            THEN("Calling execute() with a nullptr argument should set runSimulation to 'false' ") {
                oarg.execute(av, ch);
                REQUIRE_FALSE(av.runSimulation);
            }

            // test with string
            THEN("Calling execute() with a string argument should set evenRuleArgument to that value") {
                char str[] = {"oddRule"};
                ch = str;   // creating an expected char* value type
                oarg.execute(av, ch);
                REQUIRE(av.oddRuleName == "oddRule");
            }
        }
    }
}