/*  avatar_test.c  Unit Tests for avatar functions. Same as avatar.c, just 
                    removed some code for simplicity and removed main.

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
#include "../src/amazing.h"                        // Amazing definitions for messages
#include "../src/movealgorithm.h"                  // Move algorithm for avatar move
#include "../src/ascii.h"
// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 
// ---------------- Private prototypes 
int move(int id, int out_socket, char *fileName, int nAvs, int height, int width); // moves avatar
int initializeLog(char *fileName, int mazeport, int nAvs, int diff); // writes out the beginning of the log
int printSuccess(char *fileName, AM_Message move, int moves, int nAvs); // writes out the hash on completion
/*============================================================================*/

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
int move(int id, int out_socket, char *fileName, int nAvs, int height, int width)
{
    int res;                        // Check connection
    AM_Message move;                // The move mesasge you get from the server
    AM_Message next_move;           // The move message you send to the server
    int move_num;                   // The number of moves we've tried
    int direction;                  // The direction we are facing
    int moving_right;               // 1: avatar using right hand rule
    int seen_avatar;                // 0: haven't found
    XYPos *curr;                    // current position
    XYPos *prev;                    // previous position
    XYPos *M_curr;                  // current master position
    XYPos *M_prev;                  // previous master position           
    int moves_attempted;            // number of moves tried in one position
    int M_moves_attempted;          // number of masters tried by master
    int M_direction;                // direction master is facing
    int total_moves;                // tracks how many moves we made

    // ID 0 is always master
    if(id == 0) {
        moving_right = 1; // master is always moving right
    }

    // set up current and previous positions
    total_moves = 0;                
    move_num = 0;
    direction = 0;
    moving_right = 0;
    seen_avatar = 0;
    curr = calloc(1, sizeof(XYPos));
    prev = calloc(1, sizeof(XYPos));
    prev->x = -1;
    prev->y = -1;
    curr->x = -1;
    curr->y = -1;
    moves_attempted = 0;

    M_prev = calloc(1, sizeof(XYPos));
    M_prev->x = 0;
    M_prev->y = 0;
    M_moves_attempted = 0;
    M_direction = 0;

    for(;;) {

        memset(&next_move, 0, sizeof(next_move));
        res = recv(out_socket, &move, sizeof(move), 0);

        // check connection
        if(res == 0) {
            break;
        }
    
        // check message for error
        if (IS_AM_ERROR(ntohl(move.type))) {
            break;
        }

        // if success, we solved it!
        if(ntohl(move.type) == AM_MAZE_SOLVED) {
            break;
        }

        // if we met the master, start moving right
        if(ntohl(curr->x) == ntohl(move.avatar_turn.Pos[0].x) && ntohl(curr->y) == ntohl(move.avatar_turn.Pos[0].y)) {
                moving_right = 1;
        }
        
        if(ntohl(move.avatar_turn.TurnId) == 0) {
            // tracking the master, on the master's turn.
            M_curr = &(move.avatar_turn.Pos[0]); 
            if(ntohl(M_prev->x) != ntohl(M_curr->x) || ntohl(M_prev->y) != ntohl(M_curr->y)) {
                M_moves_attempted = 0;
                M_direction = getDirectionChange(M_prev, M_curr);
            }
            else {
                M_moves_attempted++;
            }

            M_prev->x = M_curr->x;
            M_prev->y = M_curr->y;
        }
        
        // if it's not our turn, don't worry.
        if(ntohl(move.avatar_turn.TurnId) != id) {
            continue;
        }

        // get the current location
        curr = &(move.avatar_turn.Pos[id]);

        // set up our next move
        next_move.type = htonl(AM_AVATAR_MOVE);
        next_move.avatar_move.AvatarId = htonl(id);

        // check if we moved, and if so, reset direction
        if(ntohl(prev->x) != ntohl(curr->x) || ntohl(prev->y) != ntohl(curr->y)) {
            moves_attempted = 0;
            direction = getDirectionChange(prev, curr);
        }
        else {
            moves_attempted++;
        }

        // get next move for left hand
        move_num = getNextMoveL(direction, moves_attempted);

        // update our previous pointer
        prev->x = curr->x;
        prev->y = curr->y;

        // if we are moving right, overwrite the left hand with right hand
        if(moving_right) {
            move_num = getNextMoveR(M_direction, M_moves_attempted);
        }

        // testing, print information about yourself
        //printf("%i, %i, %i, %i\n", id, direction, ntohl(curr->x), ntohl(curr->y));
        //fflush(stdout);

        if(!seen_avatar && moving_right) {
            seen_avatar = 1;
            move_num = 8;
        }

        // set direction and move
        total_moves++;
        next_move.avatar_move.Direction = htonl(move_num);
        send(out_socket, &next_move, sizeof(next_move), 0);
    }

    // free our dynamically allocated memory
    free(M_prev);
    free(prev);
    
    if(res == 0) {
        fprintf(stderr, "Connection timed out!");
        return EXIT_FAILURE;
    }

    // determine why we exited the for loop.
    switch(ntohl(move.type)) {
        case AM_MAZE_SOLVED:
            if(id == 0) {
                printSuccess(fileName, move, total_moves, nAvs);
            }
            return EXIT_SUCCESS;

        case AM_TOO_MANY_MOVES:
            fprintf(stderr, "Max moves exceeded.");
            return EXIT_FAILURE;

        case AM_SERVER_DISK_QUOTA:
            fprintf(stderr, "Server disk quota reached.");
            return EXIT_FAILURE;

        case AM_SERVER_OUT_OF_MEM:
            fprintf(stderr, "Server out of memory.");
            return EXIT_FAILURE;

        default:
            fprintf(stderr, "Unknown error.");
            return EXIT_FAILURE;
    }  
}


/* initalizeLog
 * @param fileName - The name of the log file
 * @param mazeport - Mazeport we are using
 * @param nAvs - The number of avatars
 * 
 * Return: Returns 0 on successful and 1 on failure
 * 
 * Creates the log file for writing. 
 */
int initializeLog(char *fileName, int mazeport, int nAvs, int diff) 
{
    FILE *fp;                           // File pointer
    char *user;                         // User who ran the program

    if((fp = fopen(fileName, "w")) == NULL) {
        return 1;
    }

    time_t current;
    current = time(NULL);

    user = getenv("USER");

    fprintf(fp, "AMAZING log file:\n\n");
    fprintf(fp, "Username: %s // Mazeport: %i // Time: %s\n", 
        user, mazeport, ctime(&current));

    fprintf(fp, "Difficulty: %i // Number of Avatars: %i\n\n", nAvs, diff);

    fclose(fp);

    return 0;
}

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
int printSuccess(char *fileName, AM_Message move, int moves, int nAvs) 
{
    FILE *fp;                           // File pointer
    if((fp = fopen(fileName, "a")) == NULL) {
        fprintf(stderr, "Can't open file %s", fileName);
        return EXIT_FAILURE;
    }
    fprintf(fp, "Maze solved in %i moves.\n", (moves * nAvs));
    fprintf(fp, "Hash: %u", ntohl(move.maze_solved.Hash));
    fclose(fp);
    return 1;
}