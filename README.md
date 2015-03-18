# AMAZING PROJECT README
## Members: Chris Leech, Jason Feng, and Jordan Hall

### Description: 
The goal of this project is for each team to design, implement, and test a client application that simulates you and your friends searching for each other in a maze that is generated and managed by a separate server application. Each person in the maze will be represented by an Avatar.

The maze is rectangular, and is a "perfect" maze. A perfect maze is defined as a maze which has one and only one path from any point in the maze to any other point. This means that the maze has no inaccessible sections, no circular paths, and no open areas.

### How to make the project:

The executibles [startup] and [avatar] will be created by running the makefile
present in the current directory. 

The main executible- and the executible you will
be running - is [startup].

Additionally, there is a separate makefile in the testing directory that will create
a unit testing executable that tests movement funcitons.

The other testing executable, a testing shell script named BATS.sh,
is also found in the testing directory, and MUST be run from that
directory. The logs will be created and saved in the main directory.

### Results:

Log files from successful runs can be found in the results directory.

### Usage:

startup -h [hostname] -d [difficulty] -n [nAvs]

[hostname] is the name of the server that is running the maze project.

[difficulty] is the difficulty of the maze you wish to solve.

[nAvs] is the number of avatars that will be put into the maze.

### Usage example:

startup -h pierce.cs.dartmouth.edu -d 4 -n 2

This example would launch the program for a difficulty for maze, with 2 avatars.

### Algorithm:

The general overview of the algorithm is as follows:

One avatar - the avatar with ID 0 - will follow the "right-hand algorithm", which 
means that the avatar will act as if he has placed his right hand against a wall and
followed the wall until the maze is solved.

All other avatars will follow the left-hand algorithm, which is the complement to the
right-hand algorithm. When the master reaches another avatar, the other avatar joins
the master in moving right. The process continues until the avatars are in the same place.
