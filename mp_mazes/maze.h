#pragma once
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <utility>
#include <stack>
class SquareMaze
{
//vectors are 1d arrays
  public:
    int width;
    int height;
    int size; 
    SquareMaze();
    SquareMaze(int w, int h);
    void makeMaze(int w,int h);
    void setWall(int x, int y, int dir, bool exists);

    int get_coord(int x, int y)const;
    int get_down(int x, int y)const;
    int get_up(int x, int y)const;
    int get_left(int x, int y)const;
    int get_right(int x, int y)const;

    cs225::PNG * drawMaze()const;
    cs225::PNG * drawMazeWithSolution();

    std::vector<int> solveMaze();
    bool canTravel_helper(int startpoint, int dir);

    void put_length(std::stack<int>,int *);
    //coordinates in pair in 1d array as coord = y*width + x
    std::pair<int,int> get_point(int coord);
    //first bool is right and second is down
    std::vector<std::pair<bool,bool> > walls;
    //solving maze
    std::vector<bool> visited;
    bool in_same_tree(DisjointSets &,int,int);
    bool canTravel(int x, int y, int dir) const;
    //construction traversing
    int traverser;
};
/* Your code here! */
