/*
 * Filename    ScreenPrinter.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/



#ifndef screenPrinterH
#define screenPrinterH


#include "../terminal/terminal.h"
#include "Cell_Culture/Population.h"

// Responsible for visually representing the simulation world on screen.
class ScreenPrinter {

private:
    Terminal terminal;

    ScreenPrinter() {}

public:
    static ScreenPrinter& getInstance() {
        static ScreenPrinter instance;
        return instance;
    }


    void printBoard(Population& population);

    void printHelpScreen();

    void printMessage(string message);

    void clearScreen();
};

#endif
