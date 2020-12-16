#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include "distance.h"

#define PI 3.141592653589793238


using namespace std;

map<string, vector<double> > AirportDistance::initialize(){
    ifstream file;
    file.open("dataset_airports.txt");
    //key is 3 letter name, value is latitude, longitude, altitude
    map<string, vector<double> > airportData;

    if(file.is_open()){
        string line;
        string delim = ",";
        while(getline(file, line)){
            string airport;
            for(int count = 1; count < 9; count++){ //(after) 4: name, 6: lat, 7: lon, 8: alt
                //find index of next comma
                int i = line.find(delim);
                //trim string to start after that comma
                line.erase(0, i + 1);
                //if count is 4, trim the first character (opening "), then create new map entry of next 3 chars (name)
                if(count == 4){
                    if(line.substr(0, 2) == "\\N")
                        break;
                    airport = line.substr(1, 3);
                    // cout << airport << endl;
                    vector<double> location;
                    airportData[airport] = location;
                }
                //if count is 6, store the number up to the next comma as the first element of the value (latitude)
                if(count == 6){
                    int temp = line.find(delim);
                    double latitude = atof((line.substr(0, temp)).c_str());
                    // cout << setprecision(16) << "double: " << latitude << endl;
                    airportData[airport].push_back(latitude);
                }
                //if count is 7, store the number up to the next comma as the second element of the value (longitude)
                if(count == 7){
                    int temp = line.find(delim);
                    double longitude = atof((line.substr(0, temp)).c_str());
                    // cout << setprecision(16) << "double: " << longitude << endl;
                    airportData[airport].push_back(longitude);
                }
                //if count is 8, store the number up to the next comma as the third element of the value (altitude) (only implemented in case we use it)
                if(count == 8){
                    int temp = line.find(delim);
                    double altitude = atof((line.substr(0, temp)).c_str());
                    // cout << setprecision(16) << "double: " << altitude << endl;
                    airportData[airport].push_back(altitude);
                }
            }
        }
        file.close();
    }
    return airportData;
}

//Calculates distance from srce to dest airport using airportData map, 
//-------------DOES NOT CHECK IF AIRPORT CODES ARE VALID!-------------
double AirportDistance::distance(string srce, string dest, map<string, vector<double> > airportData){
    double lat1, lat2, lon1, lon2; //found based on inputs
    // boost::to_upper(srce);
    // if(checkValid(srce, airportData)){
        lat1 = airportData[srce][0];
        lon1 = airportData[srce][1];
        // cout << "Departing from " << srce << " at " << lat1 << "," << lon1 << "." << endl;
    // }else
    // {
        // cout << "Invalid input. smh" << endl;
        // return 0;
    // }


    // boost::to_upper(dest);
    // if(checkValid(dest, airportData)){
        lat2 = airportData[dest][0];
        lon2 = airportData[dest][1];
    //     cout << "Flying to " << dest << " at " << lat2 << "," << lon2 << "." << endl;
    // }else
    // {
    //     cout << "Invalid input. smh" << endl;
    //     return 0;
    // }
    
    //Algorithm source: https://www.movable-type.co.uk/scripts/latlong.html
    double R = 6371000;
    double phi1 = lat1 * PI / 180;
    double phi2 = lat2 * PI / 180;
    double deltaPhi = (lat2 - lat1) * PI / 180;
    double deltaLambda = (lon2 - lon1) * PI / 180;

    double a = sin(deltaPhi/2) * sin(deltaPhi/2) +
          cos(phi1) * cos(phi2) *
          sin(deltaLambda/2) * sin(deltaLambda/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    double d = R * c;
    return d;
}

bool AirportDistance::checkValid(string airport, map<string, vector<double> > airportData){
    return airportData.end() != airportData.find(airport);
}

// int main(){   
//     map<string, vector<double> > airportData = AirportDistance::initialize();

//     //Prompt source and destination airport (for testing only)
//     string srce, dest; //inputs
//     cout << "Source airport: ";
//     getline(cin, srce);
//     boost::to_upper(srce);

//     cout << "Destination airport: ";
//     getline(cin, dest);
//     boost::to_upper(dest);
    
//     cout << "Flight distance: " << AirportDistance::distance(srce, dest, airportData) << " meters." << endl;
// }