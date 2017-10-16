/*
 * Filename    RuleOfExistence_Conway.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
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
class RuleOfExistence_Conway : public RuleOfExistence
{
private:

public:
    RuleOfExistence_Conway(map<Point, Cell>& cells)
            : RuleOfExistence({ 2,3,3 }, cells, ALL_DIRECTIONS, "conway") {}

    ~RuleOfExistence_Conway() {}

    void executeRule();
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H
