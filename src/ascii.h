/*  ascii.h Implements simple ascii drawing for the maze
 *
 *  Project name: AmazingProject
 *  Component name: ASCII
 *
 *
 *  Primary Author: Jason Feng, Chris Leech, Jordan Hall
 *  Date Created: 5/26/14
 *
 *======================================================================*/
#ifndef ASCII_H
#define ASCII_H
//
// ---------------- Open Issues
//
// ---------------- System includes e.g., <stdio.h>
#include <netinet/in.h>         // for ntohl
#include <stdio.h>              // for printf
#include <unistd.h>
// ---------------- Local includes  e.g., "file.h"

// ---------------- Constant definitions
//
// ---------------- Macro definitions
//
// ---------------- Structures/Types
//
// ---------------- Private variables
//
// ---------------- Private prototypes

/* initMap
 * @param width - width of the maze
 * @param height - height of the maze
 * @param map - pointer to the map 
 *
 * initalizes map for graphics
 */
void initMap(int width, int height, int *map);
 
/* drawAscii - draws out the current position of the players in the maze
 *
 * @param turn - the turn message from the server
 * @param width - the width of the maze
 * @param height - the height of the maze
 * @param nAvs - how many avatars are in the maze
 *
 * This will use newlines to move output up the terminal,
 * then draw an ascii maze, with avatars in the maze represented by 
 * their unique avatar id's
 *
 */
void drawAscii(int width, int height, int *map);

/*
 * translateX - this changes X values in the maze
 * world (for example, values we get back from the server)
 * into X values in the drawn world
 *     
 * @x - the value we want to translate
 *       
 */
int translateX(int x);

/*
 * translateY - this changes Y values in the maze
 * world (for example, values we get back from the server)
 * into Y values in the drawn world
 *
 * @y - the value we want to translate
 *       
 */
int translateY(int y);

/*
 * getWallX - this function takes in an x value and
 * a direction, and figures out the X value of the
 * wall we just hit
 *     
 * @x - our current x value
 * @direction - the direction we tried to go last move
 *        
 *         
 * returns the x value of the wall, pre-translated!
 */
int getWallX(int x, int direction);

/*
 * getWallY - this function takes in an Y value and
 * a direction, and figures out the Y value of the
 * wall we just hit
 *     
 * @y - our current y value
 * @direction - the direction we tried to go last move
 *        
 *         
 * returns the y value of the wall, pre-translated!
 */
int getWallY(int y, int direction);
/*====================================================================*/

#endif // ASCII_H
