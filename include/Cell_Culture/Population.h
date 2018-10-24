/**
 * @file Population.h
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the class Population
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

/**
 * @brief Representation of the complete society of cell existance and interactions.
 * @details The Population constitutes of all current, previous and future generations of cells,
 * both living and dead as well as those not yet born. By mapping all cells to their respective
 * positions in the simulation world, population has the complete knowledge of each cell's whereabouts.
 * Furthermore, the class is responsible for determining which rules should be required from the
 * RuleFactory, and store the pointer to these as members.
 *
 * Population's main responsibility during execution is determining which rule to apply for each
 * new generation and updating the cells to their new states.
 *
 * @test Test so that the constructor/destructor and the member functions do what they should
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
    /**
     * @brief Constructor for Population
     * @details Sets 'generation' to 0, and the two pointers to 'nullptr'.
     * @test The constructor should set the members to the correct values
     */
    Population() : generation(0), evenRuleOfExistence(nullptr), oddRuleOfExistence(nullptr) {}

    /**
     * @brief Destructor for Population
     * @test The object should be destroyed at the end of scope
     */
    ~Population();

    /**
     * @brief Initiates the population of cells
     * @details Based on the name of the rule, for example "Erik". It's optional to have
     * a second rule.
     * @param evenRuleName A string value representing a rule name
     * @param oddRuleName A string value representing a rule name. It will be set equal to evenRuleName
     * if no value is given.
     * @test If 'fileName' is empty, it should build cell culture randomly, otherwise from
     * file. If oddRuleName is empty, it should equal evenRuleName. The cell culture chould
     * be initiated correctly, check the 'cells' member after initialization.
     */
    void initiatePopulation(string evenRuleName, string oddRuleName = "");
    int calculateNewGeneration();

    /**
     * @brief Returns cell by specified Point value.
     * @param position A Point data type
     * @return A reference to a Cell object
     */
    Cell& getCellAtPosition(Point position) { return cells.at(position); }

    /**
     * @brief Getter for the number of Cells in the population
     * @return An int representing the Cell population size
     */
    int getTotalCellPopulation() { return cells.size(); }

};

#endif