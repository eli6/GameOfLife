/*
 * Filename    main.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include <iostream>
#include "GameOfLife.h"
#include "Support/MainArgumentsParser.h"

#ifdef DEBUG
#include <memstat.hpp>
#endif

using namespace std;

int main(int argc, char* argv[]) {

    MainArgumentsParser parser;
    ApplicationValues appValues = parser.runParser(argv, argc);

    if (appValues.runSimulation) {
        // Start simulation
        try {
            GameOfLife gameOfLife = GameOfLife(appValues.maxGenerations, appValues.evenRuleName, appValues.oddRuleName);
            gameOfLife.runSimulation();
        }
        catch(ios_base::failure &e){}

    }

    cout << endl;
    return 0;
}
