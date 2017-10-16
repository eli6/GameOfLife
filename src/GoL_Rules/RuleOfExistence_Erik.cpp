/*
 * Filename    RuleOfExistence_Erik.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "GoL_Rules/RuleOfExistence_Erik.h"

// Execute the rule specific for Erik.
void RuleOfExistence_Erik::executeRule() {
    for (auto it = cells.begin(); it != cells.end(); it++) {

        // referens current cell
        Cell& cell = it->second;

        // Ignore cells that is part of the rim
        if (cell.isRimCell())
            continue;

        // get amount of alive neighbouring cells
        int aliveNeighbours = countAliveNeighbours(it->first);

        // determine action for cell
        ACTION action = getAction(aliveNeighbours, cell.isAlive());

        if (action == KILL_CELL)
            cell.setNextColor(STATE_COLORS.DEAD);

        else if (action == GIVE_CELL_LIFE)
            cell.setNextColor(STATE_COLORS.LIVING);



        // With age comes experience. Cells older than 5 generations recieves a cyan color.
        // If the cell is older than 10 generations, it gets the value 'E' (for Erik) showing
        // its total awesomeness.
        erikfyCell(cell, action);

        // the cell will know what to do, based on this action
        cell.setNextGenerationAction(action);
    }
}

/*
* With age comes experience. Cells older than 5 generations recievees an old age color.
* If the cell is older than 10 generations, it also gets the value 'E' (for Erik) signifying
* a sentient lifeform of great wisdom. Thus proving, that intelligent life can be created using
* cellular automata.
*/
void RuleOfExistence_Erik::erikfyCell(Cell& cell, ACTION action) {
    if (action != KILL_CELL) {

        int cellAge = cell.getAge();

        // A somewhat old cell will get a color differentiating it
        if (cellAge > 4)
            cell.setNextColor(STATE_COLORS.OLD);

        // A very old cell will get a value of 'E'
        if (cellAge > 9) {
            cell.setNextCellValue(usedCellValue);

            // Determine prime elder, an extremely rare case where a cell has survived longer than any other.
            if (primeElder == nullptr || cell.getAge() > primeElder->getAge())
                setPrimeElder(&cell);
        }
    }

        // An old cell dies, reset its value
    else if (cell.getCellValue() == usedCellValue) {
        cell.setNextCellValue('#');

        // if the cell is a prime elder, nullify pointer
        if(&cell == primeElder)
            primeElder = nullptr;
    }
}

/*
Sets the prime elder, a very rare occasion of a cell surviving longer than any other. Only one cell
can be elder at a time.
*/
void RuleOfExistence_Erik::setPrimeElder(Cell* newElder) {
    if (primeElder != nullptr)
        primeElder->setNextColor(STATE_COLORS.OLD);

    primeElder = newElder;
    primeElder->setNextColor(STATE_COLORS.ELDER);
}