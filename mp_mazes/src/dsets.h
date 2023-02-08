/* Your code here! */
#ifndef DSETS_HPP
#define DSETS_HPP
#include <iostream>
#include <vector>
using namespace std;

class DisjointSets{
    public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
    vector<int> set;
    private:
    
};

#pragma once
#endif