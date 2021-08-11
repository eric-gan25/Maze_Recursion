#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

// Maze class
class Maze
{
    public:
        Maze(fstream &file);
        bool reachTheGoal();

   private:
        bool DFS(pair <int, int> pos);
        bool moveUp(pair <int, int> pos);
        bool moveDown(pair <int, int> pos);
        bool moveLeft(pair <int, int> pos);
        bool moveRight(pair <int, int> pos);

        void instruction();
        void printMap();
        void printSolution();

        int row, column;
        int visited[99][99] = {0};
        int parentX[99][99];
        int parentY[99][99];
        pair <int, int> start;
        pair <int, int> goal;
};
#endif // MAZE_H_INCLUDED

