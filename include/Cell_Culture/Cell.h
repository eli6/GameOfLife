/*
 * Filename    Cell.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#ifndef cellH
#define cellH

#include "../../terminal/terminal.h"

// Data structure holding colors to visualize the state of cells.
struct StateColors {
    COLOR LIVING, // Representing living cell
            DEAD, // Representing dead cell
            OLD,  // Representing old cell
            ELDER;// Representing very old cell
}	/* Initiate default values. */
const STATE_COLORS = { COLOR::WHITE, COLOR::BLACK, COLOR::CYAN, COLOR::MAGENTA };

// Cell action. Determined by rule, and sent to cell for future change.
enum ACTION { KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING };


/*
Cells represents a certain combination of row and column of the simulated world.

Cells may be of two types; rim cells, those representing the outer limits of the world,
or non-rim cells. The first cell type are immutable, exempt from the game's rules, and
thus their values may not be changed. The latter type, however, may be changed and edited
in ways specified by the rules.
*/
class Cell {

private:
    struct CellDetails {	// encapsulate cell details
        int age;
        COLOR color;
        bool rimCell;
        char value;
    } details;

    struct NextUpdate {		// encapsulate changes to next state
        ACTION nextGenerationAction;
        COLOR nextColor;
        char nextValue;
        bool willBeAlive;	// some rules may need to know beforehand whether the cell will be alive
    } nextUpdate;


    void incrementAge() { details.age++; }

    void killCell() { details.age = 0; }

    // Sets the character value of the cell, which will be printed to screen.
    void setCellValue(char value) { details.value = value; }

    void setColor(COLOR color) { this->details.color = color; }

public:

    Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    bool isAlive();

    void setNextGenerationAction(ACTION action);

    void updateState();

    int getAge() { return details.age; }

    COLOR getColor() { return details.color; }

    // Determines whether the cell is a rim cell, and thus should be immutable
    bool isRimCell() { return details.rimCell; }

    // Sets the color the cell will have after its next update.
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }

    char getCellValue() { return details.value; }

    // Sets the next character value of the cell, which will be printed to screen.
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    // Sets whether the cell is alive/dead next generation.
    void setIsAliveNext(bool isAliveNext) { nextUpdate.willBeAlive = isAliveNext; }

    // Will the cell be alive next generation?
    bool isAliveNext() { return nextUpdate.willBeAlive; }

    // Gets the cells next action.
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }

};

#endif
