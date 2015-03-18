/*  movealgorithm.h Implementation for left hand rule for maze traversal  

    Project name: AmazingProject
    Component name: move algorithm

    This file contains ...
    
    Primary Author: Jason Feng, Chris Leech, Jordan Hall
    Date Created: 4/27/14

======================================================================*/
// do not remove any of these sections, even if they are empty
#ifndef MOVEALGORITH_H
#define MOVEALGORITH_H
// ---------------- Prerequisites e.g., Requires "math.h"
#include "amazing.h"                        // Amazing definitions for messages
// ---------------- Constants

// ---------------- Structures/Types

// ---------------- Public Variables

// ---------------- Prototypes/Macros
    
/* getDirectionChange
 * @param prev - Previous position
 * @param curr - Current position
 *
 * Return - Returns the direction the avatar is facing
 *
 * Compares the previous and current position to determine which direction the
 * avatar is now facing. 
 */
int getDirectionChange(XYPos *prev, XYPos *curr);

/* getNextMoveL
 * @param direction - the direction the avatar is facing
 * @param moves_attempted - the number of moves we've already tried
 *
 * Return - The direction the avatar should move. 
 *
 * This algorithm will always move the avatar left if it can. Depending on what
 * direction the avatar is facing, "left" will be in a different direction 
 * according to the defined North, South, East, West in amazing.h. We use the
 * current direction and the number of unsuccessful moves we've tried to 
 * determine the direction we should move in. We will first try left, then
 * straight, then right, and finally backwards if none of those three work. This
 * algorithm is used by the slaves. 
 * Key: west = 0, north = 1, south = 2, east = 3
 *
 */
int getNextMoveL(int direction, int moves_attempted);

/* getNextMoveR
 * @param direction - the direction the avatar is facing
 * @param moves_attempted - the number of moves we've already tried
 *
 * Return - The direction the avatar should move. 
 *
 * This algorithm will always move the avatar right if it can. Depending on what
 * direction the avatar is facing, "right" will be in a different direction 
 * according to the defined North, South, East, West in amazing.h. We use the
 * current direction and the number of unsuccessful moves we've tried to 
 * determine the direction we should move in. We will first try right, then
 * straight, then left, and finally backwards if none of those three work. This
 * algorithm is used by the master. Once a master finds a slave, then the slave
 * will also use the right hand algorithm.   
 * algorithm is used by the slaves. 
 * Key: west = 0, north = 1, south = 2, east = 3
 *
 */
int getNextMoveR(int direction, int moves_attempted);  

#endif // MOVEALGORITH_H
