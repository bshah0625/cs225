#include "maze.h"
#include "dsets.h"
#include <time.h>
#include <cstdlib>
SquareMaze::SquareMaze()
{
  height = 0;
  width = 0;
}

SquareMaze::SquareMaze(int w, int h)
{
  width = w; //contructor in case params needed
  height = h;
}



int SquareMaze::get_coord(int x, int y)const
{
  return (width*y)+x; //helpers to acces up down left and right and self
}

int SquareMaze::get_down(int x, int y)const
{
  if(y+1==height)return get_coord(x,y);
  return (width*(y+1))+x;
}

int SquareMaze::get_up(int x, int y)const
{
  if(y-1<0)return get_coord(x,y);
  return (width*(y-1))+x;
}

int SquareMaze::get_right(int x, int y)const
{
  if(x+1==width)return get_coord(x,y);
  return (width*y)+x+1;
}

int SquareMaze::get_left(int x, int y)const
{
  if(x-1<0)return get_coord(x,y);
  return (width*y)+x-1;
}

//since 0 is for right which is the first in the pair, sets appropriate boolean in the pair
//sets first to exists if 0, sets second to exists if 1

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  if(dir>1||dir<0)
  {
    return;
  }
  int temp = get_coord(x,y);
  if(dir==0)
  {
    walls[temp].first = exists;
    return;
  }
  walls[temp].second = exists;
}

std::pair<int,int> SquareMaze::get_point(int coord)
{
  std::pair<int,int> point = std::make_pair(coord%width,coord/width);
  return point;
}

bool SquareMaze::in_same_tree(DisjointSets & temp, int a, int b)
{
  if(temp.find(a)==temp.find(b))
  {
    return true;
  }
  return false;
}


bool SquareMaze::canTravel(int x, int y, int dir) const
{
  int temp = (y*width)+x;
  if(dir==0)
  {
    return !(walls[temp].first);
  }
  if(dir==1)
  {
    return !(walls[temp].second);
  }
  if(dir==2)
  {
    int temp1 = get_left(x,y);
    //std::cout<<temp1<<std::endl;
    if(temp1!=temp)
    {
      return !(walls[temp1].first);
    }
    return false;
  }
  if(dir==3)
  {
    int temp2 = get_up(x,y);
    if(temp2!=temp){
      return !(walls[temp2].second);
    }
    return false;
  }
  return false;

}


void SquareMaze::makeMaze(int w, int h)
{
 //constructing new maze
 width = w;
 height = h;//assigning  width and height
 size= w*h;

 walls.resize(size);//sets walls and visited to size
 visited.resize(size);
 for(int i=0;i<size;i++)
 {
   walls[i].first = true;
   walls[i].second = true;//setting all walls to true for initial construction
   visited[i] = false;//for solving
 }
 std::stack<int> s; //stack for traversing on make
 DisjointSets checker; //uptree for checking
 checker.addelements(size);
 s.push(0);

 while(!s.empty())
 {
   traverser = s.top();
   s.pop();//pops
   checker.setunion(0,traverser);
  
   std::pair<int,int> point = get_point(traverser);//getting point to use in get point functions eg get_coord
   //if down and current coord is not in the same tree ie connected remove wall and push down to visit later

   int random = std::rand();
   if(random%2==0)
   {
     if(!in_same_tree(checker,get_coord(point.first,point.second),get_down(point.first,point.second)))// && walls[traverser].second)//checking if in tree
     {
       setWall(point.first,point.second,1,false);//remove wall (down)

       s.push(get_down(point.first,point.second));//pushes in stack
     }
     //if right and current coord is not in the same tree ie connected remove wall and push down to visit later
     if(!in_same_tree(checker,get_coord(point.first,point.second),get_right(point.first,point.second)))// && walls[traverser].first) //checking if intree
     {

       setWall(point.first,point.second,0,false);//remove wall (right)
       s.push(get_right(point.first,point.second));//pushes in stack
     }
   }else
   {
     //if right and current coord is not in the same tree ie connected remove wall and push down to visit later
     if(!in_same_tree(checker,get_coord(point.first,point.second),get_right(point.first,point.second)))// && walls[traverser].first) //checking if intree
     {
       setWall(point.first,point.second,0,false);//remove wall (right)
       s.push(get_right(point.first,point.second));//pushes in stack
     }
     if(!in_same_tree(checker,get_coord(point.first,point.second),get_down(point.first,point.second)))// && walls[traverser].second)//checking if in tree
     {
       setWall(point.first,point.second,1,false);//remove wall (down)

       s.push(get_down(point.first,point.second));//pushes in stack
     }
   }

 }

}

bool SquareMaze::canTravel_helper(int startpoint, int dir)
{
  std::pair<int,int> p = get_point(startpoint);//helper for below function
  return canTravel(p.first,p.second,dir);
}


vector<int> SquareMaze::solveMaze()
{
  std::stack<int> s;
  int * dist = new int[size];
  if(visited[0]==false)
  {
    for(int i = 0; i<size;i++)
    {
      visited[i]=false;
    }
  }
  s.push(0);
  put_length(s,dist);
 
  std::cout<<std::endl;
  int i = size-width;
  int max_dist = i;
  for(;i<size;i++)
  {
    if(dist[i]>dist[max_dist])
    {
      max_dist = i;
    }
  }
  vector<int> temp;
  int runner = max_dist;
  while(runner!=0)
  {
    if(canTravel_helper(runner,0) && dist[runner]-dist[runner+1]==1)//right
    {
      temp.insert(temp.begin(),2);
      runner =runner+1;
    }
    if(canTravel_helper(runner,1) && dist[runner]-dist[runner+width]==1)//down
    {
      temp.insert(temp.begin(),3);
      runner =runner+width;
    }
    if(canTravel_helper(runner,2) && dist[runner]-dist[runner-1]==1)//left
    {
      temp.insert(temp.begin(),0);
      runner =runner-1;
    }
    if(canTravel_helper(runner,3) && dist[runner]-dist[runner-width]==1)//up
    {
      temp.insert(temp.begin(),1);
      runner =runner-width;
    }
  }

  delete[] dist;
  return temp;
}

