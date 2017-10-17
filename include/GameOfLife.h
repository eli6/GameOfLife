/*
 * Filename    GameOfLife.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#ifndef GameOfLifeH
#define GameOfLifeH

#include "Cell_Culture/Population.h"
#include "ScreenPrinter.h"
#include <string>

/*
The heart of the simulation, interconnects the main execution with the graphical presentation.

Creates and manages Population and the ScreenPrinter instances. Will instruct the Population of cells to keep
updating as long as the specified number of generations is not reached, and for each iteration instruct
ScreenPrinter to write the information on screen.
*/
class GameOfLife {

private:
    Population population;
    ScreenPrinter& screenPrinter;
    int nrOfGenerations;

public:
    GameOfLife(int nrOfGenerations, string evenRuleName, string oddRuleName);

    void runSimulation();

};

#endif
