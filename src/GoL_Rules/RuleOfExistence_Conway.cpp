/*
 * Filename    RuleOfExistence_Conway.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "GoL_Rules/RuleOfExistence_Conway.h"

// Execute the rule specific for Conway.
void RuleOfExistence_Conway::executeRule() {
    for (auto it = cells.begin(); it != cells.end(); it++) {

        // referens current cell
        Cell& cell = it->second;

        // Ignore cells that is part of the rim
        if (cell.isRimCell())
            continue;

        // get amount of alive neighbouring cells
        int aliveNeighbours = countAliveNeighbours(it->first);
        std::cout << it->first.x << "," << it->first.y << " ";

        std::cout << "aliveNeighbors: " << aliveNeighbours << std::endl;

        // determine action for cell
        ACTION action = getAction(aliveNeighbours, cell.isAlive());

        if (action == KILL_CELL)
            cell.setNextColor(STATE_COLORS.DEAD);

        else if (action == GIVE_CELL_LIFE)
            cell.setNextColor(STATE_COLORS.LIVING);

        // the cell will know what to do, based on this action
        cell.setNextGenerationAction(action);
    }
}