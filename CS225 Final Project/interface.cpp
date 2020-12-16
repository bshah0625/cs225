#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include "interface.h"
#include "distance.h"

string code_1 = "NULL";
string code_2 = "NULL";

int main(){
    //Initialize map for airport locations
    map<string, vector<double> > airportData = AirportDistance::initialize();
    cout << airportData.size();
    //Only allow a valid input (included in the map)
    bool valid = true;
    do{
        if(!valid)
            cout << "Invalid input." << endl;
        cout << "Input your First Airport Code (Ex. ORD, ATL, PHX): " << endl;
        cin >> code_1;
        boost::to_upper(code_1); //Converts input to all uppercase
        valid = AirportDistance::checkValid(code_1, airportData); //Function that checks if given string is valid airport
    }while(!valid);
    do{
        if(!valid)
            cout << "Invalid input." << endl;
        cout << "Input your Second Airport Code (Ex. ORD, ATL, PHX): " << endl;
        cin >> code_2;
        boost::to_upper(code_2);
        valid = AirportDistance::checkValid(code_2, airportData);
    }while(!valid);

    //Displays processed inputs
    cout << "Departure: " << code_1 << endl;
    cout << "Destination: " << code_2 << endl;

    //calculates distance between airport code_1 and code_2 directly (TEMPORARY, NEEDS TO BE REPLACED WITH ALGORITHM TO CALCULATE BASED ON ROUTES)
    double distanceM = AirportDistance::distance(code_1, code_2, airportData); //distance function returns distance between airports in meters
    cout << "Distance: " << distanceM/1000 << "km" << endl;
}