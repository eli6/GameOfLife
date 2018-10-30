/**
 * @file RuleOfExistence.h
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Rules of Existance for cells.
 * @details These rules lies at the heart
of the simulation, and determines the fate of each cell in the world population.
 */


#ifndef RULEOFEXISTENCE_H
#define RULEOFEXISTENCE_H

#include<string>
#include<map>
#include<vector>
#include "../Cell_Culture/Cell.h"
#include "../Support/Globals.h"
using namespace std;


// Data structure for storing population limits. Used by rules to determine what ACTION to make.
struct PopulationLimits {
    int UNDERPOPULATION, // cell dies of loneliness
            OVERPOPULATION, // cell dies of over crowding
            RESURRECTION; // cell lives on / is resurrected
};

// Data structure for storing directional values. Used by rules to determine neighbouring cells.
struct Directions {
    int HORIZONTAL, VERTICAL;
};

// All directions; N, E, S, W, NE, SE, SW, NW
const vector<Directions> ALL_DIRECTIONS{ { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 },{ 1,-1 },{ 1,1 },{ -1,1 },{ -1,-1 } };

// Cardinal directions; N, E, S, W
const vector<Directions> CARDINAL{ { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 } };

// Diagonal directions; NE, SE, SW, NW
const vector<Directions> DIAGONAL{ { 1,-1 },{ 1,1 },{ -1,1 },{ -1,-1 } };


/**
 * @class RuleOfExistence
 * @brief Abstract base class, upon which concrete rules will derive.
 * @details The derivations of RuleOfExistence is what determines the culture of Cell Population. Each rule implements
specific behaviours and so may execute some parts in different orders. In order to accommodate this
requirement RuleOfExistence will utilize a **Template Method** desing pattern, where all derived rules
implements their logic based on the virtual method executeRule().
 @test Test basic constructor behaviour for this class. Test that the virtual public methods and the destructor work for the derived classes.
 */
class RuleOfExistence {
protected:
    // Amounts of alive neighbouring cells, with specified limits
    const PopulationLimits POPULATION_LIMITS;


    // Reference to the population of cells
    map<Point, Cell>& cells;

    // The directions, by which neighbouring cells are identified
    const vector<Directions>& DIRECTIONS;

    string ruleName;


    int countAliveNeighbours(Point currentPoint);

public:
    //made public for testing
    ACTION getAction(int aliveNeighbours, bool isAlive);
    //for testing
    PopulationLimits getPopLimits(){ return POPULATION_LIMITS; }
    const vector<Directions>& getDirections() { return DIRECTIONS; }
    /**
     * @brief Constructor for a rule of existence. Used by derived classes.
     * @details The parameters sets values for population limit values (values for under- /overpopulation etc.),
     * adds a map of cells mapped to their Point positions, sets directions to be used in calculations, as well as the name of the rule of existence in use.
     * @test Test that the constructor produces a correct Rule of Existence object: Test default values of the constructor. Test it with correct and false values. Test that getRuleName returns the rule name.
     *
     * @param limits . Amount of live neighboring cells (private constant).
     * @param cells Map of Cells and their Point locations.
     * @param DIRECTIONS Directions to identify neighboring cells.
     * @param ruleName Name of the rule for cell generation.
     */
    RuleOfExistence(PopulationLimits limits, map<Point, Cell>& cells, const vector<Directions>& DIRECTIONS, string ruleName)
            : POPULATION_LIMITS(limits), cells(cells), DIRECTIONS(DIRECTIONS), ruleName(ruleName) {}

    /**
     * @brief Virtual destructor for the specific rules of existence.
     * @details See derived implementations for more details.
     * @test Check that derived class destructors can be called.
     */
    virtual ~RuleOfExistence() {}

    // Execute rule, in order specific to the concrete rule, by utilizing template method DP
    /**
     * @brief Virtual executeRule() function for derived classes.
     * @details See derived implementations for more details.
     * @test Test derived class implementation of this virtual function.
     */
    virtual void executeRule() = 0;

    /**
     * @brief Returns the name of the Rule of Existence.
     * @details Normal getter function. Will be used for test purposes.
     * @test Test derived class implementation of this virtual function.
     *
     * @return Returns the chosen rule name.
     *
     */
    string getRuleName() { return ruleName; }
};

#endif
