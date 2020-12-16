#pragma once
#include <vector>
using namespace std;

class DisjointSets
{
  public:
    vector<int> uptrees;
    void addelements(int);
    void setunion(int,int);
    void print_set();
    int find(int);
    int size(int);


};
/* Your code here! */
