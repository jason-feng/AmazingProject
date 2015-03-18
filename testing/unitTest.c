/*  unitTest.c  Tests functions for startup, avatar, and movealgorithm

    Project name: AmazingProject
    Component name: Testing

    This file contains ...
    
    Primary Author: Jason Feng, Chris Leech, Jordan Hall
    Date Created: 4/27/14

    Special considerations:  
        (e.g., special compilation options, platform limitations, etc.) 
    
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>
#include <unistd.h>
// ---------------- Local includes  e.g., "file.h"
#include "../src/movealgorithm.h"
#include "../src/amazing.h"
#include "../src/startup.h"
#include "../src/avatar.h"
// ---------------- Constant definitions 

// ---------------- Macro definitions

// each test should start by setting the result count to zero
#define START_TEST_CASE  int rs=0

// check a condition and if false print the test condition failed
// e.g., SHOULD_BE(dict->start == NULL)
// note: the construct "#x" below is the sstringification preprocessor operator that
//       converts the argument x into a character string constant
#define SHOULD_BE(x) if (!(x))  {rs=rs+1; \
    printf("Line %d test [%s] Failed\n", __LINE__,#x); \
  }

// return the result count at the end of a test
#define END_TEST_CASE return rs

//
// general macro for running a best
// e.g., RUN_TEST(TestDAdd1, "DAdd Test case 1");
// translates to:
// if (!TestDAdd1()) {
//     printf("Test %s passed\n","DAdd Test case 1");
// } else { 
//     printf("Test %s failed\n", "DAdd Test case 1");
//     cnt = cnt +1;
// }
//
#define RUN_TEST(x, y) if (!x()) {              \
    printf("Test %s passed\n", y);              \
} else {                                        \
    printf("Test %s failed\n", y);              \
    cnt = cnt + 1;                              \
}
// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/* translateXTest
 * Tests the translateX function from ascii.c
 * Tests if the translateX function works correctly for negative, positive, 
 * and zero integers
 */
int translateXTest();

/* translateYTest
 * Tests the translateY function from ascii.c
 * Tests if the translateY function works correctly for negative, positive, 
 * and zero integers
 */
int translateYTest();

/* initializeLogTest
 * Tests the initializeLog function from avatar
 * Checks if the log file is created and then deletes it
 */
int initializeLogTest();

/* printSuccessTest
 * Tests the printSuccess function from avatar
 * Checks if the hash value and the total number of moves value is correctly
 * printed onto the log file.
 */
int printSucessTest();

/* convertToIntTest
 * Tests the convertToInt function from startup
 * Tests if the function correctly tests for non numerical inputs and 
 * correctly returns an error. Also tests to make sure the correct numerical
 * input is saved in the buffer.
 */
int convertToIntTest();

/* getFileNameTest
 * Tests the getFileName function from startup
 * Tests if the getFileName function returns the correct formatted log file
 */
int getFileNameTest();

/* setUpCommandTest
 * Tests the setUpCommand function from startup
 * Uses a random group of variables to check if the command is correctly created
 */
int setUpCommandTest();

/* getDirectionChangeTest
 * Tests the getDirectionChange function in movealgorithm
 * Generates all possible combinations of different positions for both the
 * current and previous positions and checks if the direction is correctly
 * returned
 */
int getDirectionChangeTest();

/* getNextMoveLTest
 * Tests the getNextMoveR function from movealgorithm
 * Tries every combination of direction and moves_attempted and checks if the
 * returned direction is correct;
 * Key: west = 0, north = 1, south = 2, east = 3
 * For lefthand rule, should try left, straight, right, back
 */
int getNextMoveLTest();

/* getNextMoveRTest
 * Tests the getNextMoveR function from movealgorithm
 * Tries every combination of direction and moves_attempted and checks if the
 * returned direction is correct;
 * Key: west = 0, north = 1, south = 2, east = 3
 * For righthand rule, should try right, straight, left, back
 */
int getNextMoveRTest();
/*====================================================================*/

int translateXTest() 
{
    START_TEST_CASE;
    int x2;

    int x1 = 1;
    x2 = translateX(x1);
    SHOULD_BE(x2 == 5);

    x1 = -1;
    x2 = translateX(x1);
    SHOULD_BE(x2 == -3);

    x1 = 0;
    x2 = translateX(x1);
    SHOULD_BE(x2 == 1);

    END_TEST_CASE;
}

int translateYTest() 
{
    START_TEST_CASE;
    int y2;

    int y1 = 1;
    y2 = translateY(y1);
    SHOULD_BE(y2 == 3);

    y1 = -1;
    y2 = translateY(y1);
    SHOULD_BE(y2 == -1);

    y1 = 0;
    y2 = translateY(y1);
    SHOULD_BE(y2 == 1);

    END_TEST_CASE;
}

