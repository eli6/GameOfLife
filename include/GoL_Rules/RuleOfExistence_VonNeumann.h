/**
 * @file    RuleOfExistence_VonNeumann.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1
 * @brief   Contains class RuleOfExistence_VonNeumann
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
#define GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H

#include "RuleOfExistence.h"
/**
*   @brief Von Neumann's RuleOfExistence, differs from Conway in that only 4 neighbours are accounted for.
*
*   @details Concrete Rule of existence, implementing Von Neumann's rule.
*   Only difference from Conway is that neighbours are determined using only cardinal directions (N, E, S, W).
*
*   @test Test constructor/destructor and executeRule().
*/
class RuleOfExistence_VonNeumann : public RuleOfExistence
{
private:

public:
    /**
     * @brief Constructor for a vonNeumann-Rule of Existence.
     * @details Very similar to Conwways rule, except that only cardinal directions are used.
     * PopulationLimits are set as:
     * - UNDERPOPULATION	< 2
     * - OVERPOPULATION   > 3
     * - RESURRECTION     = 3
     *
     * @param cells Map of cells and their points.
     */
    RuleOfExistence_VonNeumann(map<Point, Cell>& cells)
            : RuleOfExistence({ 2,3,3 }, cells, CARDINAL, "von_neumann") {}

    /**
    * @brief Class destructor.
    * @details Default destructor for class.
    * @test Check that it is run at end of scope.
    */
    ~RuleOfExistence_VonNeumann() {}

    /**
     * @brief Executes the rule to determine generational changes in the cell population.
     * @details Calculates how many alive neighbors a (non-rim) cell has and determines what action to take
       depending on neighbors and if the cell is alive or not. The cells new color will be set (for example dead/living) and a cell method is invoked so that the cell can take further action.
     * @test Test that this method sets correct cell colors for different neighbor scenarios.
     */
    void executeRule();

    /**
     * @brief Returns cell by specified Point value.
     * @param position A Point data type
     * @return A reference to a Cell object
     */
    Cell& getCellAtPosition(Point position) { return cells.at(position); }

    /** TEST FUNCTION
    * @brief Gives the number of alive neighbors aftr each rule execution.
    * @details Useful for testing if executeRule() counts alive neighbors correctly.
    *
    */
    int countAlive(Point aPoint){
        Cell cell = getCellAtPosition(aPoint);
        if(!cell.isRimCell()){
            int aliveN = countAliveNeighbours(aPoint);
            return aliveN;
        }
        return 0;

    }
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
