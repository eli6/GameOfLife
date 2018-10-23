/**
 * @file    RuleOfExistence_Conway.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1
 * @brief       Contains RuleOfExistance_Conway class.
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H
#define GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H

#include "RuleOfExistence.h"
/*
Conway's RuleOfExistence, applying actions based on PopulationLimits on all 8 surrounding neighbours.

Concrete RuleOfExistence, implementing Conway's rule of determining alive neighbours surrounding the cell
by checking all 8 directions, 4 x Cardinal + 4 x Diagonal. PopulationLimits are set as;

*UNDERPOPULATION	< 2*	**Cell dies of loneliness**
*OVERPOPULATION		> 3*	**Cell dies of overcrowding**
*RESURRECTION		= 3*	**Cell is infused with life**
*/

/**
 * @brief Conway's RuleOfExistence, applying actions based on PopulationLimits on all 8 surrounding neighbours.
 * @details Concrete RuleOfExistence, implementing Conway's rule of determining alive neighbours surrounding the cell
    by checking all 8 directions, 4 x Cardinal + 4 x Diagonal. PopulationLimits are set as: UNDERPOPULATION	< 2*	**Cell dies of loneliness** | OVERPOPULATION		> 3*	**Cell dies of overcrowding** | RESURRECTION		= 3*	**Cell is infused with life**
 * @test Test public methods and constructor.
 */
class RuleOfExistence_Conway : public RuleOfExistence
{
private:

public:
    /**
     * @brief Constructor for a Conway-Rule of Existence.
     * @details Constructs a rule of existance with all 8 directions
     * (4 x cardinal 4 x diagonal). <br>UNDERPOPULATION = <2 <br> OVERPOPULATION = >3 <br>RESURRECTION = 3.
     * @test Test that a correct RuleOfExistence_Conway object is created.
     *
     * @param cells Map of existing cells and their points.
     */
    RuleOfExistence_Conway(map<Point, Cell>& cells)
            : RuleOfExistence({ 2,3,3 }, cells, ALL_DIRECTIONS, "conway") {}

    /**
     * @brief Class destructor.
     * @details Default destructor for class.
     * @test Check that it is run at end of scope.
     */
    ~RuleOfExistence_Conway() {}

    /**
     * @brief Executes the rule to determine generational changes in the cell population.
     * @details Calculates how many alive neighbors a (non-rim) cell has and determines what action to take
       depending on neighbors and if the cell is alive or not. The cells new color will be set (for example dead/living) and a cell method is invoked so that the cell can take further action.
     * @test Test that this method sets correct cell colors for different neighbor scenarios.
     */
    void executeRule();
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H
