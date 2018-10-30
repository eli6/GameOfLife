/**
 * @file
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the struct ApplicationValues, the base class for a number of
 * derived classes called BaseClass, and the derived classes HelpArgument, GenerationsArgument
 * WorldSizeArgument, FileArgument, EvenRuleArgument, OddRuleArgument.
*/

#ifndef GAMEOFLIFE_MAINARGUMENTS_H
#define GAMEOFLIFE_MAINARGUMENTS_H

#include "Globals.h"
#include "ScreenPrinter.h"
#include <sstream>
#include <string>

using namespace std;

/**
 * @struct ApplicationValues
 * @brief Contains arguments for the simulation.
 * @details It contains one boolean value that is set to 'true', two strings to represent
 * odd and even rule names, and an integer to represent the number of generations, and it's
 * set to 100.
 */
struct ApplicationValues {
    bool runSimulation = true;
    string evenRuleName, oddRuleName;
    int maxGenerations = 100;

};

/**
 * @class BaseArgument
 * @brief Base class for argument classes
 * @details The classes are used for giving arguments
 * @test The constructor and member functions
 */
class BaseArgument {
protected:
    const string argValue;

    /**
     * @brief nform the user that no value was provided for the argument
     */
    void printNoValue();

public:
    /**
     * @brief Constructor for BaseArgument
     * @details Takes a string value and sets the member argValue with it. It
     * receives different string values from different derived classes.
     * @param argValue A string value
     * @test The constructor should set the string value correcty
     */
    BaseArgument(string argValue) : argValue(argValue) {}

    /**
     * @brief Virtual Destructor
     */
    virtual ~BaseArgument() {}

    /**
     * @brief A virtual function used in the derived classes to execute the arguments
     * @param appValues A reference to an AppliactionValues instance
     * @param value A pointer to a char set to 'nullptr'
     */
    virtual void execute(ApplicationValues& appValues, char* value = nullptr) = 0;

    /**
     * @brief Getter for the member 'argValue'
     * @return A reference to the string value 'argValue'
     */
    const string& getValue() { return argValue; }
};

/**
 * @class HelpArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-h'.
 */
class HelpArgument : public BaseArgument {
public:
    /**
     * @brief The constructor sets the member in the base class argValue to '-h'.
     * @test So that the value is set correctly to '-h'.
     */
    HelpArgument() : BaseArgument("-h") {}

    /**
     * @brief Destructor
     * @Test So that it functions correctly
     */
    ~HelpArgument() {}

    /**
     * @brief Prints the help screen from ScreenPrinter
     * @param appValues An ApplicationValues object reference
     * @param value A pointer to a char
     * @bug The parameter 'value' is never used
     */
    void execute(ApplicationValues& appValues, char* value);
};

/**
 * @brief Number of generations to simulate
 * TODO test
 */
class GenerationsArgument : public BaseArgument {
public:
    /**
     * @brief
     */
    GenerationsArgument() : BaseArgument("-g") {}

    /**
     * @brief
     */
    ~GenerationsArgument() {}

    /**
     * @brief Sets the number of generations
     * @details Sets the 'maxGenerations' member in ApplicationValues to what the
     * parameter 'generations' points to
     * @param appValues A reference to an ApplicationValues object
     * @param generations A pointer to a char
     */
    void execute(ApplicationValues& appValues, char* generations);
};

/**
 * @class WorldsizeArgument
 * @brief Custom population size
 */
class WorldsizeArgument : public BaseArgument {
public:
    WorldsizeArgument() : BaseArgument("-s") {}
    ~WorldsizeArgument() {}

    /**
     * @brief Sets the world dimensions using an istringstream object
     * @param appValues A reference to an ApplicationValues object
     * @param dimensions A pointer to a char
     */
    void execute(ApplicationValues& appValues, char* dimensions);
};

/**
 * @brief Initiate population from file
 */
class FileArgument : public BaseArgument {
public:
    FileArgument() : BaseArgument("-f") {}
    ~FileArgument() {}

    /**
     * @brief
     * @param appValues
     * @param fileNameArg
     */
    void execute(ApplicationValues& appValues, char* fileNameArg);
};

/**
 * @brief Rule used for even generations *
 */
class EvenRuleArgument : public BaseArgument {
public:
    EvenRuleArgument() : BaseArgument("-er") {}
    ~EvenRuleArgument() {}

    void execute(ApplicationValues& appValues, char* evenRule);
};

/**
 * @brief Rule used for odd generations
 */
class OddRuleArgument : public BaseArgument {
public:
    OddRuleArgument() : BaseArgument("-or") {}
    ~OddRuleArgument() {}

    void execute(ApplicationValues& appValues, char* oddRule);
};

#endif //GAMEOFLIFE_MAINARGUMENTS_H
