#include "catch2.hpp"
#include <map>
#include "../include/GoL_Rules/RuleFactory.h"

SCENARIO("we create and return a rule of existence"){
    GIVEN("a rule factory object and a cell map"){
        RuleFactory ruleFactory = RuleFactory::getInstance();
        map<Point,Cell> cells;

        //we create a rule and rulename for use in tests below
        RuleOfExistence *rule;
        std::string ruleName;

        WHEN("We pass an existing rule into the function") {
            ruleName = "von_neumann";
            rule = ruleFactory.createAndReturnRule(cells, "von_neumann");
            THEN("the rules name should match the one we entered") {
                REQUIRE(rule->getRuleName() == ruleName);
            }
        }
        WHEN("We pass a non existant rule into the function"){
            ruleName = "elin";
            THEN("The function should throw"){
                REQUIRE_THROWS(ruleFactory.createAndReturnRule(cells, ruleName));
            }

        }
        WHEN("We pass no rule name into the function"){
            rule = ruleFactory.createAndReturnRule(cells);
            THEN("The rule should have defaulted to conway"){
                REQUIRE(rule->getRuleName() == "conway");
            }
        }

    }


}



