/*  avatar.h  Header file for avatar.c

    Project name: AmazingProject
    Component name: avatar
    
    Primary Author: Jason Feng, Chris Leech, Jordan Hall
    Date Created: 4/27/14  

    Input: [Avatar ID] [Number of Avatars] [Difficulty Level] [IP Address]
        [Mazeport] [Filename for log file]

    Command line options: None

    Output: 

    Error Conditions:

    Special considerations:  
        (e.g., special compilation options, platform limitations, etc.) 
    
======================================================================*/
#ifndef AVATAR_H
#define AVATAR_H
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <sys/socket.h>                     // server communication
#include <stdlib.h>                         // atoi
#include <stdio.h>                          // printf
#include <netinet/in.h>                     // Control message protocol
#include <unistd.h>                         // Posix constants
#include <sys/types.h>                      // tread
#include <netdb.h>                          // hostent
#include <arpa/inet.h>                      // htonl, ntohl
#include <string.h>                         // strcmp
#include <errno.h>                          // errors
#include <time.h>                           // clock
// ---------------- Local includes  e.g., "file.h"
#include "amazing.h"                        // Amazing definitions for messages
#include "movealgorithm.h"                  // Move algorithm for avatar move
#include "ascii.h"
// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 
// ---------------- Private prototypes 
/* move
 * 
 * @param id - The ID number of the avatar we want to move
 * @param out_socket - The socket we are writing to
 * @param fileName - The name of the log file
 * @param nAvs - The number of avatars
 *
 * Return: Returns failure for various errors, success when all the avatars
 * find each other. 
 *
 * Psuedocode:
 * 1. Initalize variables by setting up positions, directions, moves, etc.
 * 2. Enter move loop - keep moving until all the avatars find each other
 * 3. Error checking within the loop for connection or errors from the server
 * 4. The avatars have left hand move, the masters have right hand move, if a
 * master finds an avatar, then the avatar will move with the master and also 
 * use right hand rule. 
 * 5. Free memory
 * 6. Error checking 
 */
int move(int id, int out_socket, char *fileName, int nAvs, int height, int width);

/* initalizeLog
 * @param fileName - The name of the log file
 * @param mazeport - Mazeport we are using
 * @param nAvs - The number of avatars
 * 
 * Return: Returns 0 on successful and 1 on failure
 * 
 * Creates the log file for writing. 
 */
int initializeLog(char *fileName, int mazeport, int nAvs, int diff);

/* printSuccess
 * @param fileName - The name of the log file
 * @param move - The successful move
 * @nAvs - The number of avatars
 * 
 * Return: Returns 1 if successful and exits failure if it cannot open the file
 * 
 * Writes the successful solved code to the log file as well as the number of
 * moves it took. 
 */
int printSuccess(char *fileName, AM_Message move, int moves, int nAvs); 
/*============================================================================*/
#endif // AVATAR_H