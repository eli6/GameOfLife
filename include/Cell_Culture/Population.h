/*
 * Filename    Population.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#ifndef POPULATION_H
#define POPULATION_H

#include<map>
#include<string>
#include "Cell.h"
#include "Support/Globals.h"
#include "GoL_Rules/RuleOfExistence.h"
#include "GoL_Rules/RuleFactory.h"

using namespace std;

/*
Representation of the complete society of cell existance and interactions.

The Population constitutes of all current, previous and future generations of cells, both living and dead
as well as those not yet born. By mapping all cells to their respective positions in the simulation world,
Population has the complete knowledge of each cell's whereabouts. Furthermore, the class is responsible for
determining which rules should be required from the RuleFactory, and store the pointer to these as members.

Population's main responsibility during execution is determining which rule to apply for each new generation
and updating the cells to their new states.
*/
/***
 * @brief
 * @details
 * @test
 */
class Population
{
private:
    int generation;
    map<Point, Cell> cells;
    RuleOfExistence* evenRuleOfExistence;
    RuleOfExistence* oddRuleOfExistence;

    void randomizeCellCulture();
    void buildCellCultureFromFile();

public:
    Population() : generation(0), evenRuleOfExistence(nullptr), oddRuleOfExistence(nullptr) {}
    ~Population();

    void initiatePopulation(string evenRuleName, string oddRuleName = "");
    int calculateNewGeneration();

    // Returns cell by specified key value.
    Cell& getCellAtPosition(Point position) { return cells.at(position); }

    // Gets the total amount of cells in the population, regardless of state.
    int getTotalCellPopulation() { return cells.size(); }

};

#endif