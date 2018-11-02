/**
 * @file
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the class RuleFactory
 */

#ifndef RULEFACTORY_H
#define RULEFACTORY_H

#include "../GoL_Rules/RuleOfExistence.h"

/**
 * @brief Singleton class to handle creation of RulesOfExistence objects.
 * @details Has two methods, and one of them returns a pointer to a RuleOfExistence object
 * where the type depends on the rule name given as argument, the other returns a reference
 * to an instance of a RuleFactory.
 * @test That an object is created correctly.
 */
class RuleFactory
{
private:
    RuleFactory() {}

public:
    /**
     * @brief Creates an instance of RuleFactory.
     * @details Returns a reference to that instance.
     * @return A reference to a RuleFactory object
     * @test Check so that the RuleFactory object is created correctly
     */
    static RuleFactory& getInstance();

    /**
     * @brief Creates an instance of a RuleOfExistence
     * @details The type depends on the ruleName parameter, where default is 'conway'
     * @param cells A reference to a map<Point, Cell>
     * @param ruleName A string with the default value 'conway'
     * @return A pointer to a RuleOfExistence object
     * @test That a correct type is created with the different names
     * @bug Function does not throw when the ruleName does not exist, and silently defaults to conway.
     */
    RuleOfExistence* createAndReturnRule(map<Point, Cell>& cells, string ruleName = "conway");
};

#endif