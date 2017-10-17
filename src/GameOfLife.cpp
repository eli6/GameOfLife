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

GameOfLife::GameOfLife(int nrOfGenerations, string evenRuleName, string oddRuleName)
        : nrOfGenerations(nrOfGenerations), screenPrinter(ScreenPrinter::getInstance()) {

    // initiate population
    population.initiatePopulation(evenRuleName, oddRuleName);
}

/*
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
}