int initializeLogTest()
{
    START_TEST_CASE;
    char *fileName = NULL;
    int mazeport = 40368;
    int nAvs = 4;
    int diff = 3;

    fileName = calloc(100, sizeof(char));
    strcpy(fileName, "Amazing_jfeng_3_4.log");
    
    initializeLog(fileName, mazeport, nAvs, diff);
    
    SHOULD_BE(access(fileName, F_OK) != -1);    // file exists
    unlink(fileName);                           // delete file

    free(fileName);
    END_TEST_CASE;
}

int printSucessTest()
{
    START_TEST_CASE;

    char *fileName = NULL;
    AM_Message move;
    int moves = 1000; 
    int nAvs = 4;
    int mazeport = 40368;
    int diff = 3;
    FILE *fp;
    char *buff;
    int buff_len = 50;
    int success = 0;
    fileName = calloc(100, sizeof(char));
    strcpy(fileName, "Amazing_jfeng_3_4.log");
    move.maze_solved.Hash = 3143850;
    buff = calloc(buff_len, sizeof(char));

    initializeLog(fileName, mazeport, nAvs, diff);
    printSuccess(fileName, move, moves, nAvs);

    if ((fp = fopen(fileName, "r")) != NULL) {
        while (fscanf(fp, "%s\n", buff) == 1) {
            // Get every string and check the total number of moves value and 
            // the hash value, should be 4000 and 2868391680
            if(strcmp(buff, "4000") == 0 || strcmp(buff, "2868391680") == 0) {
                success++;
            }
        }
    }

    fclose(fp);
    free(buff);
    unlink(fileName);
    free(fileName);
    SHOULD_BE(success == 2);
    END_TEST_CASE;
}

int convertToIntTest() 
{
    START_TEST_CASE;

    char *input;
    uint32_t output = 0;
    int error = 1;
    input = calloc(100, sizeof(char));
    
    strcpy(input, "5");
    if (convertToInt(input, &output) == 0) {
        fprintf(stderr, "%s\n", "Error nonnumeric input");
    }
    SHOULD_BE(output == 5);

    strcpy(input, "abc");
    if (convertToInt(input, &output) == 0) {
        error = 0;
    }
    SHOULD_BE(error == 0); 
    error = 1;   

    strcpy(input, "abc123");
    if (convertToInt(input, &output) == 0) {
        error = 0;
    }
    SHOULD_BE(error == 0);    
    error = 1;

    strcpy(input, "123abc");
    if (convertToInt(input, &output) == 0) {
        error = 0;
    }
    SHOULD_BE(error == 0);    
    error = 1;

    free(input);
    END_TEST_CASE;
}

int getFileNameTest() 
{
    START_TEST_CASE;
    int d = 3;
    int n = 4;
    char *fileName;
    fileName = getFileName(d,n);
    SHOULD_BE(strcmp(fileName, "Amazing_jfeng_3_4.log") == 0);
    END_TEST_CASE;
}

int setUpCommandTest() 
{
    START_TEST_CASE;

    int id = 0;
    int nAvs = 2;
    int dif = 4;
    char *ip = NULL;
    int mport = 40368;
    char *file = NULL; 
    int height = 100; 
    int width = 100;
    char *command;

    ip = calloc(100, sizeof(char));
    file = calloc(100, sizeof(char));

    strcpy(ip, "1324324");
    strcpy(file, "Amazing_jfeng_3_4.log");
    command = setUpCommand(id, nAvs, dif, ip, mport, file, height, width);
    SHOULD_BE(strcmp(command, "avatar 0 2 4 1324324 40368 Amazing_jfeng_3_4.log 100 100") == 0);
    free(ip);
    free (file);
    free(command);
    END_TEST_CASE;
}

int getDirectionChangeTest() 
{
    START_TEST_CASE;

    int direction = -1;

    XYPos prev1;
    XYPos curr1;

    prev1.x = 1;
    prev1.y = 1;
    curr1.x = 0;
    curr1.y = 1;
    direction = getDirectionChange(&prev1, &curr1);
    SHOULD_BE(direction == 0);

    prev1.x = 1;
    prev1.y = 1;
    curr1.x = 1;
    curr1.y = 0;
    direction = getDirectionChange(&prev1, &curr1);
    SHOULD_BE(direction == 1);

    prev1.x = 1;
    prev1.y = 1;
    curr1.x = 1;
    curr1.y = 2;
    direction = getDirectionChange(&prev1, &curr1);
    SHOULD_BE(direction == 2);

    prev1.x = 0;
    prev1.y = 1;
    curr1.x = 1;
    curr1.y = 1;
    direction = getDirectionChange(&prev1, &curr1);
    SHOULD_BE(direction == 3);

    END_TEST_CASE;
}

