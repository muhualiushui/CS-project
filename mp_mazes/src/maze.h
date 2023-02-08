/* Your code here! */
#ifndef MAZE_HPP
#define MAZE_HPP
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <queue>
#include <map>
class SquareMaze:public cs225::PNG{
    public:
    SquareMaze(){};
    bool canTravel(int x,int y,int dir );
    PNG * drawMaze()const;
    PNG * drawMazeWithSolution();	
    void makeMaze(int width,int height);
    void setWall(int x, int y, int dir, bool exist);
    vector<int> solveMaze();
    DisjointSets maze;
    struct Wall{
        bool right=true;
        bool down=true;
    };
    vector<Wall> wall;
    int width_=0;
    int height_=0;
    ///////helper
    vector<tuple<int,int,int>> adjacent_pair(pair<int,int> index, map<pair<int,int>,bool> visited);
    void sub_direction(map<pair<int,int>,bool>& visited,vector<vector<int>>& mul_routes,vector<int> route,pair<int,int> start,int dir);
    private:
};
#pragma once
#endif