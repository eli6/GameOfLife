/*
 * Filename    FileLoader.cpp
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#include "Support/FileLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Cell_Culture/Population.h>

// Loads the given map with cells read from the file thats pointed to by The global variable fileName
void FileLoader::loadPopulationFromFile(map<Point, Cell>& cells) {

    // Open file for reading, if file cant be found throw an exception that
    // prints a error message and throws back to main(closes application)
    ifstream inFile(fileName);
    try {
        if (!inFile.good()) {
            throw ios_base::failure("");
        }
    }
    catch (ios_base::failure &e) {
        cout << "Could not find file. Closing application." << endl;
        throw;
    }


    string worldSize;
    // Read dimensions from file
    getline(inFile, worldSize);

    // Load the read dimensions
    istringstream iss(worldSize);
    iss >> WORLD_DIMENSIONS.WIDTH;
    iss.get();
    iss >> WORLD_DIMENSIONS.HEIGHT;
    iss.clear();


    for (int row = 0; row <= WORLD_DIMENSIONS.HEIGHT + 1; row++) {
        // Dont read a line from file for rim rows
        if (!(row == 0 || row == WORLD_DIMENSIONS.HEIGHT + 1)) {
            string populationRow;
            getline(inFile, populationRow);
            iss.str(populationRow);
        }

        for (int column = 0; column <= WORLD_DIMENSIONS.WIDTH + 1; column++) {
            // if cell is a rim cell
            if (column == 0 || row == 0
                || column == WORLD_DIMENSIONS.WIDTH + 1
                || row == WORLD_DIMENSIONS.HEIGHT + 1) {

                cells[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
            }
            else { // If cell is an ordinary cell
                char cellState = iss.get();

                if (cellState == '1') {
                    cells[Point{column, row}] = Cell(false, GIVE_CELL_LIFE); // create a ordinary living cell
                }
                else if (cellState == '0') {
                    cells[Point{column, row}] = Cell(false, IGNORE_CELL); // else create a ordinary dead cell
                }
            }
            iss.clear();
        }
    }
    inFile.close();
}