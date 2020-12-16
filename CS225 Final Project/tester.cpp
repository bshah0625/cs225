#include <list>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main(){
    ifstream myfile;
    myfile.open ("dataset_routes.txt");

    //checker list
    list<string> airport_list;

    //opening dataset
    string line;
    int counter = 0;
    if (myfile.is_open()) {
        while ( getline(myfile,line) ){
            counter = 1;
            std::string s = line;
            std::string delimiter = ",";

            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);

                s.erase(0, pos + delimiter.length());
                if (counter == 3 || counter == 5){
                    airport_list.push_back(token);
                }

                counter++;
            }


        }
        myfile.close();

    }

    airport_list.sort();
    airport_list.unique();

    list <string> :: iterator it;
    for (it = airport_list.begin(); it != airport_list.end(); ++it){
        cout << '\t' << *it;
    }
    cout << '\n';


    return 0;


}
