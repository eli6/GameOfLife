/*
 * Filename    SupportStructures.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
 *
 * Various supportive structures to be used throughout the application!
*/

#ifndef GAMEOFLIFE_SUPPORTSTRUCTURES_H
#define GAMEOFLIFE_SUPPORTSTRUCTURES_H

/*
Constitues a single Point in the simulated world.

The Point structure handles x and y (column/row) coordinates in the world of Game of life, and is used
to map Cell objects to their positions.
*/
struct Point {
    int x, y;

    // Overloading operator < for comparing Point objects
    bool operator < (const Point& other) const {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }

};

/*
Data structure holding information about world dimensions in pixels.
*/
struct Dimensions {
    int WIDTH, HEIGHT;
};


#endif //GAMEOFLIFE_SUPPORTSTRUCTURES_H
