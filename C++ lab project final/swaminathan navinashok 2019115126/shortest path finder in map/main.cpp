
#include <iostream>
#include<stack>
#include<queue>
#include<vector>
#include<string>
#include "Map.h"

using std::cout; using std::cin;
using std::endl;




void printMap(const Map& m)
{

int height = m.getHeight();
int width = m.getWidth();

    for(int line = 0; line < height; line++){   //row by row

        bool start = m.getStart() == m(line, 0).getName(), end = m.getEnd() == m(line, 0).getName();

         cout<<"				";
        if (!m(line, 0).getAbove()) {
            cout << "+---+";
            
        } else {
            cout << "+   +";
        }
            // base 1 cell for that row

        for(int cell = 1; cell  < width; cell++) {//remaining cells in that row


            if (!m(line, cell).getAbove()) {
                cout << "---+";
            } else {
                cout << "   +";
            }

        }

        cout << endl;


        if(start) {  //if start vertex is in first col
             cout<<"				";
            if (!m(line, 0).getLeft()) {
                cout << "|(";
            } else {
                cout << "( ";
            }

            if (m(line, 0).getCost() != 0) {
                cout <<  m(line, 0).getCost();
            } else {
                cout << m(line, 0).getName();
            }


            if (!m(line, 0).getRight()) {
                cout << ")|";
            } else {
                cout << ") ";
            }

        }


        if(end){  //if end vertex is in first col
          cout<<"				";
            if (!m(line, 0).getLeft()) {
                cout << "|{";
            } else {
                cout << "{ ";
            }

            if (m(line, 0).getCost() != 0 ) {
                cout << m(line, 0).getCost();
            } else {
                cout << m(line, 0).getName();
            }

            if (!m(line, 0).getRight()) {
                cout << "}|";
            } else {
                cout << "} ";
            }
            


        }


        if(!start and !end){
            cout<<"				";
            if (!m(line, 0).getLeft()) {
                cout << "| ";
              
            } else {
                cout << "  ";
                
            }

            if (m(line, 0).getCost() != 0) {
                cout << m(line, 0).getCost();
            } else {
                cout << m(line, 0).getName();
            }

            if (!m(line, 0).getRight()) {
                cout << " |";
            } else {
                cout << "  ";
            }
        }


        for(int cell = 1; cell  < width; cell++) {

            start = m.getStart() == m(line, cell).getName();
            end = m.getEnd() == m(line, cell).getName();

            if(start){  //start vertex in any other col other than 0
                if (m(line, cell).getCost() != 0) {
                    cout << "(" << m(line, cell).getCost();
                } else {
                    cout << "(" << m(line, cell).getName();
                }

                if (!m(line, cell).getRight()) {
                    cout << ")|";
                } else {
                    cout << ") ";
                }

            }


            if(end){  //end vertex in any col other than 0

                if (m(line, cell).getCost() != 0) {
                    cout << "{" << m(line, cell).getCost();
                } else {
                    cout << "{" << m(line, cell).getName();
                }

                if (!m(line, cell).getRight()) {
                    cout << "}|";
                } else {
                    cout << "} ";
                }


            }
            if(!start and !end) {

                if (m(line, cell).getCost() != 0) {
                    cout<< " " << m(line, cell).getCost();
                } else {
                    cout << " " << m(line, cell).getName();
                }

                if (!m(line, cell).getRight()) {
                    cout << " |";
                } else {
                    cout << "  ";
                }
            }
        }

        cout << endl;



    }
    

    if(!m(height - 1, 0).getBelow()){
    	//last row,first col
        cout<<"				";
        cout << "+---+"; 
    }
    else{
        cout << "+   +";
    }


    for(int cell = 1; cell < width; cell++){
         //last row , any col other than first col
        if(!m(height - 1, cell).getBelow()){

            cout << "---+";
        }
        else{
            cout << "   +";
        }


    }
    cout << endl << endl;
    

}


struct compareLocations { // defining the comparison operator
    bool operator() (Location const& l1, Location const& l2) {
        return l1.getCost() > l2.getCost();
    }
};







