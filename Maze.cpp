#include <iostream>
#include <fstream>
#include <string.h>

#include "Maze.h"

using namespace std;

// Constructor that reads in a file and makes a visited array
Maze::Maze(fstream &file)
{
    char temp[99];
    int i = 0;

    while (file.getline(temp, 99))
    {
        for (int j = 0; j < strlen(temp); j++)
        {
            // Creates restraints for walls, and also notes start and goal position
            if (temp[j] == '#')
            {
                visited[i][j] = 1;
            }
            if (temp[j] == 'S')
            {
                start.first = i;
                start.second = j;
            }
            if (temp[j] == 'G')
            {
                goal.first = i;
                goal.second = j;
            }
        }
        i++;
        column = strlen(temp);
    }
    row = i;
}

// Function that calls the recursive DFS that traverses the grid
// Also checks if it traversed to the goal position, if so, it outputs the full solution, otherwise prints impossible
// Also outputs maze instructions
bool Maze::reachTheGoal()
{
    instruction();

    DFS(start);

    if (visited[goal.first][goal.second] == 2)
    {
        cout << "Remember that * denotes the final solution path taken and ! denotes a path traveled" << endl
             << "Complete Solution:" << endl;
        printSolution();
        return true;
    }
    else
    {
        cout << "Impossible maze." << endl;
        return false;
    }
}

// Function that outputs maze instructions
void Maze::instruction()
{
    cout << "S denotes the start, G denotes the goal." << endl
         << "# denotes walls, ! denotes a path traveled." << endl
         << ". denotes the possible path one can take" << endl
         << "And * denotes the final solution path taken." << endl << endl
         << "This is the maze: " << endl;
}

// Recursive DFS that traverses the grid
bool Maze::DFS(pair <int, int> pos)
{
    visited[pos.first][pos.second] = 2;

    printMap();
    cout << endl;

    moveUp(pos);
    moveRight(pos);
    moveDown(pos);
    moveLeft(pos);
}

// Series of movement functions.
// Checks if move is in bounds, and if the corresponding position is in
// a wall or if has been visited already
bool Maze::moveUp(pair <int, int> pos)
{
    if (visited[goal.first][goal.second])
    {
        return true;
    }
    else if (pos.first > 0 && !visited[pos.first - 1][pos.second])
    {
        // A parent array is kept to keep track of every move
        // Backtracking from the goal position returns the solution
        parentX[pos.first - 1][pos.second] = pos.first;
        parentY[pos.first - 1][pos.second] = pos.second;

        pair <int, int> next;
        next.first = pos.first - 1;
        next.second = pos.second;

        cout << "Moving up from position X=" << pos.first << " Y=" << pos.second << endl;

        // Calls DFS on the next position
        return DFS(next);
    }
    return false;
}

// Same premise as above, but for movement down
bool Maze::moveDown(pair <int, int> pos)
{
    if (visited[goal.first][goal.second])
    {
        return true;
    }
    else if (pos.first < row - 1 && !visited[pos.first + 1][pos.second])
    {
        parentX[pos.first + 1][pos.second] = pos.first;
        parentY[pos.first + 1][pos.second] = pos.second;

        pair <int, int> next;
        next.first = pos.first + 1;
        next.second = pos.second;

        cout << "Moving down from position X=" << pos.first << " Y=" << pos.second << endl;

        // Calls DFS on the next position
        return DFS(next);
    }
    return false;
}

//Same premise as above, but for movement right
bool Maze::moveRight(pair <int, int> pos)
{
    if (visited[goal.first][goal.second])
    {
        return true;
    }
    else if (pos.second < column - 1 && !visited[pos.first][pos.second + 1])
    {
        parentX[pos.first][pos.second + 1] = pos.first;
        parentY[pos.first][pos.second + 1] = pos.second;

        pair <int, int> next;
        next.first = pos.first;
        next.second = pos.second + 1;

        cout << "Moving right from position X=" << pos.first << " Y=" << pos.second << endl;

        // Calls DFS on the next position
        return DFS(next);
    }
    return false;
}

//Same premise as above, but for movement left
bool Maze::moveLeft(pair <int, int> pos)
{
    if (visited[goal.first][goal.second])
    {
        return true;
    }
    else if (pos.second > 0 && !visited[pos.first][pos.second - 1])
    {
        parentX[pos.first][pos.second - 1] = pos.first;
        parentY[pos.first][pos.second - 1] = pos.second;

        pair <int, int> next;
        next.first = pos.first;
        next.second = pos.second - 1;

        cout << "Moving left from position X=" << pos.first << " Y=" << pos.second << endl;

        // Calls DFS on the next position
        return DFS(next);
    }
    return false;
}

// Translates the visited array into a readable maze with symbols
// S denotes the start, G denotes the goal
// # denotes walls, ! denotes a path traveled
// * denotes the final solution path taken
void Maze::printMap()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (i == start.first && j == start.second)
            {
                cout << "S ";
            }
            else if (i == goal.first && j == goal.second)
            {
                cout << "G ";
            }
            else if (visited[i][j] == 1)
            {
                cout << "# ";
            }
            else if (visited[i][j] == 2)
            {
                cout << "! ";
            }
            else if (visited[i][j] == 3)
            {
                cout << "* ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

// Function that backtracks the parent array to return the solution
void Maze::printSolution()
{
    // Current node is set to goal
    pair <int, int> cur = goal;

    // Backtracks on path, marking every node traveled in the visited array to 3, representing the final path
    while (cur != start)
    {
        visited[cur.first][cur.second] = 3;

        pair <int, int> tmp = cur;

        cur.first = parentX[tmp.first][tmp.second];
        cur.second = parentY[tmp.first][tmp.second];
    }
    printMap();
}
