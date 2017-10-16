/*
 * Filename    GameOfLife.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "GameOfLife.h"
#include <thread>
#include <chrono>
#include "GoL_Rules/RuleFactory.h"

/** Constructor for the game object, calls initialization of cell population.
@param nrOfGenerations specifies the amount of generations to be simulated.
@param evenRuleName the name of the rule to be used on even iterations.
@param oddRuleName the name of the rule to be used on odd iterations.
*/
GameOfLife::GameOfLife(int nrOfGenerations, string evenRuleName, string oddRuleName)
        : nrOfGenerations(nrOfGenerations), screenPrinter(ScreenPrinter::getInstance()) {

    // initiate population
    population.initiatePopulation(evenRuleName, oddRuleName);
}

/**
* Run the simulation for as many generations as been set by the user (default = 500).
* For each iteration; calculate population changes and print the information on screen.
*/
void GameOfLife::runSimulation() {

    // Clears the terminal
    screenPrinter.clearScreen();

    // Print generation zero
    screenPrinter.printBoard(population);

    // For each generation
    while (population.calculateNewGeneration() < nrOfGenerations) {
        // Print the calculated generation
        screenPrinter.printBoard(population);

        this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // We are done with the factory, we can delete the instance.
    // However, a singleton is not a leak and should by its nature not be deleted. But for the
    // sake of the assignment, we will comply with the no-leak requirement.
//    delete RuleFactory::getInstance();
}