void PrintCoordinates(Location loc, Map & m, int x, int y){ //called frpm sucess which in turn was called from search path
  
    if(x == m.getStartX() and y == m.getStartY()) { // ensures start co-ordinate is printed
           cout<<"\n\n\n        Shortest path    :      ";cout << m(x, y).getName() <<m(x, y);  
		   //() is overloaded for map objject m,    where m(x,y) returns location object , << is overloaded for location object
        return;
    }



    PrintCoordinates(m(loc.getParentX(), loc.getParentY()), m, loc.getParentX(), loc.getParentY());

m(x, y).getName()!= ' ' and  m(x, y).getName()!= '.' ?   cout << m(x, y).getName() <<m(x, y) : cout << m(x, y);
/* if the location has a Name like A, B. then print it otherwise don't*/

}

void Failure(){  //used in both Djikstra and searchPath


    cout << "could not find a path from start to destination" << endl;
}

void success(Location loc, Map& m){ //called from searchpath
     //in the beginning this is the end location
    int currentX = loc.getX();
    int currentY = loc.getY();

 PrintCoordinates(loc, m, currentX, currentY); 

    while(currentY != m.getStartY() or currentX != m.getStartX()){ // loops till start Location


        /*
           // if you want to replace chars other than start and end in path  with 'o' in search  path 
        if(loc.getEnd()!=loc.getName())
        {
             m.setNameAt(currentX, currentY, 'o');  // it is set to 'o'
            cout<<"\n\n\n\n";
            printMap(m);
        
          }
          
        
        */
		
		if(loc.getName() == '.' ) { // if the name is '.'   
            m.setNameAt(currentX, currentY, 'o');  // it is set to 'o'
            cout<<"\n\n\n\n";
            printMap(m);
        }

        currentX = loc.getParentX();  // x is now parent x
        currentY = loc.getParentY(); // y is parent y
        loc = m(currentX, currentY);  // loc = parent loc


    }

    m.setPathFounded(true);  // set path found to true to print
    cout << endl << endl;
}





/*used in searchPath Function*/
template <class T>  //T: location
T& top(std::stack<T>& s) { return s.top(); } // returns the top of a stack

template <class T>  //T: location
T& top(std::queue<T>& q) { return q.front(); } // returns the front of a queue








template<class T>  // T IS STACK<LOCATION> OR QUEUE<LOCATION>
bool SearchPath(Map& m){ 

    T LocationContainer;

    LocationContainer.push(m(m.getStartX(), m.getStartY()));//overloaded paranthesis to return location object

    Location currentNode; 


    while(!LocationContainer.empty()){  // until it is empty, i.e all nodes visited
        currentNode = top(LocationContainer);//custom funct top
        /* currentNode is top of a stack in DFS or front of a queue in BFS*/


        int  x = currentNode.getX();
        int  y = currentNode.getY();

        LocationContainer.pop();  // pop the top or front.

        if(x == m.getEndX() and y == m.getEndY()){ // if we have reached the end, call the success function and return true

            success(currentNode, m);

            return true;

        }

        if(m(x, y).getName() == ' '){
            // if name is a blank space, make it a '.', I preferred not to make Locations like A, B, C into '.'

            m.setNameAt(x, y, '.');
            cout<<"\n\n\n\n";
            printMap(m);

        }


        if(currentNode.getBelow() and  !m(x + 1, y).getVisited()){  // check if below is accessible and if its not visited

            m.setParentsAt(x + 1, y, x, y);      // set parent of location_below to current node

            m.setHasParents(x + 1, y, true);       // set hasParents for location_below to true

            LocationContainer.push(m(x + 1, y));   // push the location_below to Container



        }
        if(currentNode.getRight() and !m(x,y + 1).getVisited()){   // same algorithm for below, except for right
            m.setParentsAt(x, y + 1, x, y);
            m.setHasParents(x, y + 1, true);
            LocationContainer.push(m(x,y + 1));


        }
        if(currentNode.getLeft() and !m(x ,y - 1).getVisited()){ // same algorithm for below, except for left


            m.setParentsAt(x, y - 1, x, y);
            m.setHasParents(x, y - 1, true);
            LocationContainer.push(m(x ,y - 1));

        }

        if(currentNode.getAbove() and !m(x-1,y).getVisited()){ // same algorithm for below, except for above


            m.setParentsAt(x- 1, y, x, y);
            m.setHasParents(x - 1, y, true);
            LocationContainer.push(m(x-1,y));


        }

        m(x, y).setVisited(true);  // set the current node to visited


    }


    Failure();
    return false;

}



