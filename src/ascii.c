/*  ascii.c - draw the current maze in ascii
 *
 *  Project name: AmazingProject
 *  Component name: ascii drawing
 *
 *
 *  Primary Author: Jason Feng, Chris Leech, Jordan Hall
 *  Date Created: 5/26/14
 *
 *======================================================================*/
//
// ---------------- Open Issues
//
// ---------------- System includes e.g., <stdio.h>
#include <netinet/in.h>         // for ntohl
#include <stdio.h>              // for printf
#include <unistd.h>             // posix
#include <stdlib.h>             // putc
// ---------------- Local includes  e.g., "file.h"
#include "ascii.h"              // for prototypes
// ---------------- Constant definitions
//
// ---------------- Macro definitions
//
// ---------------- Structures/Types
//
// ---------------- Private variables
//
// ---------------- Private prototypes
//
/*====================================================================*/

/* initMap
 * @param width - width of the maze
 * @param height - height of the maze
 * @param map - pointer to the map 
 *
 * initalizes map for graphics
 */
void initMap(int width, int height, int *map) 
{
    // counters
    int h;
    int w;

    height = translateY(height);
    width = translateX(width);

    for(h = 0; h < height; h++) {
        for(w = 0; w < width; w++) {
            // because this is a 1-d array that *mirrors* a 2d array,
            // we are using the index "y*width + x" to correspond
            // with point x, y
                
            // start by putting spaces all around
            map[h*width + w] = ' ';

            // add in the junctions
            if((h % 2 == 0) && (w % 4 ==0)) {
                map[h*width + w] = '+';
            }

            // add in our walls with "W"
            if(h == 0 || w == 0 || h == height - 1 || w == width - 1) {
                map[h*width + w] = 'W';
            }
        }
    }
}

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
void drawAscii(int width, int height, int *map) 
{
    // counters
    int i;
    int j;
 
    height = translateY(height);
    width = translateX(width);

    printf("%c[2J",27);
    // write out each line of the map! 
    for(i = 0; i < height; i ++) {
        putc('\n', stdout);
        for(j = 0; j < width; j++) {
            putc(map[i*width + j], stdout);
        }
    }
    fflush(stdout);
}

/* translateX - this changes X values in the maze
 * world (for example, values we get back from the server)
 * into X values in the drawn world
 *     
 * @param x - the value we want to translate
 *       
 */
int translateX(int x) 
{
    return 4*x + 1;
}

/* translateY - this changes Y values in the maze
 * world (for example, values we get back from the server)
 * into Y values in the drawn world
 *
 * @param y - the value we want to translate
 *       
 */
int translateY(int y) 
{
    return 2*y + 1;
}

/* getWallX - this function takes in an x value and
 * a direction, and figures out the X value of the
 * wall we just hit
 *     
 * @param x - our current x value
 * @param direction - the direction we tried to go last move
 *        
 *         
 * returns the x value of the wall, pre-translated!
 */
int getWallX(int x, int direction) 
{
    switch(direction) {
        case 0:
            return (4*x + 2) - 2;
        case 1:
            return (4*x + 2);
        case 2:
            return (4*x + 2);
        case 3:
            return (4*x + 2) + 2;
    }
    return 0;
}

/* getWallY - this function takes in an Y value and
 * a direction, and figures out the Y value of the
 * wall we just hit
 *     
 * @param y - our current y value
 * @param direction - the direction we tried to go last move    
 *         
 * returns the y value of the wall, pre-translated!
 */
int getWallY(int y, int direction) 
{
    switch(direction) {
        case 0:
            return (2*y + 1);
        case 1:
            return (2*y + 1) - 1;
        case 2:
            return (2*y + 1) + 1;
        case 3:
            return (2*y + 1);
    }
    return 0;
}
