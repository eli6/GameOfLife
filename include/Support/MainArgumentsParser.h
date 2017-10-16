/*
 * Filename    MainArgumentsParser.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#ifndef mainArgumentsParserH
#define mainArgumentsParserH

#include "MainArguments.h"
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

/*
Static functions that parses the starting arguments for the application.
*/
class MainArgumentsParser {
public:
    ApplicationValues& runParser(char* argv[], int length);

private:
    ApplicationValues appValues;

    // Checks if a given option exists
    bool optionExists(char** begin, char** end, const std::string& option);

    // gets the given option value
    char* getOption(char** begin, char** end, const std::string& option);
};

#endif
