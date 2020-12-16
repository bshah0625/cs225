#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

class AirportDistance{
    public:
        static map<string, vector<double> > initialize(); //Imports data from the text file into a map, then returns the map
        static double distance(string srce, string dest, map<string, vector<double> > airportData); //Returns distance between two given airports using the given map
        static bool checkValid(string airport, map<string, vector<double> > airportData); //Returns whether the given airport is included in the map
};