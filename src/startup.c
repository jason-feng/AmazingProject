/*  startup.c Creates and initalizes the maze for solving

    Project name: AmazingProject
    Component name: startup
    
    Primary Author: Jason Feng, Chris Leech, Jordan Hall
    Date Created: 4/27/14

    Input: -h [HOSTNAME] -d [DIFFICULTY] -n [NUMBER_AVATARS]

    Command line options:
        -h: hostname
        -d: difficulty
        -n: nAvatars

    Output: Generates a fileName for the log file, initializes connection with 
    the server, and creates avatars for the maze.

    Error Conditions:
        Invalid Number of arguments with flags (7)
        Non numeric arguments for -d and -n flags
        Could not get host when attempting to get ipAddress
        Could not connect to host when connecting via socket        
        Connection timed out
        Unsuccessful init due to bad difficulty level or too many avatars

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
#include "amazing.h"                        // Amazing definitions for messages
// ---------------- Constant definitions 
#define MAX_FILE 50                         // Max file length
#define MAX_COMMAND 200                     // Max command size
// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
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
int convertToInt(const char* const str, uint32_t *val) 
{
    char * endptr;                  
    if (str == NULL || *str == '\0') {
       return 0;
    }
    else {
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
 * @param height - height of the maze
 * @param width - width of the maze
 *
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

int main(int argc, char *argv[]) 
{
    int opt = -1;                   // Commands
    char *hostname = NULL;                 // Name of the host we are using
    uint32_t difficulty = -1;            // Difficulty level
    uint32_t nAvatars = -1;              // Number of avatars
    struct hostent *ipFind = NULL;         // Ip address struct
    char *ipAddress = NULL;                // Ip address
    int res = 0;                        // Connection error
    int out_socket = 0;                 // Socket
    uint32_t mazePort = 0;              // Mazeport
    char *fileName = NULL;                 // Filename for log
    char *command = NULL;                  // Command to send for avatar
    uint32_t type = 0;                  // Message type
    uint32_t errNum = 0;                // Error number for init fail
    struct sockaddr_in servaddr;    // Addresse
    AM_Message initial;             // Message for initialization
    AM_Message okMessage;           // Successful init

    if (argc != 7) {
        fprintf(stderr, "%s\n", "Error invalid number of arguments");
        return EXIT_FAILURE;
    }

    while ((opt = getopt(argc, argv, "n:d:h:")) != -1) {
        switch (opt) {
            case 'h':
                hostname = optarg;
                break;

            case 'd':
                if (convertToInt(optarg, &difficulty) == 0) {
                    fprintf(stderr, "%s\n", "Error non-numeric argument");
                    return EXIT_FAILURE;
                }                
                break;
            case 'n':
                if (convertToInt(optarg, &nAvatars) == 0) {
                    fprintf(stderr, "%s\n", "Error non-numeric argument");
                    return EXIT_FAILURE;
                }
                break;

            default:
                fprintf(stderr, "%s takes options -ndh",argv[0]);
                return EXIT_FAILURE;
        }
    }

    // Setup init message
    memset(&initial, 0, sizeof(initial));
    initial.type = htonl(AM_INIT);
    initial.init.nAvatars = htonl(nAvatars);
    initial.init.Difficulty = htonl(difficulty);
    
    // Get ip address
    if ((ipFind = gethostbyname(hostname)) == NULL) {
        fprintf(stderr, "Could not connect to host: %s", hostname);
        return EXIT_FAILURE;
    }
    ipAddress = ipFind->h_addr_list[0];

    // Socket initalization
    memcpy(&servaddr.sin_addr, ipFind->h_addr_list[0], ipFind->h_length);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port =  htons(atoi(AM_SERVER_PORT));

    // Get connection
    out_socket = socket(AF_INET, SOCK_STREAM, 0);
    res = connect(out_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    if(res < 0) {
        fprintf(stderr, "Could not connect to host: %s", hostname);
        return EXIT_FAILURE;
    }

    send(out_socket, &initial, sizeof(initial), 0);

    // Check return message from init
    memset(&okMessage, 0, sizeof(okMessage));
    res = recv(out_socket, &okMessage, sizeof(okMessage), 0);
    if(res == 0) {
        fprintf(stderr, "Connection timed out\n");
        return EXIT_FAILURE;
    }
    
    // Check message type
    type = ntohl(okMessage.type);
    if (IS_AM_ERROR(type))
    {
        errNum = ntohl(okMessage.init_failed.ErrNum);
        fprintf(stderr, "Unsuccessful init - ");
        if(errNum == AM_INIT_BAD_DIFFICULTY) {
            fprintf(stderr, "%s\n", "Bad Difficulty Level");
        }
        if(errNum == AM_INIT_TOO_MANY_AVATARS) {
            fprintf(stderr, "%s\n", "Too many avatars");
        }
        return EXIT_FAILURE;
    }

    // Get mazePort and fileName
    mazePort = ntohl(okMessage.init_ok.MazePort);
    fileName = getFileName(difficulty, nAvatars);

    int height = ntohl(okMessage.init_ok.MazeHeight);
    int width = ntohl(okMessage.init_ok.MazeWidth);

    // Create avatars
    for(int i = 0; i < nAvatars; i ++) {
        if((res = fork()) == 0) {
            command = setUpCommand(i, nAvatars, difficulty, ipAddress, 
                mazePort, fileName, height, width);
            system(command);
            free(fileName);
            free(command);
            return(EXIT_SUCCESS);
        }  
    }
    free(fileName);
    return(EXIT_SUCCESS);
}
