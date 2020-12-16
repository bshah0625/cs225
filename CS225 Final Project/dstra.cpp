#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <cfloat>

//tbae
using namespace std;

string minDistance(map<string, double> dist_map, map<string, bool> visited, int size){
    double min = DBL_MAX;
    string min_key;

    map<string, double>::iterator it;
    for (it = dist_map.begin(); it != dist_map.end(); it++){
        if (dist_map[it->first] < min && visited[it->first] == false){
            min = dist_map[it->first];
            min_key = it->first;
        }
    }

    return min_key;
}

void print(string src, string des, map<string, double> dist_map, map<string, string> prev_tracker){
    //finding the shortest path from src -> des
    list<string> spath;
    spath.push_front(des);
    string prev = prev_tracker[des];
    while (prev != ""){
        spath.push_front(prev);
        prev = prev_tracker[prev];
    }

    //printing out path and distance
    if (dist_map[des] == DBL_MAX){
        cout << "\nThere exists no routes between the two places selected. Please try again.\n";
        return;
    }

    cout << "The shortest path from " << src << " to " << des <<": \n";

    int counter = 0;
    while (!spath.empty()){
        if (counter == 0){
            cout << spath.front();
        }else{
            cout << " -> " << spath.front();
        }

        spath.pop_front();
        counter++;
    }

    cout << "\nThe total distance is " << dist_map[des] << " kilometers. \n";
}

double print2(string src, string des, map<string, double> dist_map, map<string, string> prev_tracker, bool second_time){
    if (!second_time){
        list<string> spath;
        spath.push_front(des);
        string prev = prev_tracker[des];
        while (prev != ""){
            spath.push_front(prev);
            prev = prev_tracker[prev];
        }

        //printing out path and distance
        if (dist_map[des] == DBL_MAX){
            cout << "\nThere exists no routes between the two places selected. Please try again.\n";
            return -1;
        }

        int counter = 0;
        while (!spath.empty()){
            if (counter == 0){
                cout << spath.front();
            }else{
                cout << "-> " << spath.front();
            }

            spath.pop_front();
            counter++;
        }
        return dist_map[des];
    }else {
        list<string> spath;
        spath.push_front(des);
        string prev = prev_tracker[des];
        while (prev != ""){
            spath.push_front(prev);
            prev = prev_tracker[prev];
        }

        if (dist_map[des] == DBL_MAX){
            cout << "\nThere exists no routes between the two places selected. Please try again.\n";
            return -1;
        }

        int counter = 0;
        spath.pop_front();
        cout << " -> ";
        while (!spath.empty()){
            if (counter == 0){
                cout << spath.front();
            }else{
                cout << " -> " << spath.front();
            }

            spath.pop_front();
            counter++;
        }
        return dist_map[des];

    }
}

double calculate(string src, string des, map<string, map<string, double> > dictionary, list<string> tracker, bool landmark, bool second_time){
    // map {vertex: distance from src node}
    map<string, double> dist_map;

    //map {vertex: prev_vertex}
    map<string, string> prev_tracker;

    //map {vertex: visited}
    map<string, bool> visited;

    //initialize all key values
    //for visited map, set all values to false;
    for (list<string>::iterator it = tracker.begin(); it != tracker.end(); it++){
        dist_map[*it] = DBL_MAX;
        prev_tracker[*it] = "";
        visited[*it] = false;
    }

    //distance from src -> src is 0
    dist_map[src] = 0;

    for (int count = 0; count < tracker.size(); count++) {

        //getting the key of the next minimum distance vertex
        string key = minDistance(dist_map, visited, tracker.size());

        //marking the key visited now
        visited[key] = true;

        //visitng all connected edges and doing proper updating and traversal
        map<string, double>::iterator it2;
        for (it2 = dictionary[key].begin(); it2 != dictionary[key].end(); it2++){
            string temp_key = it2->first;
            if (!visited[temp_key]){ //checking if its visited
                if (it2->second + dist_map[key] < dist_map[temp_key]){
                    dist_map[temp_key] = it2->second + dist_map[key];
                    prev_tracker[temp_key] = key;
                }
            }
        }


    }

    if (!landmark){
        print(src, des, dist_map, prev_tracker);
        return 0;
    }else{
        double toReturn = print2(src, des, dist_map, prev_tracker, second_time);
        return toReturn;
    }


}


void calculate_landmark(string src, string mid, string des, map<string, map<string, double> > dictionary, list<string> tracker){

    cout << "\nThe shortest path from " << src << " to " << des << " WHILE visiting " << mid <<": \n";

    double dist1 = calculate(src, mid, dictionary, tracker, true, false);
    double dist2 = calculate(mid, des, dictionary, tracker, true, true);

    if (dist1 == -1 || dist2 == -1){
        return;
    }


    cout << "\nThe total distance is " << dist1 + dist2 << " kilometers. \n";
}
