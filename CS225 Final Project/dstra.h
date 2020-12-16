#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <cfloat>

using namespace std;

void calculate(string src, string des, map<string, map<string, double> > dictionary, list<string> tracker, bool landmark, bool second_time);
string minDistance(map<string, double> dist_map, map<string, bool> visited, int size);
void calculate_landmark(string src, string mid, string des, map<string, map<string, double> > dictionary, list<string> tracker);
double print2(string src, string des, map<string, double> dist_map, map<string, string> prev_tracker, bool second_time);
void print(string src, string des, map<string, double> dist_map, map<string, string> prev_tracker);
