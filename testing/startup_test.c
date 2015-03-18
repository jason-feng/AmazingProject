/*  startup_test.c This is the same as startup.c except with the main removed
                    for unit testing

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
    
==============================================================================*/
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
#include <getopt.h>                         // Command line arguments parsing
#include <inttypes.h>                       // Printing out u_int32
// ---------------- Local includes  e.g., "file.h"
#include "../src/amazing.h"                        // Amazing definitions for messages
// ---------------- Constant definitions 
#define MAX_FILE 50                         // Max file length
#define MAX_COMMAND 200                     // Max command size
// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int convertToInt(const char* const str, uint32_t *val); // parses numeric input
char *getFileName(int d, int n);                        // get log file name
char *setUpCommand(int id, int nAvs, int dif, char *ip, int mport, char *file, int height, int width);
/*============================================================================*/

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
int convertToInt(const char* const str, uint32_t *val) {
    if (str == NULL || *str == '\0') {
       return 0;
    }
    else {
        char * endptr;
        *val = strtol (str, &endptr, 0);
        return *endptr == '\0';
    }
}

/* getFileName
 * @param d - Difficulty level
 * @param n - Number of avatars
 *
 * Return - Returns a filename for the log file
 *
 * Constructs a filename for the log file using the specified difficulty level
 * and the number of avatars
 */
char *getFileName(int d, int n) 
{
    char *fileName;                         // File name
    char digit[10];                         // Used for difficulty and nAvs
    fileName = calloc(1, MAX_FILE * sizeof(char));
    strcat(fileName, "Amazing_");
    strcat(fileName, getenv("USER"));

    fileName[strlen(fileName)+1] = '\0';
    fileName[strlen(fileName)] = '_';

    sprintf(digit, "%u", d);
    strcat(fileName, digit);

    fileName[strlen(fileName)+1] = '\0';
    fileName[strlen(fileName)] = '_';

    sprintf(digit, "%u", n);
    strcat(fileName, digit);
    strcat(fileName, ".log");
    return fileName;
}

/* setUpCommand
 * @param id - Id of the avatar
 * @param nAvs - Number of avatars
 * @param dif - Difficulty level
 * @param ip - IP address
 * @param mport - Mazeport
 * @param file - fileName for log file
 * return - Returns a command
 * 
 * Creates a command using the specified parameters
 */
char *setUpCommand(int id, int nAvs, int dif, char *ip, int mport, char *file, int height, int width) 
{
    char *command = NULL;              // Command
    command = calloc(MAX_COMMAND+1, sizeof(char));
    snprintf(command, (MAX_COMMAND+1) * sizeof(char), 
        "avatar %i %i %i %s %i %s %i %i", id, nAvs, dif, ip, mport, file, height, width);

    return command;
}