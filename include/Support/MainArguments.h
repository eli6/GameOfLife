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
     * @brief Informs the user that no value was provided for the argument
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
     * @test It should return the correct value.
     */
    const string& getValue() { return argValue; }
};

/**
 * @class HelpArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-h'.
 * @test The constructor and member function should function properly
 */
class HelpArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @test The correct letter should be set as argValue
     */
    HelpArgument() : BaseArgument("-h") {}

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
 * @class GenerationArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-g'.
 * @test The constructor and member function should function properly
 */
class GenerationsArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @test The correct letter should be set as argValue
     */
    GenerationsArgument() : BaseArgument("-g") {}

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
 * @class WorldSizeArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-s'.
 * @test The constructor and member function should function properly
 */
class WorldsizeArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @test The correct letter should be set as argValue
     */
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
 * @class FileArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-f'.
 * @test The constructor and member function should function properly
 */
class FileArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @test The correct letter should be set as argValue
     */
    FileArgument() : BaseArgument("-f") {}
    ~FileArgument() {}

    /**
     * @brief Sets the fileName
     * @param appValues Reference to an ApplicationValues object
     * @param fileNameArg A pointer to char
     */
    void execute(ApplicationValues& appValues, char* fileNameArg);
};

/**
 * @class EvenRuleArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-er'.
 * @test The constructor and member function should function properly
 */
class EvenRuleArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @test The correct letter should be set as argValue
     */
    EvenRuleArgument() : BaseArgument("-er") {}
    ~EvenRuleArgument() {}

    /**
     * @brief Sets the appValues member evenRule
     * @param appValues A reference to an ApplicatoinValues object
     * @param oddRule A pointer to char
     */
    void execute(ApplicationValues& appValues, char* evenRule);
};

/**
 * @class OddRuleArgument
 * @brief Derived class from BaseArgument
 * @details sets the member argValue to '-or'.
 * @test The constructor and member function should function properly
 */
class OddRuleArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @test The correct letter should be set as argValue
     */
    OddRuleArgument() : BaseArgument("-or") {}
    ~OddRuleArgument() {}

    /**
     * @brief Sets the appValues member oddRuleName
     * @param appValues A reference to an ApplicatoinValues object
     * @param oddRule A pointer to char
     */
    void execute(ApplicationValues& appValues, char* oddRule);
};

#endif //GAMEOFLIFE_MAINARGUMENTS_H