/*Djikstras Functions*/

void successDjikstra(Location loc, Map& m){


    int currentX = loc.getX();
    int currentY = loc.getY();
    int totalCost = 0; // total cost value



    PrintCoordinates(loc, m, currentX, currentY); // print the co-ordinates

    while(currentY != m.getStartY() or currentX != m.getStartX()){
        if(loc.getName() == ' ' or loc.getName() == '.') {
            m.setNameAt(currentX, currentY, m(currentX, currentY).getCost() + '0');
         
            // makes the cost of the location, the name. if at (2, 1) has cost is 1 and name of ' ' now it will have a name of '1'
        }
        totalCost += m(currentX, currentY).getCost(); 

        currentX = loc.getParentX();
        currentY = loc.getParentY();
        loc = m(currentX, currentY);

    }
    
    cout<<"\n\n\n		total cost/toll gate tax sum  : (assuming no toll gate is present if cost not specified )  =    "<<totalCost;
    m.setPathFounded(true);
    m.zeroCostPaths(); // making the cost of every other path 0 to print '.' and ' '. Print function prints;

}

bool searchDjikstra(Map& m){
   
    priority_queue<Location, vector<Location>, compareLocations> locationQueue;


    locationQueue.push(m(m.getStartX(), m.getStartY()));

    Location currentNode;

    while(!locationQueue.empty()){

        currentNode = locationQueue.top();


        int   x_currentNode = currentNode.getX();
        int   y_currentNode = currentNode.getY();

        m.setVisitedAt(x_currentNode, y_currentNode, true); // set current node to visited

        locationQueue.pop();// returns min cost node so far

        if(x_currentNode == m.getEndX() and y_currentNode == m.getEndY()){

            successDjikstra(currentNode, m);
            return true;

        }

        if(m(x_currentNode,y_currentNode).getName() == ' '){

            m.setNameAt(x_currentNode, y_currentNode, '.');
            

        }

        if(currentNode.getBelow() and  !m(x_currentNode + 1, y_currentNode).getVisited()){

            m.setParentsAt(x_currentNode + 1, y_currentNode, x_currentNode, y_currentNode);

            m.setHasParents(x_currentNode + 1, y_currentNode, true);

            locationQueue.push(m(x_currentNode + 1, y_currentNode));// rearranged by priority queue to give min cost at top



        }

        if(currentNode.getLeft() and !m(x_currentNode, y_currentNode - 1).getVisited()){

            m.setParentsAt(x_currentNode, y_currentNode - 1, x_currentNode, y_currentNode);
            m.setHasParents(x_currentNode, y_currentNode - 1, true);
            locationQueue.push(m(x_currentNode, y_currentNode - 1));

        }
        if(currentNode.getRight() and !m(x_currentNode,y_currentNode+ 1).getVisited()){
            m.setParentsAt(x_currentNode, y_currentNode+ 1, x_currentNode,y_currentNode);
            m.setHasParents(x_currentNode, y_currentNode + 1, true);
            locationQueue.push(m(x_currentNode,y_currentNode + 1));


        }

        if(currentNode.getAbove() and !m(x_currentNode- 1, y_currentNode).getVisited()){


            m.setParentsAt(x_currentNode- 1, y_currentNode, x_currentNode,y_currentNode);
            m.setHasParents(x_currentNode - 1, y_currentNode, true);
            locationQueue.push(m(x_currentNode - 1,y_currentNode));


        }


    }


    Failure(); // calls the failure function
    return false;

}

void loadMap(Map& m){

    string fileName;
 
    cout << "\n\n\n\n\n			please enter filename (with extension)    :       ";
cin >> fileName;

    m = Map{fileName};

    m.getLoaded() ? cout << "\n\n\n\n        loaded successfully\n\n   " : cout << "\n\n\n\n        failed to load map, check filename\n\n   ";
    cout << endl << endl;


}