void SquareMaze::put_length(std::stack<int> s,int * dist){
  int len = 0;
  dist[0] = 0;
  int runner;
  if(visited[0]==false)
  {
    visited[0] = true;
    while(!s.empty())//uses DFS to traverse all points and assign a given length
    {
      runner = s.top();//become stack top
      s.pop();
      len = dist[runner];//assign length so that for example if we come back to a location after a traversal reaches a
      //dead end, the correct length is assigned
      if(canTravel_helper(runner,0) && !visited[runner+1])//right
      {
        dist[runner+1] = len+1;//assigns one away if can travel
        visited[runner+1] = true;
        s.push(runner+1);
      }
      if(canTravel_helper(runner,1) && !visited[runner+width])//down
      {
        dist[runner+width] = len+1;
        visited[runner+width] = true;
        s.push(runner+width);
      }
      if(canTravel_helper(runner,2) && !visited[runner-1])//left
      {
        dist[runner-1] = len+1;
        visited[runner-1] = true;
        s.push(runner-1);
      }
      if(canTravel_helper(runner,3) && !visited[runner-width])//up
      {
        dist[runner-width] = len+1;
        visited[runner-width] = true;
        s.push(runner-width);
      }
    }
  }
  if(visited[0]==true)
  {
    visited[0] = false;
    while(!s.empty())//uses DFS to traverse all points and assign a given length
    {
      runner = s.top();//become stack top
      s.pop();
      len = dist[runner];//assign length so that for example if we come back to a location after a traversal reaches a
      //dead end, the correct length is assigned
      if(canTravel_helper(runner,0) && visited[runner+1])//right
      {
        dist[runner+1] = len+1;//assigns one away if can travel
        visited[runner+1] = false;
        s.push(runner+1);
      }
      if(canTravel_helper(runner,1) && visited[runner+width])//down
      {
        dist[runner+width] = len+1;
        visited[runner+width] = false;
        s.push(runner+width);
      }
      if(canTravel_helper(runner,2) && visited[runner-1])//left
      {
        dist[runner-1] = len+1;
        visited[runner-1] = false;
        s.push(runner-1);
      }
      if(canTravel_helper(runner,3) && visited[runner-width])//up
      {
        dist[runner-width] = len+1;
        visited[runner-width] = false;
        s.push(runner-width);
      }
    }
  }
}
cs225::PNG * SquareMaze::drawMaze() const {
  cs225::PNG* ret = new cs225::PNG((width * 10) + 1, (height * 10) + 1);
  for (int i = 0; i < (height * 10) + 1; i++)
  {
    ret->getPixel(0, i).l = 0.0;
  }
  for (int i = 10; i < (width * 10) + 1; i++)
  {
    ret->getPixel(i, 0).l = 0.0;
  }
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      if (walls[get_coord(x,y)].first)
      {
        for (int i = 0; i < 11; i++)
        {
          ret->getPixel((10 * x) + 10, (10 * y) + i).l = 0.0;
        }
      }
      if (walls[get_coord(x,y)].second)
      {
        for (int i = 0; i < 11; i++)
        {
          ret->getPixel((10 * x) + i, (10 * y) + 10).l = 0.0;
        }
      }
    }
  }
  return ret;
}

cs225::PNG * SquareMaze::drawMazeWithSolution() {
  cs225::PNG* ret = drawMaze();
  vector<int> steps = solveMaze();
  int x = 5; //starting
  int y = 5; //starting
  for (size_t j = 0; j < steps.size(); j++) {
    if (steps[j] == 0) {
      for (int i = 0; i < 11; i++) {//draw 10
        ret->getPixel(x+i, y).h = 0;
        ret->getPixel(x+i, y).s = 1;
        ret->getPixel(x+i, y).l = 0.5;
        ret->getPixel(x+i, y).a = 1.0;
      }
      x += 10;//increment currpos
    } else if (steps[j] == 1) {
      for (int i = 0; i < 11; i++) {
        ret->getPixel(x, y+i).h = 0;
        ret->getPixel(x, y+i).s = 1;
        ret->getPixel(x, y+i).l = 0.5;
        ret->getPixel(x, y+i).a = 1.0;
      }
      y += 10;//inc
    } else if (steps[j] == 2) {
      for (int i = 0; i < 11; i++) {
        ret->getPixel(x-i, y).h = 0;
        ret->getPixel(x-i, y).s = 1;
        ret->getPixel(x-i, y).l = 0.5;
        ret->getPixel(x-i, y).a = 1.0;
      }
      x -= 10;//dec
    } else if (steps[j] == 3) {
      for (int i = 0; i < 11; i++) {
        ret->getPixel(x, y-i).h = 0;
        ret->getPixel(x, y-i).s = 1;
        ret->getPixel(x, y-i).l = 0.5;
        ret->getPixel(x, y-i).a = 1.0;
      }
      y -= 10;//dec
    }
  }
  int mx = x/10;//final
  for (int i = 1; i < 10; i++) {
    ret->getPixel(mx*10 +i, (height)*10).l = 1;
    ret->getPixel(mx*10 +i, (height)*10).a = 1;
  }
  return ret;
}
/* Your code here! */
