/**
 * @file
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the class GameOfLife
*/

#ifndef GameOfLifeH
#define GameOfLifeH

#include "Cell_Culture/Population.h"
#include "ScreenPrinter.h"
#include <string>

/**
 * @class GameOfLife
 * @brief The heart of the simulation, interconnects the main execution with the graphical presentation.
 * @details Creates and manages the Population and ScreenPrinter instances. Will instruct the population
 * of cells to keep updating as long as the specified number of generations is not reached, and for each
 * iteration instruct ScreenPrinter to print the information to the screen.
 * @test Constructor and member function
 */
class GameOfLife {

private:
    Population population;
    ScreenPrinter& screenPrinter;
    int nrOfGenerations;

public:
    /**
     * @brief Constructor that takes one int and two string values as parameters
     * @details The int sets the number of generations, the two strings sets the even and odd rule names. An
     * instance of ScreenPrinter is also created and lastly initiatePopulation() is called on the member
     * population.
     * @param nrOfGenerations An int value
     * @param evenRuleName A string value
     * @param oddRuleName A string value
     * @test 1) The even and odd rule names should be correctly set 2) The population should be initiated with
     * those values.
     */
    GameOfLife(int nrOfGenerations, string evenRuleName, string oddRuleName);

    /**
     * @brief Runs the simulation for the set number of generations
     * @details The default number of generations is 500. The sequence is as follows:
     * 1. Clear the screen through the ScreenPrinter object
     * 2. Print the first population onto the screen
     * 3. Continue to calculate new generations and printing them until all generations have been computed.
     * @test It should run the correct number of generations
     * @bug Doesn't throw exception when GameOfLife object is created with incorrect values
     */
    void runSimulation();

    /*
     * Test functions, written for testing purposes
     */
    Population& getPopulation() { return population; }

};

#endif