void DisplayPath(Map& m){

    if (m.getPathFounded()) {
    	cout<<"\n\n\n\n";
        printMap(m);
    } else {
        cout << "error: no path was found" << endl << endl;
    }


}

void optionsMenu(int & choice)  {



       

        cout
                << "\n\n\n\n\n\n		1)Load Map"
                << "\n\n\n		2)Display Map"
                << "\n\n\n		3)Set Start"
                << "\n\n\n		4)Set Goal"
                << "\n\n\n		5)Find a Path with Depth First Search   (note : DFS doesnt give shortest paths )"
                << "\n\n\n		6)Find Shortest Path with Breadth First Search"
                << "\n\n\n		7)Find Path with minimum total toll gate cost with Dijikstra's algorithm "
                << "\n\n\n		8)Display Path"
                << "\n\n\n		0)Quit"
				<< "\n\n\n\n\n			Please select an option   :      " ;
                
        cin >> choice;
        cout<<"\n\n\n\n";







}

int main() {
 system("Color 4F");

    int choice = -1;
    Map m;




    while(choice != 0){


        optionsMenu(choice);


        switch (choice) {
        	case 0:break;

            case 1:{


 loadMap(m);


    break;
            }


            case 2: {
            
        if(!m.getLoaded()){ // check if map is loaded before attempting to print.
            cout << "\n\n\n      map is not loaded " << endl;
        }


        else {
        	cout<<"\n\n\n\n";
    printMap(m);
            }


break;

            }


            case 3: {

                if(!m.getLoaded()){
                    cout << "\n\n      map is not loaded  " << endl;
                }               else {

                    if(m.getPathFounded()) {

                    cout << "\n\n      please reload the map" << endl;
                    }

                    else {
                        m.setStart();
                    }
                }
            break;

            }


            case 4: {

                if(!m.getLoaded()){
                    cout << "\n\n     map is not loaded " << endl;
                }

                else {

                    if(m.getPathFounded()) {

                        cout << "\n\n     please reload the map" << endl;
                    }
else {
                        m.setEnd();
                    }
                }
                break;

            }


            case 5: {
        if(!m.getLoaded() xor m.getPathFounded()){

    cout << "\n\n      please load/reload the map: " << endl;
        }

        else {

            if (!m.getStart()) {

                cout << "\n\n\n   please select a start value!" << endl;
                m.setStart();
            }

            if (!m.getEnd()) {
                cout << "\n\n\n     please select a end value!" << endl;
                m.setEnd();

            }

              cout<<"\n\n\n\n\t      ";
            SearchPath<stack<Location>>(m);
              cout<<"\n\n\n\n      ";
        }

            }
            break;


            case 6: {

                if(!m.getLoaded() xor m.getPathFounded()){
 
                    cout << "\n\n      please load/reload the map: " << endl;
                }
                else {


                    if (!m.getStart()) {

                        cout << "\n\n    please select a start value!" << endl;
                        m.setStart();
                    }

                    if (!m.getEnd()) {
                        cout << "\n\n     please select a end value!" << endl;
                        m.setEnd();

                    }

                      cout<<"\n\n\n\n\t      ";
                    SearchPath<queue<Location>>(m);
                     cout<<"\n\n\n\n      ";
                }
                break;
            }


            case 7: {

                if(!m.getLoaded() xor m.getPathFounded()){
                    cout << "\n\n     please load/reload the map!" << endl;
                }
                else{

                    if (!m.getStart()) {

                        cout << "\n\n     please select a start value!";
                        m.setStart();
                    }

                    if (!m.getEnd()) {
                        cout << "\n\n     please select a end value!";
                        m.setEnd();

                    }
                     cout<<"\n\n\n\n\t    ";
                    searchDjikstra(m);
                     cout<<"\n\n\n\n      ";
                }
                break;
            }


            case 8: {
            DisplayPath(m);

                break;
            }
           

            default: {

                cout << "\n\n     incorrect option chosen...." << endl;
                break;
            }
        }


    }
    return 0;
}
