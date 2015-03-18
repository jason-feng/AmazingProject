/*  movealgorithm.c - Implementation for left hand rule for maze traversal  

    Project name: AmazingProject
    Component name: move algorithm

    This file contains ...
    
    Primary Author: Jason Feng, Chris Leech, Jordan Hall
    Date Created: 5/26/14

    Special considerations:  
        (e.g., special compilation options, platform limitations, etc.) 
    
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
// ---------------- Local includes  e.g., "file.h"
#include "amazing.h"                        // Amazing definitions for messages
// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

/* getDirectionChange
 * @param prev - Previous position
 * @param curr - Current position
 *
 * Return - Returns the direction the avatar is facing
 *
 * Compares the previous and current position to determine which direction the
 * avatar is now facing. 
 */
int getDirectionChange(XYPos *prev, XYPos *curr) 
{
    if(prev->x == curr->x) { // moving N/S
        if(prev->y > curr->y) { // note - this is counter intuitive, because y is inverted
            return 1; // north
        }
        return 2; // south
    }
    if(prev->x > curr->x) { 
        return 0; // west
    }
    return 3; // east
}

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
 * algorithm is used by the slaves. 
 * Key: west = 0, north = 1, south = 2, east = 3
 *
 */
int getNextMoveL(int direction, int moves_attempted) 
{
    switch (direction) {
        case 0:
            switch(moves_attempted) {
                case 0:
                    return 2;
                case 1:
                    return 0;
                case 2:
                    return 1;
                case 3:
                    return 3;
            }
        case 1:
            switch(moves_attempted) {
                case 0:
                    return 0;
                case 1:
                    return 1;
                case 2:
                    return 3;
                case 3:
                    return 2;
            }
        case 2:
            switch(moves_attempted) {
                case 0:
                    return 3;
                case 1:
                    return 2;
                case 2:
                    return 0;
                case 3:
                    return 1;
            }
        case 3:
            switch(moves_attempted) {
                case 0:
                    return 1;
                case 1:
                    return 3;
                case 2:
                    return 2;
                case 3:
                    return 0;
            }
    }
    return 0;
}

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
int getNextMoveR(int direction, int moves_attempted) 
{
    switch (direction) {
        case 0:
            switch(moves_attempted) {
                case 0:
                    return 1;
                case 1:
                    return 0;
                case 2:
                    return 2;
                case 3:
                    return 3;
            }
       case 1:
            switch(moves_attempted) {
                case 0:
                    return 3;
                case 1:
                    return 1;
                case 2:
                    return 0;
                case 3:
                    return 2;
            }
       case 2:
            switch(moves_attempted) {
                case 0:
                    return 0;
                case 1:
                    return 2;
                case 2:
                    return 3;
                case 3:
                    return 1;
            }
       case 3:
            switch(moves_attempted) {
                case 0:
                    return 2;
                case 1:
                    return 3;
                case 2:
                    return 1;
                case 3:
                    return 0;
            }
    }
    return 0;
}
