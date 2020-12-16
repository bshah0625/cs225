#include "dsets.h"
#include <iostream>
using namespace std;

int DisjointSets::size(int elem)
{
  int temp3 = find(elem);
  return -1*uptrees[temp3];
}

int DisjointSets::find(int elem)
{
  if(elem>=(int)uptrees.size())
  {
    return -1;
  }
  if(uptrees[elem]<0)
  {
    return elem;
  }
  int root = find(uptrees[elem]);
  uptrees[elem] = root;
  return root;
}

void DisjointSets::setunion(int first,int second)
{
  int temp1 = find(first);
  int temp2 = find(second);
  if(temp1==temp2)return;
  if(uptrees[temp1]>uptrees[temp2])
  {
    uptrees[temp2]+=uptrees[temp1];//update size
    uptrees[temp1] = temp2;//temp1 points to temp2
    return;
  }
  uptrees[temp1]+=uptrees[temp2];//update size
  uptrees[temp2] = temp1;//temp2 points to temp1
}

void DisjointSets::print_set()
{
  for(int i=0;i<(int)uptrees.size();i++){
    cout<<uptrees[i]<<" ";
  }
  cout<<endl;
}

void DisjointSets::addelements(int num)
{
  for(int i=0;i<num;i++)
  {
    uptrees.push_back(-1);
  }
}
/* Your code here! */
