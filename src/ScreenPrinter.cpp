/*
 * Filename    ScreenPrinter.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "ScreenPrinter.h"
#include <iostream>

using namespace std;

// Prints the population to screen
void ScreenPrinter::printBoard(Population& population) {

    // TODO change to dimension
    int windowHeight = WORLD_DIMENSIONS.HEIGHT + 1;
    int windowWidth = WORLD_DIMENSIONS.WIDTH + 1;

    terminal.showCursor(false);	// hide cursor

    // Each row
    for (int row = 0; row <= windowHeight; row++) {
        // Each column
        for (int column = 0; column <= windowWidth; column++) {
            // Get cell att position [column,row]
            Cell cell = population.getCellAtPosition(Point{column, row});

            // set cursor to relevant point
            terminal.setCursor(column, row);

            // If cell isn't a rim cell
            if (!cell.isRimCell()) {

                // Get cell color
                COLOR cellColor = cell.getColor();

                // Change terminal color
                terminal.pushColor(TerminalColor(cellColor, STATE_COLORS.DEAD));

                // Write cell to screen
                cout << cell.getCellValue();

                // Reset color
                terminal.popColor();
            }
        }
    }
}

// Prints the help screen
void ScreenPrinter::printHelpScreen() {
    cout << "-h help" << endl << endl
         << "-er <Even rulename> [default=conway]" << endl
         << "\tconway" << endl
         << "\tvon_neumann" << endl
         << "\terik" << endl << endl
         << "-or <Odd rulename> [default=same as even]" << endl
         << "\tconway" << endl
         << "\tvon_neumann" << endl
         << "\terik" << endl << endl
         << "-g <Amount of generations> [default=500]" << endl << endl
         << "-s <World dimensions> [default=80x24]" << endl << endl
         << "-f <Filename for initial state> [default=random state]" << endl
         << "\tfilename overrides -s argument" << endl;
}

// print message, som information to the user (i.e. error messages)
void ScreenPrinter::printMessage(string message) {
    cout << message << endl;
}

// Clears the terminal
void ScreenPrinter::clearScreen() {

    terminal.clear();
}