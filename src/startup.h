/*  startup.h Header files for startup

    Project name: AmazingProject
    Component name: startup
    
    Primary Author: Jason Feng, Chris Leech, Jordan Hall
    Date Created: 4/27/14

    Input: -h [HOSTNAME] -d [DIFFICULTY] -n [NUMBER_AVATARS]

    Command line options:
        -h: hostname
        -d: difficulty
        -n: nAvatars

    Output: Creates a log file with the Mazeport, User, and time the program 
    started. The log also contains the hash and the number of moves it took
    to solve.

    Error Conditions:

    Special considerations:  
        (e.g., special compilation options, platform limitations, etc.) 
    
======================================================================*/
// do not remove any of these sections, even if they are empty

#ifndef STARTUP_H
#define STARTUP_H

// ---------------- Prerequisites e.g., Requires "math.h"
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
#include <getopt.h>                         // Command line arguments parsing
#include <inttypes.h>                       // Printing out u_int32
// ---------------- Local includes  e.g., "file.h"
#include "amazing.h"                        // Amazing definitions for messages
// ---------------- Constants
#define MAX_FILE 50                         // Max file length
#define MAX_COMMAND 200                     // Max command size
// ---------------- Structures/Types

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/*
 * convertToInt - converts a character buffer to an int
 * @str: the character buffer to inspect
 * @val: a pointer to the converted value
 *
 * Returns 0 if str is null or is a nul terminator. Otherwise, we check is the 
 * str contains a non-numeric digit. If it doesn't, return 1 and val is set to 
 * the the converted value. Else, return 0.
 *
 * Takes strings from messages and converts them to their numerical forms
 *
 */
int convertToInt(const char* const str, uint32_t *val);

/* getFileName
 * @param d - Difficulty level
 * @param n - Number of avatars
 *
 * Return - Returns a filename for the log file
 *
 * Constructs a filename for the log file using the specified difficulty level
 * and the number of avatars
 */
char *getFileName(int d, int n);

/* setUpCommand
 * @param id - Id of the avatar
 * @param nAvs - Number of avatars
 * @param dif - Difficulty level
 * @param ip - IP address
 * @param mport - Mazeport
 * @param file - fileName for log file
 * @param height - height of the maze
 * @param width - width of the maze
 *
 * return - Returns a command
 * 
 * Creates a command using the specified parameters
 */
char *setUpCommand(int id, int nAvs, int dif, char *ip, int mport, char *file, int height, int width);
/*============================================================================*/

#endif // STARTUP_H

