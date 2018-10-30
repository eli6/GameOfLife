/**
 * @file
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the class ScreenPrinter
*/



#ifndef screenPrinterH
#define screenPrinterH


#include "../terminal/terminal.h"
#include "Cell_Culture/Population.h"

/**
 * @class Cell
 * @brief Responsible for visually representing the simulation world on screen.
 * @test Test so that member functions do as they should
 */
class ScreenPrinter {

private:
    Terminal terminal;

    ScreenPrinter() {}

public:
    static ScreenPrinter& getInstance() {
        static ScreenPrinter instance;
        return instance;
    }

    /**
     * @brief Prints the population of cells to the screen
     * @details The function uses a for-loop to loop through the cells at each position
     * using the height and width of the world. For each cell it first checks so it's not
     * a rim cell, then it gets the color,  pushes the color to the terminal, prints it
     * to the screen, and finally resets the color for the next iteration. The printing
     * is done by std::cout and the Cell function getCellValue().
     * @param population A reference to a Population object.
     * @test It should print the correct colors, and it should print the color of every cell.
     * @bug there is something unfinished in the function implementation.
     */
    void printBoard(Population& population);

    /**
     * @brief Prints help screen
     * @test The output is static so it should always print the same text.
     */
    void printHelpScreen();

    /**
     * @brief Prints a message to the screen
     * @details The message that is printed is a string given as an argument to the function
     * @param message A string value
     * @test so that it prints the correct message
     */
    void printMessage(string message);

    /**
     * @brief Clears the screen
     * @test The screen should be cleared.
     */
    void clearScreen();
};

#endif
