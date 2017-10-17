/*
 * Filename    RuleFactory.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "GoL_Rules/RuleFactory.h"
#include "GoL_Rules/RuleOfExistence_Conway.h"
#include "GoL_Rules/RuleOfExistence_VonNeumann.h"
#include "GoL_Rules/RuleOfExistence_Erik.h"

// Singleton factory receiver.
RuleFactory& RuleFactory::getInstance() {
    static RuleFactory ruleFactory;	// only one instance of variable is allowed
    return ruleFactory;
}

// Creates and returns specified RuleOfExistence.
RuleOfExistence* RuleFactory::createAndReturnRule(map<Point, Cell>& cells, string ruleName) {
    if (ruleName == "von_neumann")
        return new RuleOfExistence_VonNeumann(cells);
    else if (ruleName == "erik")
        return new RuleOfExistence_Erik(cells);

    // defaults to Conway's rule
    return new RuleOfExistence_Conway(cells);
}