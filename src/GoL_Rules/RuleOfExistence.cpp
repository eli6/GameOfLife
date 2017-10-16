/*
 * Filename    RuleOfExistence.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "GoL_Rules/RuleOfExistence.h"


// Determines the amount of alive neighbouring cells to current cell, using directions specified by the rule.
int RuleOfExistence::countAliveNeighbours(Point currentPoint) {
    // get current cell position
    int column = currentPoint.x;
    int row = currentPoint.y;

    int aliveNeighbours = 0;

    Point targetPoint;
    // check neighbouring cells in all directions relevant for the rule
    for (auto direction : DIRECTIONS) {
        targetPoint.x = column + direction.HORIZONTAL;	// target cell's column
        targetPoint.y = row + direction.VERTICAL;		// target cell's row

        // is the neighbouring cell alive
        if (cells.at(targetPoint).isAlive())
            aliveNeighbours++;
    }

    return aliveNeighbours;
}

// Determines what action should be taken regarding the current cell, based on alive neighbouring cells.
ACTION RuleOfExistence::getAction(int aliveNeighbours, bool isAlive) {
    if (isAlive) {
        if (aliveNeighbours < POPULATION_LIMITS.UNDERPOPULATION)
            return KILL_CELL;
        else if (aliveNeighbours > POPULATION_LIMITS.OVERPOPULATION)
            return KILL_CELL;
        else
            return IGNORE_CELL;
    }

    else if (aliveNeighbours == POPULATION_LIMITS.RESURRECTION)
        return GIVE_CELL_LIFE;

    return DO_NOTHING;
}