int getNextMoveLTest() 
{
    START_TEST_CASE;

    int direction;
    int moves_attempted;
    int dir;
    // try every combination of direction and moves_attempted
    for (direction = 0; direction < 4; direction++) {
        for(moves_attempted = 0; moves_attempted < 4; moves_attempted++) {
            dir = getNextMoveL(direction, moves_attempted);
            switch (direction) {
                case 0:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 2);
                            break;
                        case 1:
                             SHOULD_BE(dir == 0);
                             break;
                        case 2:
                            SHOULD_BE(dir == 1);
                            break;
                        case 3:
                            SHOULD_BE(dir == 3);
                            break;
                    }
                    break;
               case 1:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 0);
                            break;
                        case 1:
                            SHOULD_BE(dir == 1);
                            break;
                        case 2:
                            SHOULD_BE(dir == 3);
                            break;
                        case 3:
                            SHOULD_BE(dir == 2);
                            break;
                    }
                    break;
               case 2:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 3);
                            break;
                        case 1:
                            SHOULD_BE(dir == 2);
                            break;
                        case 2:
                            SHOULD_BE(dir == 0);
                            break;
                        case 3:
                            SHOULD_BE(dir == 1);
                            break;
                    }
                    break;
               case 3:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 1);
                            break;
                        case 1:
                            SHOULD_BE(dir == 3);
                            break;
                        case 2:
                            SHOULD_BE(dir == 2);
                            break;
                        case 3:
                            SHOULD_BE(dir == 0);
                            break;
                    }
                    break;
            }
        }
    }
    END_TEST_CASE;
}

int getNextMoveRTest() 
{
    START_TEST_CASE;

    int direction;
    int moves_attempted;
    int dir;
    // try every combination of direction and moves_attempted
    for (direction = 0; direction < 4; direction++) {
        for(moves_attempted = 0; moves_attempted < 4; moves_attempted++) {
            dir = getNextMoveR(direction, moves_attempted);
            switch (direction) {
                case 0:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 1);
                            break;
                        case 1:
                             SHOULD_BE(dir == 0);
                             break;
                        case 2:
                            SHOULD_BE(dir == 2);
                            break;
                        case 3:
                            SHOULD_BE(dir == 3);
                            break;
                    }
                    break;
               case 1:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 3);
                            break;
                        case 1:
                            SHOULD_BE(dir == 1);
                            break;
                        case 2:
                            SHOULD_BE(dir == 0);
                            break;
                        case 3:
                            SHOULD_BE(dir == 2);
                            break;
                    }
                    break;
               case 2:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 0);
                            break;
                        case 1:
                            SHOULD_BE(dir == 2);
                            break;
                        case 2:
                            SHOULD_BE(dir == 3);
                            break;
                        case 3:
                            SHOULD_BE(dir == 1);
                            break;
                    }
                    break;
               case 3:
                    switch(moves_attempted) {
                        case 0:
                            SHOULD_BE(dir == 2);
                            break;
                        case 1:
                            SHOULD_BE(dir == 3);
                            break;
                        case 2:
                            SHOULD_BE(dir == 1);
                            break;
                        case 3:
                            SHOULD_BE(dir == 0);
                            break;
                    }
                    break;
            }
        }
    }
    END_TEST_CASE;
}

int main(int argc, char * argv[]) 
{
    int cnt = 0;
    RUN_TEST(translateXTest, "translateXTest");
    RUN_TEST(translateYTest, "translateYTest");
    RUN_TEST(initializeLogTest, "initializeLogTest");
    RUN_TEST(printSucessTest, "printSucessTest");
    RUN_TEST(convertToIntTest, "convertToIntTest");
    RUN_TEST(getFileNameTest, "getFileNameTest");
    RUN_TEST(setUpCommandTest, "setUpCommandTest");
    RUN_TEST(getDirectionChangeTest, "getDirectionChangeTest");
    RUN_TEST(getNextMoveLTest, "getNextMoveLTest");
    RUN_TEST(getNextMoveRTest, "getNextMoveRTest");
    if (cnt == 0) {
        fprintf(stdout, "%s\n", "All tests passed!");
        return 0;
    }
    else {
        fprintf(stdout, "%s\n", "One or more tests failed");
        return 1;
    }
}