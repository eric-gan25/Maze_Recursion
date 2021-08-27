#include <iostream>
#include <fstream>

#include "Maze.h"

using namespace std;

int main()
{
    // Opens File
    fstream mazeFile;
    mazeFile.open("maze1.txt");

    // Creates a maze object that contains the maze
    Maze myMaze(mazeFile);

    // Runs a recursive depth first search and if the maze is possible, it outputs the full solution, otherwise prints impossible
    myMaze.reachTheGoal();

    return 0;
}

