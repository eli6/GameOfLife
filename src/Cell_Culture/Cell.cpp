/*
 * Filename    Cell.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/
#include "Cell_Culture/Cell.h"

// Constructor that determines the cell's starting values.
Cell::Cell(bool isRimCell, ACTION action) : details({ 0,STATE_COLORS.LIVING, isRimCell, '#' }) {
    // the cell will update to its initial state
    nextUpdate.nextColor = (action == GIVE_CELL_LIFE) ? STATE_COLORS.LIVING : STATE_COLORS.DEAD;
    nextUpdate.nextGenerationAction = action;
    nextUpdate.nextValue = details.value;

    updateState();
}

// Updates the cell to its new state, based on stored update values.
void Cell::updateState() {
    switch (this->nextUpdate.nextGenerationAction)
    {
        case KILL_CELL:
            killCell();
            break;
        case IGNORE_CELL:
            if (isAlive())
                incrementAge();
            break;
        case GIVE_CELL_LIFE:
            if(!details.rimCell)
                incrementAge();
            break;
    }

    // should the color be updated
    if (details.color != nextUpdate.nextColor)
        setColor(nextUpdate.nextColor);

    // should the value be updated
    if (details.value != nextUpdate.nextValue)
        setCellValue(nextUpdate.nextValue);

    this->nextUpdate.nextGenerationAction = DO_NOTHING;	// reset next action
}

// is the cell alive?
bool Cell::isAlive() {
    if (details.rimCell) {
        return false;
    }
    else {
        return details.age > 0;
    }
}

// Sets the cells next action to take in its coming update.
void Cell::setNextGenerationAction(ACTION action) {
    if (details.rimCell)
        return;

    if (action == GIVE_CELL_LIFE && isAlive())
        return;

    this->nextUpdate.nextGenerationAction = action;
}