/**
 * @file
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Contains the class FileLoader
*/

#ifndef FileLoaderH
#define FileLoaderH

#include <map>
#include "Cell_Culture/Cell.h"
#include "Globals.h"

using namespace std;

/**
 * @brief Determines starting values for simulation based on contents of specified file.
 * @details The file contains values for WORLD_DIMENSIONS and cell Population and the object uses
 * this to create the corresponding cells.
 * @test So that the member functions work as they should
*/
class FileLoader {

public:
    /**
     * @brief Constructor for FileLoader
     */
    FileLoader() {}

    /**
     * @brief Loads a population from file
     * @details Uses the string variable fileName declared in Globals.h to try to open a file
     * with a try-catch block. An ios_base::failure exception is thrown if unsuccessful. If not,
     * the world dimensions are read from file and used to create a population of cells.
     * @test 1) That the file is opened when a correct filename is used 2) That an exception
     * is thrown when not 3) That the correct world size is read 4) That a population of cells is created.
     */
    void loadPopulationFromFile(map<Point, Cell>& cells);

};

#endif
