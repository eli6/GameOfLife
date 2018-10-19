/**
 * @file SupportStructures.h
 * @author Erik Ström
 * @date October 2017
 * @version 0.1
 * @brief Various supportive structures to be used throughout the application!
 * @details Contains point coordinate structure and world dimensions.
 */

#ifndef GAMEOFLIFE_SUPPORTSTRUCTURES_H
#define GAMEOFLIFE_SUPPORTSTRUCTURES_H

/***
@brief Constitues a single Point in the simulated world.

@details The Point structure handles x and y (column/row) coordinates in the world of Game of life, and is used
to map Cell objects to their positions.
***/
struct Point {
    int x, y;

    // Overloading operator < for comparing Point objects
    bool operator < (const Point& other) const {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }

};

/***
@brief Data structure holding information about world dimensions in pixels.
@details Available dimensions are WITH and HEIGHT
***/
struct Dimensions {
    int WIDTH, HEIGHT;
};


#endif //GAMEOFLIFE_SUPPORTSTRUCTURES_H
