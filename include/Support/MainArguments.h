/*
 * Filename    MainArguments.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#ifndef GAMEOFLIFE_MAINARGUMENTS_H
#define GAMEOFLIFE_MAINARGUMENTS_H

#include "Globals.h"
#include "ScreenPrinter.h"
#include <sstream>
#include <string>

using namespace std;

struct ApplicationValues {
    bool runSimulation = true;
    string evenRuleName, oddRuleName;
    int maxGenerations = 100;

};

class BaseArgument {
protected:
    const string argValue;

    // inform the user that no value was provided for the argument
    void printNoValue();

public:
    BaseArgument(string argValue) : argValue(argValue) {}
    virtual ~BaseArgument() {}
    virtual void execute(ApplicationValues& appValues, char* value = nullptr) = 0;

    const string& getValue() { return argValue; }
};

// Help screen
class HelpArgument : public BaseArgument {
public:
    HelpArgument() : BaseArgument("-h") {}
    ~HelpArgument() {}

    void execute(ApplicationValues& appValues, char* value);
};

// Amount of generations to simulate
class GenerationsArgument : public BaseArgument {
public:
    GenerationsArgument() : BaseArgument("-g") {}
    ~GenerationsArgument() {}

    void execute(ApplicationValues& appValues, char* generations);
};

// Custom population size
class WorldsizeArgument : public BaseArgument {
public:
    WorldsizeArgument() : BaseArgument("-s") {}
    ~WorldsizeArgument() {}

    void execute(ApplicationValues& appValues, char* dimensions);
};

// Initiate population from file
class FileArgument : public BaseArgument {
public:
    FileArgument() : BaseArgument("-f") {}
    ~FileArgument() {}

    void execute(ApplicationValues& appValues, char* fileNameArg);
};

// Rule used for even generations
class EvenRuleArgument : public BaseArgument {
public:
    EvenRuleArgument() : BaseArgument("-er") {}
    ~EvenRuleArgument() {}

    void execute(ApplicationValues& appValues, char* evenRule);
};

// Rule used for odd generations
class OddRuleArgument : public BaseArgument {
public:
    OddRuleArgument() : BaseArgument("-or") {}
    ~OddRuleArgument() {}

    void execute(ApplicationValues& appValues, char* oddRule);
};

#endif //GAMEOFLIFE_MAINARGUMENTS_H
