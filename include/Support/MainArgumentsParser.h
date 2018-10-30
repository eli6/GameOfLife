/**
 * @file
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the class MainArgumentsParser
*/

#ifndef mainArgumentsParserH
#define mainArgumentsParserH

#include "MainArguments.h"
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * @class MainArgumentsParser
 * @brief Static functions that parses the starting arguments for the application.
 * @test The member functions
*/
class MainArgumentsParser {
public:
    /**
     * @brief Parses the arguments given at the start of execution
     * @details The main function of the class. Is used before the simulation starts. It takes the
     * arguments given at the start of execution, creates a vector with pointers to a new instance
     * of each derived argument class, runs a number of actions that modify the member appValues
     * based on these arguments, and then returns a reference to it.
     * @param argv A pointer to a C-string
     * @param length An integer
     * @return A reference to an ApplicationValues object
     * TODO how test?
     */
    ApplicationValues& runParser(char* argv[], int length);

private:
    ApplicationValues appValues;

    /**
     * @brief Checks if a given option exists
     * @details Uses std::find() to find if option exists and returns 'true' if it does
     * @param begin A pointer to a pointer to char
     * @param end A pointer to a pointer to char
     * @param option A const reference to a string
     * @return A boolean value
     */
    bool optionExists(char** begin, char** end, const std::string& option);

    /**
     * @brief Gets the given option value
     * @details Iterates over a string and returns the iterator itself if the value was found,
     * otherwise it returns a nullptr.
     * @param begin A pointer to a pointer to char for where to start the iteration
     * @param end A pointer to a pointer to char for where to end the iteration
     * @param option A reference to a string on which the iteration takes place
     * @return A pointer to char that is the iterator if the value was found
     * @test Check so a correct value is returned from different combinations of arguments
     */
    char* getOption(char** begin, char** end, const std::string& option);
};

#endif
