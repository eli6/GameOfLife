/*
 * Filename    Population.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "Cell_Culture/Population.h"
#include "GoL_Rules/RuleFactory.h"
#include <random>
#include <ctime>
#include <string>
#include "Support/FileLoader.h"
#include "Support/Globals.h"

// Initializing cell culture and the concrete rules to be used in simulation.
void Population::initiatePopulation(string evenRuleName, string oddRuleName) {
    // Determine whether the cell culture should be randomized or built from file.
    if (!fileName.empty())
        buildCellCultureFromFile();
    else
        randomizeCellCulture();

    // create the rules we will use, based on specified rule names
    if (oddRuleName == "")	// if empty, same as even rule
        oddRuleName = evenRuleName;
    this->evenRuleOfExistence = RuleFactory::getInstance().createAndReturnRule(cells, evenRuleName);
    this->oddRuleOfExistence = RuleFactory::getInstance().createAndReturnRule(cells, oddRuleName);
}

// Send cells map to FileLoader, which will populate its culture based on file values.
void Population::buildCellCultureFromFile() {
    FileLoader fileLoader;
    fileLoader.loadPopulationFromFile(cells);
}

// Build cell culture based on randomized starting values.
void Population::randomizeCellCulture() {
    default_random_engine generator(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> random(0, 1);

    // allocate and map cells based on worldSize
    for (int row = 0; row <= WORLD_DIMENSIONS.HEIGHT + 1; row++) {

        for (int column = 0; column <= WORLD_DIMENSIONS.WIDTH + 1; column++) {
            // if cell is a rim cell
            if (column == 0 || row == 0
                || column == WORLD_DIMENSIONS.WIDTH + 1
                || row == WORLD_DIMENSIONS.HEIGHT + 1) {

                cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
            }
            else { // If cell is an ordinary cell
                if (random(generator)) { // Randomly pick alive/dead
                    cells[Point{column, row}] = Cell(false, GIVE_CELL_LIFE); // create a ordinary living cell
                }
                else {
                    cells[Point{column, row}] = Cell(false, IGNORE_CELL); // else create a ordinary dead cell
                }
            }
        }
    }
}

// Destructor that frees allocated memory.
Population::~Population() {
    if (evenRuleOfExistence != nullptr) {
        delete evenRuleOfExistence;
    }
    if (oddRuleOfExistence != nullptr) {
        delete oddRuleOfExistence;
    }
}

// Update the cell population and determine next generational changes based on rules.
int Population::calculateNewGeneration() {

    // update the states of cells
    for (auto it = cells.begin(); it != cells.end(); it++) {
        it->second.updateState();
    }

    // alternate between even / odd rule
    if (generation % 2 == 0) {
        evenRuleOfExistence->executeRule();
    }
    else {
        oddRuleOfExistence->executeRule();
    }
    return ++generation;
}