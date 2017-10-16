/*
 * Filename    MainArguments.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "Support/MainArguments.h"

void BaseArgument::printNoValue() {
    ScreenPrinter::getInstance().printMessage("No value for " + argValue + " found!");
}

void HelpArgument::execute(ApplicationValues& appValues, char* value) {
    ScreenPrinter::getInstance().printHelpScreen();
    appValues.runSimulation = false;
}

void GenerationsArgument::execute(ApplicationValues& appValues, char* generations) {
    if(generations)
        appValues.maxGenerations = stoi(generations);
    else {
        printNoValue();
        appValues.runSimulation = false;
    }
}

void WorldsizeArgument::execute(ApplicationValues& appValues, char* dimensions) {
    if (dimensions) {
        istringstream iss(dimensions);
        iss >> WORLD_DIMENSIONS.WIDTH;
        iss.get();
        iss >> WORLD_DIMENSIONS.HEIGHT;
    }
    else {
        printNoValue();
        appValues.runSimulation = false;
    }
}

void FileArgument::execute(ApplicationValues& appValues, char* fileNameArg) {
    if (fileNameArg) {
        fileName = fileNameArg;
    }
    else {
        printNoValue();
        appValues.runSimulation = false;
    }
}

void EvenRuleArgument::execute(ApplicationValues& appValues, char* evenRule) {
    if (evenRule) {
        appValues.evenRuleName = evenRule;
    }
    else {
        printNoValue();
        appValues.runSimulation = false;
    }
}

void OddRuleArgument::execute(ApplicationValues& appValues, char* oddRule) {
    if (oddRule) {
        appValues.oddRuleName = oddRule;
    }
    else {
        printNoValue();
        appValues.runSimulation = false;
    }
}