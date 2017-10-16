/*
 * Filename    MainArgumentsParser.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "ScreenPrinter.h"
#include "Support/MainArgumentsParser.h"

// Arguments provided by the user
ApplicationValues &MainArgumentsParser::runParser(char *argv[], int length) {

    vector<BaseArgument *> arguments = {new HelpArgument, new GenerationsArgument, new WorldsizeArgument,
                                        new FileArgument, new EvenRuleArgument, new OddRuleArgument};

    for (auto arg : arguments) {
        const string& argValue = arg->getValue();
        char* value;
        if (optionExists(argv, argv + length, argValue)) {
            if(argValue != "-h")
                value = getOption(argv, argv + length, argValue);
            arg->execute(appValues, value);

        }
    }

    // if no even rule name has been set, default to conway
    if (appValues.evenRuleName.empty()) {
        appValues.evenRuleName = "conway";
    }
    // if no odd rule name has been set, default to same as even rule name
    if (appValues.oddRuleName.empty()) {
        appValues.oddRuleName = appValues.evenRuleName;
    }

    for(auto arg : arguments) {
        delete arg;
    }

    return appValues;
}

// Checks if a given option exists
bool MainArgumentsParser::optionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

// gets the given option value
char *MainArgumentsParser::getOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);

    if (itr != end && ++itr != end) {
        return *itr;
    } else {
        return 0;
    }
}