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
#include "../Cell_Culture/Cell.h"
#include "Globals.h"

using namespace std;

/**
 * @brief Determines starting values for simulation based on contents of specified file.
 * @details The file contains values for WORLD_DIMENSIONS and cell Population and the object uses
 * this to create the corresponding cells.
 * @test So that the member functions work as they should
*/
class FileLoader {
private:

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
     * @param cells A reference to an object of the type map<Point, Cell>
     * @test 1) That the file is opened when a correct filename is used 2) That an exception
     * is thrown when not 3) That the correct world size is read 4) That a population of cells is created.
     *  @bug Uncaught exception when using an incorrect seed file.
     *  @bug Creates a cell population that is 2 cells too wide and 2 cells too high. Cell at point 19,9 is not a rim cell as expected. Change in if clause so that values between 0 and WORLD_DIMENSIONS.HEIGHT/WIDTH - 1 instead of +1 is used.
     *  @bug Row 0 is also read from file although it contains rim cells, since that line isn't explicitly removed or skipped. It also reads a total of 10 rows starting from 0, and not 9 whiuch was expected, since WORLD_DIMENSIONS.HEIGHT+1 instead of -1 is used.
     *  @bug " char cellState = iss.get();" gets the 0 at the start of the row and creates a dead cell, but that is a rimCell and should be skipped
     * */
    void loadPopulationFromFile(map<Point, Cell>& cells);

};

#endif
