

#pragma once


#include<iostream>
#include <utility> // for std::move
#include<vector>
#include<fstream>
#include <cctype>
#include<cstring>
#include<string>
#include "Location.h"


using namespace std;

class Map {


private:

    int width{}, height{}; 

    vector<vector<Location>> locations; 

    char start{}, end{}; 

    int start_X{}, start_Y{}, end_X{}, end_Y{}; 

    bool Loaded{false}, pathFounded{false}; 



public:
    Map(int w, int h, vector<vector<Location>> vec_locations) : width{w}, height{h}, locations{std::move(vec_locations)} {}
    //use move to copy vector 


   explicit Map()= default;
     // explicit keyword mentioned to avoid implicit conversion
    explicit Map(const string& fileName) { 

        ifstream in(fileName);

        if (in.fail()) {
            cout << "error: map file not found" << endl;

        }

        else {



            string str1, str2, str3;// take 3 rows at a time and analyze
            getline(in, str1);//the dashed line above( the dashes)
            getline(in, str2);// the line having characters 
            getline(in, str3);//the dashed line below


            int line = 0;
int cell = 0;
            while (!in.eof()) {  //move down 3 at a time till eof
cell = 0;
                int i = 0, j = 0, k = 1;
                char name = ' ';


                vector<Location> vec_location;

                while (i < str1.size() - 1) {  //iterate through that row till size of line

                    Location location;

                    location.setX(line);//to set row
                    location.setY(cell);//to set col

                    if (str1[i] == '+')
                        i++; // new path

                    if (str1[i] == '-')
                        location.setAbove(false);
                    else if (str1[i] == ' ')
                        location.setAbove(true);

                    else
                        cout << "error evaluation above at line = " << line <<"  cell = " << cell << endl;


                    i = i + 3; // path left as each dash --- is length 3

                    if (str2[j] == '|')
                        location.setLeft(false);
                    else if (str2[j] == ' ')
                        location.setLeft(true);
                    else
                        cout << "error evaluation left"<< line <<"  cell = " << cell  << endl;


                    j = j + 2; // cost  , this is where letter would be 

                    if (str2[j] != ' ') 

                        if (isdigit(str2[j]))    //digit
                            location.setCost(str2[j] - '0');

                        else {//char
                            location.setCost(0);//location.setCost(1);
                            location.setName(str2[j]);
                        }
                    else location.setCost(0);//blank

                    j = j + 2; //path right, now head to start of new cell at right in row containing letters

                    if (str2[j] == '|') location.setRight(false);
                    else if (str2[j] == ' ') location.setRight(true);
                    else
                        cout << "error evaluation right"<< line <<"  cell = " << cell  << endl;


                    //path below
                    if (str3[k] == ' ') location.setBelow(true);
                    else if (str3[k] == '-') location.setBelow(false);
                    else
                        cout << "error evaluation below" << line <<"  cell = " << cell << endl;


                    k = k + 4; // wall below  , move to next col

                    vec_location.push_back(location); // push in vector<Location>
                    cell++; // increment cell
                }

                line++;   // increment line

                str1 = str3;// now look at next 3 lines 
                getline(in, str2);
                getline(in, str3);
                   //locations is the  name of vector containing all locations
                this->locations.push_back(vec_location);  // pushing vector<Location> to member variable vector<vector>Location>>  , 
				//this is done for every set of 3 rows to get 2d vector , with each vector inside locations corresponding to a vector for each 3 row



            }

            width = cell;
            height = line;

            Loaded = true;
            pathFounded = false;

        }


    }













    void setLocationsUnvisited(){

        for(auto & location : locations){
            for(auto & j : location){

                j.setVisited(false);

            }
        }
    }


    void setStart(){

        char start_char;
        bool found = false;

        do {   
            cout << "\n\n\n\n		please enter start location     :    " ;
            cin >> start_char;

            bool same = start_char == end;
            if(same){
                cout << "\n\n\n       start and end co-ordinates cannot be same!\n\n" << endl;

                     }  

            for(int i  = 0 ; i < locations.size() && !found && !same; i++){  
			//loop to check if there exsists an entered location exsists on map wiith that name , and if so, set it as start location
                for(int j = 0 ; j < locations[i].size(); j++){

                    if( locations[i][j].getName() == start_char){

                        start_X = i; // line/row
                        start_Y = j; // cell/col
                        start = locations[i][j].getName();

                        found = true;
                    }

                }

            }
        }
        while(!found);

    }

    void setEnd(){

        char end_char;
        bool found = false;


        do {
            cout << "\n\n\n\n		please enter destination location    :   " ;
            cin >> end_char;

            bool same = end_char == start;
            if(same){
                cout << "\n\n		start and end co-ordinates cannot be same!    \n\n" << endl;

            }

            for(int i  = 0 ; i < locations.size() && !found && !same; i++){
                for(int j = 0 ; j < locations[i].size(); j++){

                    if(end_char == locations[i][j].getName()){

                        end_X = i; // line
                        end_Y = j; // cell
                        end = locations[i][j].getName();

                        found = true;
                    }

                }

            }


        }
        while(!found);
    }




    char getStart() const{
        return start;
    }



    char getEnd() const{
        return end;
    }

    int getStartX() const {
        return start_X;
    }

    int getStartY() const{
        return  start_Y;
    }



    void setEndX(int x)  {
        end_X = x;
    }

    void setEndY(int y) {
        end_Y = y;
    }


    void setStartX(int x) {
        start_X = x;
    }

    void setStartY(int y){
        start_Y = y;
    }



    int getEndX() const {
        return end_X;
    }

    int getEndY() const{
        return  end_Y;
    }





    int getWidth() const {

        return width;


    };

    int getHeight() const {

        return height;

    };


    int setWidth(int w) {

        width = w;


    };

    int setHeight(int h) {

        height = h;

    };


    vector<vector<Location>> getLocations() const {

        return locations;


    }


    void setLocations(vector<vector<Location>> vec_vec_locations)  {

        locations = std::move(vec_vec_locations);

    }




    void setCost(int x, int y, int cost){
        locations[x][y].setCost(cost);

    }

    bool getLoaded ()const
    {

        return Loaded;
    }

    void setLoaded(bool boolean){

        Loaded = boolean;
    }

    bool getPathFounded ()const
    {

        return pathFounded;
    }

    void setPathFounded(bool boolean){

        pathFounded = boolean;
    }


   
    void setVisitedAt(int x, int y, bool boolean){

        locations[x][y].setVisited(boolean);

    }

   
    void setParentsAt(int x, int y, int X_coord, int Y_coord) {

        locations[x][y].setParentX(X_coord);
        locations[x][y].setParentY(Y_coord);

    }



    void setHasParents(int x, int y, bool Boolean){
        locations[x][y].setHasParents(Boolean);

    }



    void setNameAt(int x, int y, char obj){
        locations[x][y].setName(obj);

    }




    

    void zeroCostPaths(){

        for( auto& line: locations){
            for(auto& cell: line){

                    cell.setCost(0);
           }
        }

    }


 Location& operator () (const int line, const int cell)
    {

            return locations[line][cell];

    }


  const  Location& operator () (const int line, const int cell) const
    {

        return locations[line][cell];

    }



};




