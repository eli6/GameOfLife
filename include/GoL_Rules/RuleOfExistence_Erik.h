/**
 * @file        RuleOfExistence_Erik.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1
 * @brief       Contains RuleOfExistance_Erik class.
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
#define GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H

#include "RuleOfExistence.h"


/**
 * @brief Erik's RuleOfExistence, based on Conway's rule while also differentiate the appearance of cells based on their age.
 * @details - Once a cell has survived a minimum amount of generations it will recieve a color to distinguish itself from younger ones.
- If such a cell would then survive another set amount of generations, it will be marked with a value of **E**.
- In the extreme case, where the cell has achieved above requirements and is determined to be the oldest living cell, it will
become a **prime elder**, and have its color changed once again. A generation may only have one such elder.
 @test Test constructor and public members of this class.
 */
class RuleOfExistence_Erik : public RuleOfExistence
{
private:
    char usedCellValue;	// char value to differentiate very old cells.
    Cell* primeElder;

    void setPrimeElder(Cell* newElder);

public:
    /**
     * Getter public for testing
     */
    Cell* getPrimeElder(){ return primeElder; }

    /** MADE PUBLIC FOR TESTING
     * @brief Changes cells based on their generational status
     * @param cell The cell to be examined
     * @param action Action to take depending on number of neighbours.

     * @bug Cells older than 10 generations stop being cyan colored, which seems to be unintened
     */
    void erikfyCell(Cell& cell, ACTION action);

    /**
     * @brief Constructor for the class
     * @details Constructs a rule of existance object with population limits:
     * - UNDERPOPULATION : < 2
     * - OVERPOPULATION > 3
     * - RESURRECTION = 3
     * The rule will apply to all directions and the rule name is "Erik".
     * The specificity of the Erik rule is that the value "E" is also added to very old cells.
     * @test Test that the constructor produces a correct object.
     *
     * @param cells A map of Points and Cells that defines existing cells.
     */
    RuleOfExistence_Erik(map<Point, Cell>& cells)
            : RuleOfExistence({2,3,3}, cells, ALL_DIRECTIONS, "erik"), usedCellValue('E') {
        primeElder = nullptr;
    }

    /**
     * @brief Default destructor.
     * @details Destroys object at end of scope.
     * @test Test that the destructor is run at end of scope.
     */
    ~RuleOfExistence_Erik() {}

    /**
     * @brief Executes the rule to determine generational changes in the cell population.
     * @details Calculates how many alive neighbors a (non-rim) cell has and determines what action to take
       depending on neighbors and if the cell is alive or not. The cells new color will be set (for example dead/living).
       This Erik class also adds extra colors for cells older than 5 generations (cyan) and adds an "E" to cells older than 10 generations.
       A cell method is then invoked so that the cell can take further action.
     * @test Test that this method sets correct cell colors for different neighbor scenarios and that it adds an "E" to very old cells.
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

#endif //GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
