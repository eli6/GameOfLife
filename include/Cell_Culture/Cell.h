/**
 * @file       Cell.h.
 * @author     Erik Ström.
 * @date       October 2017.
 * @version    0.1.
 * @brief      Contains the Cell class, the enum STATE_COLORS and the struct StateColors.
*/

#ifndef cellH
#define cellH

#include "../../terminal/terminal.h"

/**
 * @struct StateColors
 * @brief Data structure to visualize the state of cells with colors.
 * @details The default colors are white, black, cyan and magenta. It has
 * four members of they type STATE_COLORS, representing cells in the
 * following states: living (LIVING), dead (DEAD), old (OLD) and very old (ELDER).
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
 * @brief Cells represent a certain combination of rows and columns of the simulated world.
 * @details Cells may be of two types:
 * 1. Rim cells: those representing the outer limits of the world. They are immutable,
 * exempt from the rules of the game, thus their values may not be changed.
 * 2. Non-rim cells: May be changed and edited in ways specified by the rules.
 * @test Test constructor and member functions
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
     *
     * @test Test so that the age increments as it should
     */
    void incrementAge() { details.age++; }

    /**
     * killCell()
     * @brief Kills cell
     * @details This function kills the cell by setting its age equal to 0
     *
     * @test Test so that the age equals 0
     */
    void killCell() { details.age = 0; }

    /**
     * setCellValue(char value)
     * @brief Sets the character value of the cell
     * @details The character value is what is printed to the screen
     * @param value a character value
     *
     * @test Test so that the value that is set actually applies to the object
     */
    void setCellValue(char value) { details.value = value; }

    /**
     * setColor(COLOR color)
     * @brief Sets the color of the cell
     * @details The color is the visual representation of the state of the cell
     * @param color a COLOR vallue
     *
     * @test Test so that the color is correct
     */
    void setColor(COLOR color) { this->details.color = color; }

public:

    /**
     * @brief Constructor for the class Cell
     * @details Sets the values for both structs in the Cell object. The implementation sets default values of CellDetails to age = 0, color = dead (unless action is GIVE_CELL_LIFE), and screen character = #.
     * @param isRimCell a boolean value set to 'false'
     * @param action an ACTION value set to 'DO_NOTHING'
     *
     * @test Test so that the object is created with the correct values
     */
    Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    /**
     * @brief Checks if the cell is alive
     * @details If the cell is alive the return value is 'true'
     * @return bool
     *
     * @test Test so that the correct boolean value is returned
     */
    bool isAlive();

    /**
     * @brief Sets the state of the next generation
     * @details The state is based on the current state of the cell and the state of
     * its neighbours. If the cell is a rim cell, or its 'action' memeber is set to
     * GIVE_CELL_LIFE while isAlive() returns 'true', then nothing happens. Otherwise,
     * 'action' equals nextGenerationAction() run on nextUpdate.
     * @param action an ACTION value
     *
     * @test Test so that the two if-statements work, as well as setting the 'action' member
     * correctly
     */
    void setNextGenerationAction(ACTION action);

    /**
     * @brief Updates the state of the Cell
     * @details Based on the NextUpdate part, it updates the state of the Cell
     * by checking the ACTION data member in NextUpdate and update the current state
     * using that information
     *
     * @test Test so all three cases in the switch-statement work, as well as the
     * two subsequent if-statements
     */
    void updateState();

    /**
     * @brief Getter for the current age of the Cell
     * @return int The current age of the Cell
     *
     * @test Test so that the correct age is returned
     */
    int getAge() { return details.age; }

    /**
     * @brief Getter for the data member 'color'
     * @return COLOR The current COLOR value of the Cell
     *
     * @test Test so that the correct color is returned
     */
    COLOR getColor() { return details.color; }

    /**
     * @brief Determines if the Cell is a rim cell
     * @details If it is a rim cell it should be immutable
     * @return bool Returns 'true' if it is indeed a rim cell
     *
     * @test Test so that the correct boolean value is returned for both types
     */
    bool isRimCell() { return details.rimCell; }

    /**
     * @brief Setter for 'nextColor'
     * @details Sets the color the cell will have after its next update.
     * @param nextColor a COLOR data type to represent the next state of the Cell
     *
     * @test Test so that it updates the object to the correct color
     */
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }

    /**
     * @brief Getter for the 'value' data member of the Cell
     * @return char a 'char' value which is the character that represents the Cell on screen
     *
     * @test Test so that the correct value is returned
     */
    char getCellValue() { return details.value; }

    /**
     * @brief Setter for 'nextValue'
     * @details This is the value (cell character printed on screen) the member 'value' will have after the Cell's next update
     * @param value The character that is printed to the screen
     *
     * @test Test so that the member is updated correctly
     */
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    /**
     * @brief Sets whether the cell is alive or dead next generation.
     * @param isAliveNext a boolean value that represents if the Cell will be alive
     * the next generation
     *
     * @test Test so that the member 'willBeAlive' is updated correctly
     */
    void setIsAliveNext(bool isAliveNext) { nextUpdate.willBeAlive = isAliveNext; }

    /**
     * @brief Returns 'true' if the cell will be alive next generation
     * @return bool
     *
     * @test Test so that the return value is correct
     */
    bool isAliveNext() { return nextUpdate.willBeAlive; }

    /**
     * @brief Getter for the 'action' member of the next generation
     * @return ACTION
     *
     * @test Test so that the return value is correct 
     */
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }

};

#endif
