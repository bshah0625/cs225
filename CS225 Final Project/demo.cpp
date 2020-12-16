#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include "distance.h"
#include "dstra.h"
#include <stdlib.h>

using namespace std;

int main(){
    //creating graph
    map<string, map<string, double> > dictionary;

    //creating tracker list of airports that are inserted (must be unique)
    list<string> tracker;
    list<string> src_tracker;
    list<string> des_tracker;

    //initializing airport database
    map<string, vector<double> > airport_data = AirportDistance::initialize();
    //reopening
    ifstream myfile;
    myfile.open ("dataset_routes.txt");
    string line;
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;

    //FIX BOUND IF YOU DONT WANT TO WAIT FOR A LONG TIME**************************
    int bound = 60000;

    if (myfile.is_open()) {
        while ( getline(myfile,line) ){
            counter3++;
            cout << " LOADING " << counter3 << "/" << bound << "\n";
            if (counter3 == bound){
                break;
            }
            counter = 1;
            std::string s = line;
            std::string delimiter = ",";

            size_t pos = 0;
            std::string token;
            std::string token_holder;

            //basically a c++ version of a python .split(string)
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);

                s.erase(0, pos + delimiter.length());

                //counter 3 would mean the starting destination
                if (counter == 3){
                     if (AirportDistance::checkValid(token, airport_data) == false){
                         break;
                     }else{
                         bool unique = (std::find(tracker.begin(), tracker.end(), token) == tracker.end());
                         if (unique){
                             tracker.push_back(token);
                         }
                         unique = (std::find(src_tracker.begin(), src_tracker.end(), token) == src_tracker.end());
                         if (unique){
                             src_tracker.push_back(token);
                         }
                     }
                    //making sure that a key exists in the dictionary
                    if (dictionary.find(token) == dictionary.end()) {
                      counter2++;
                      map<string, double> temp;
                      dictionary[token] = temp;
                    }
                    //saving the key for when we reach the ending destination
                    token_holder = token;

                //counter 5 would mean the ending destination
                } else if (counter == 5){
                    if (AirportDistance::checkValid(token, airport_data) == false){
                        break;
                    }
                    bool unique = (std::find(tracker.begin(), tracker.end(), token) == tracker.end());
                    if (unique){
                        tracker.push_back(token);
                    }
                    unique = (std::find(des_tracker.begin(), des_tracker.end(), token) == des_tracker.end());
                    if (unique){
                        des_tracker.push_back(token);
                    }
                    map<string, double> *temp = &dictionary[token_holder];
                    (*temp)[token] = (AirportDistance::distance(token_holder, token, airport_data)) / 1000;



                    //list<string>::iterator it = std::find(dictionary[token_holder].begin(), dictionary[token_holder].end(), token);
                    //bool check = it != dictionary[token_holder].end();
                    //if (!check){
                        //dictionary[token_holder].push_back(token);
                    //}
                }

                counter++;
            }


        }
        myfile.close();
        cout << "\n \n \n \n ";
    }



    //INTERFACE GOES HERE
    string code_1;
    string code_2;
    string code_3;
    bool valid = true;
    bool error;
    bool error2;
    while (true){
        cout << "\n\n\nWhich of the following options would you like to choose?\n";
        cout << "1. Shortest Path from point A to B\n";
        cout << "2. Shortest Path from point A to B through C\n";
        string output;
        cin >> output;
        int temp;

        while (true){
            try {
                temp = stoi(output);
                break;
            }catch (...){
                cout << "Option does not exist. Please put in either 1 or 2.";
            }
        }



        if (temp == 1) {
            do{
                if(!valid)
                    cout << "Invalid input" << endl;
                else if(error){
                    cout << "There are no source destinations of " << code_1 << " in our database. Try another one!";
                }
                cout << "\n \nInput your ***FIRST*** Airport Code (Ex. ORD, ATL, PHX): " << endl;
                cin >> code_1;
                if (code_1 == "quit"){
                    break;
                }
                valid = AirportDistance::checkValid(code_1, airport_data); //Function that checks if given string is valid airport
                error = (std::find(src_tracker.begin(), src_tracker.end(), code_1) == src_tracker.end());
            }while(!valid || error);
            do{
                if(!valid)
                    cout << "Invalid input." << endl;
                else if(error)
                    cout << "There are no arrival destinations of " << code_1 << " in our database. Try another one!";
                cout << "Input your *****SECOND***** Airport Code (Ex. ORD, ATL, PHX): " << endl;
                cin >> code_2;
                valid = AirportDistance::checkValid(code_2, airport_data);
                error = (std::find(des_tracker.begin(), des_tracker.end(), code_2) == des_tracker.end());
            }while(!valid || error);

            cout << "\n \n \n";
            calculate(code_1, code_2, dictionary, tracker, false, false);
        }else if (temp == 2){
            do{
                if(!valid)
                    cout << "Invalid input" << endl;
                else if(error){
                    cout << "There are no source destinations of " << code_1 << " in our database. Try another one!";
                }
                cout << "\n \nInput your ***FIRST*** Airport Code (Ex. ORD, ATL, PHX): " << endl;
                cin >> code_1;
                if (code_1 == "quit"){
                    break;
                }
                valid = AirportDistance::checkValid(code_1, airport_data); //Function that checks if given string is valid airport
                error = (std::find(src_tracker.begin(), src_tracker.end(), code_1) == src_tracker.end());
            }while(!valid || error);
            do{
                if(!valid)
                    cout << "Invalid input." << endl;
                else if(error || error2)
                    cout << "There are no arrival destinations of " << code_1 << " in our database. Try another one!";
                cout << "Input your *****SECOND***** Airport Code (Ex. ORD, ATL, PHX): " << endl;
                cin >> code_2;
                valid = AirportDistance::checkValid(code_2, airport_data);
                error = (std::find(src_tracker.begin(), src_tracker.end(), code_2) == src_tracker.end());
                error2 = (std::find(des_tracker.begin(), des_tracker.end(), code_2) == des_tracker.end());
            }while(!valid || error || error2);
            do{
                if(!valid)
                    cout << "Invalid input." << endl;
                else if(error)
                    cout << "There are no arrival destinations of " << code_1 << " in our database. Try another one!";
                cout << "Input your *****THIRD***** Airport Code (Ex. ORD, ATL, PHX): " << endl;
                cin >> code_3;
                valid = AirportDistance::checkValid(code_3, airport_data);
                error = (std::find(des_tracker.begin(), des_tracker.end(), code_3) == des_tracker.end());
            }while(!valid || error);

            calculate_landmark(code_1, code_2, code_3, dictionary, tracker);
        }

    }




    // map<string, map<string, double> >::iterator it;
    // string space = " ";
    // for ( it = dictionary.begin(); it != dictionary.end(); it++ )
    // {
    //     cout << it->first << " :";
    //     map<string, double> :: iterator it2;
    //     for (it2 = it->second.begin(); it2 != it->second.end(); ++it2){
    //         cout << " [";
    //         cout << it2->first;
    //         cout << " : ";
    //         cout << it2->second;
    //         cout << "], ";
    //     }
    //     cout << '\n';
    // }

    return 0;
}
