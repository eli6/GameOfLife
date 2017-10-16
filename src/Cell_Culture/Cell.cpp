/*
 * Filename    Cell.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/
#include "Cell_Culture/Cell.h"

/**
* Constructor that determines the cell's starting values.
* @param isRimCell whether the cell is a rim cell.
* @param action whether the cell should have a starting value. Defaults to DO_NOTHING.
*/
Cell::Cell(bool isRimCell, ACTION action) : details({ 0,STATE_COLORS.LIVING, isRimCell, '#' }) {
    // the cell will update to its initial state
    nextUpdate.nextColor = (action == GIVE_CELL_LIFE) ? STATE_COLORS.LIVING : STATE_COLORS.DEAD;
    nextUpdate.nextGenerationAction = action;
    nextUpdate.nextValue = details.value;

    updateState();
}

/**
* Updates the cell to its new state, based on stored update values.
* @return void
*/
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

/**
* Determines whether the cell is alive/dead.
* @return true if alive, else false
*/
bool Cell::isAlive() {
    if (details.rimCell) {
        return false;
    }
    else {
        return details.age > 0;
    }
}

/**
* Sets the cells next action to take in its coming update.
* @param action defining next update state.
* @return void
*/
void Cell::setNextGenerationAction(ACTION action) {
    if (details.rimCell)
        return;

    if (action == GIVE_CELL_LIFE && isAlive())
        return;

    this->nextUpdate.nextGenerationAction = action;
}