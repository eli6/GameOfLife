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
/**
 * @struct StateColors
 * @brief Data structure to visualize the state of cells with colors.
 * @details This data structure holds colors to visualize the state of cells where
 * the default colors are white, black, cyan and magenta. It has four members of
 * they type STATE_COLORS, representing cells in the following states:
 * living (LVING), dead (DEAD), old (OLD) and very old (ELDER).
 */
struct StateColors {
    COLOR LIVING, // Representing living cell
            DEAD, // Representing dead cell
            OLD,  // Representing old cell
            ELDER;// Representing very old cell
}	/* Initiate default values. */
const STATE_COLORS = { COLOR::WHITE, COLOR::BLACK, COLOR::CYAN, COLOR::MAGENTA };

/**
 * @enum ACTION
 * @brief Cell action
 * @details The actions are determined by rule and are sent to cell for future change
 */
enum ACTION { KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING };


/**
 * @class Cell
 * @brief Cells represents a certain combination of row and column of the simulated world.
 * @details Cells may be of two types; rim cells, those representing the outer limits of
 * the world, ro non-rim cells. The first cell type are immutable, exempt from the game's
 * rules, and thus their values may not be changed. The latter type, however, may be changed
 * and edited in ways specified by the rules.
 */
class Cell {

private:
    /**
     * @struct CellDetails
     * @brief the details of the cell in the current state
     * @details when this state changes the details are updated with the corresponding
     * values of NextUpdate. The member 'value' contains the character that is printed
     * on the screen.
     */
    struct CellDetails {	// encapsulate cell details
        int age;
        COLOR color;
        bool rimCell;
        char value;
    } details;

    /**
     * @struct NextUpdate
     * @brief Contains the values for the next update of the cell state
     * @details
     */
    struct NextUpdate {		// encapsulate changes to next state
        ACTION nextGenerationAction;
        COLOR nextColor;
        char nextValue;
        bool willBeAlive;	// some rules may need to know beforehand whether the cell will be alive
    } nextUpdate;

    /**
     * incrementAge()
     * @brief Increments age
     * @details The function accesses the age member through the struct 'details'
     * and increments it by 1
     */
    void incrementAge() { details.age++; }

    /**
     * killCell()
     * @brief Kills cell
     * @details This function kills the cell by setting its age equal to 0
     */
    void killCell() { details.age = 0; }

    /**
     * setCellValue(char value)
     * @brief Sets the character value of the cell
     * @details The character value is what is printed to the screen
     * @param value a character value
     */
    void setCellValue(char value) { details.value = value; }

    /**
     * setColor(COLOR color)
     * @brief Sets the color of the cell
     * @details The color is the visual representation of the state of the cell
     * @param color a COLOR vallue
     */
    void setColor(COLOR color) { this->details.color = color; }

public:

    /**
     * @brief Constructor for the class Cell
     * @details
     * @param isRimCell a boolean value set to 'false'
     * @param action an ACTION value set to 'DO_NOTHING'
     */
    Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    /**
     * @brief Checks if the cell is alive
     * @details If the cell is alive the return value is 'true'
     * @return bool
     */
    bool isAlive();

    /**
     * @brief Sets the state of the next generation
     * @details The state is based on the current state of the cell and the state of
     * its neighbours
     * @param action an ACTION value
     */
    void setNextGenerationAction(ACTION action);

    /**
     *
     */
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
