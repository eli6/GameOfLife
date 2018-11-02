cmake_minimum_required(VERSION 3.2)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

include_directories($ENV{TOOLS_INCLUDE} ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/test)

# Add terminal sub directory
add_subdirectory(terminal)

# Om Debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Debug mode
    message("Debug mode")
    add_definitions(-DDEBUG)
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Release mode.
    message("Release mode")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

set(SRC_LIST
        include/Cell_Culture/Cell.h include/Support/FileLoader.h include/GameOfLife.h include/Support/Globals.h include/Support/MainArgumentsParser.h include/Cell_Culture/Population.h include/GoL_Rules/RuleFactory.h include/GoL_Rules/RuleOfExistence.h include/ScreenPrinter.h src/Cell_Culture/Cell.cpp src/Support/FileLoader.cpp src/GameOfLife.cpp src/Support/Globals.cpp src/Cell_Culture/Population.cpp src/GoL_Rules/RuleFactory.cpp src/GoL_Rules/RuleOfExistence.cpp src/ScreenPrinter.cpp include/GoL_Rules/RuleOfExistence_Conway.h src/GoL_Rules/RuleOfExistence_Conway.cpp include/GoL_Rules/RuleOfExistence_VonNeumann.h src/GoL_Rules/RulesOfExistence_VonNeumann.cpp include/GoL_Rules/RuleOfExistence_Erik.h src/GoL_Rules/RuleOfExistence_Erik.cpp include/Support/SupportStructures.h src/Support/MainArgumentsParser.cpp include/Support/MainArguments.h src/Support/MainArguments.cpp)

set(TEST_LIST
        test/test-main.cpp test/test-cell.cpp test/test-mainargumentsparser.cpp test/test-mainargumentsparser.cpp test/test-ruleOfExistence_conway.cpp test/test_fileloader.cpp test/test-ruleOfExistence_VonNeumann.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${SRC_LIST})

add_executable(${PROJECT_NAME}-test ${SRC_LIST} ${TEST_LIST})

target_link_libraries(${PROJECT_NAME} Terminal)

target_link_libraries(${PROJECT_NAME}-test Terminal)
