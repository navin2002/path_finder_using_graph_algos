
#pragma once
#include<vector>
#include<string>



class Location{
private:
    int x_coord, y_coord, parentX, parentY;  

    int cost; 

    bool above, below, left, right; 

    bool isVisited, hasParents;   

    char name;



public:

    Location() :  x_coord{-1}, y_coord{-1}, parentX{-1},parentY{-1}, cost{-1}, 

                  above{false}, below{false}, left{false}, right{false}, 

                  isVisited{false}, hasParents{false}, 

                  name{' '} {};




    Location(int x, int y) : x_coord{x}, y_coord{y},

    parentX{-1},parentY{-1}, cost{-1}, 

    above{false}, below{false}, left{false}, right{false}, 

    isVisited{false}, hasParents{false}, 

    name{' '} {};









  friend std::ostream& operator<<( std::ostream& os, Location location) {


        os << "(" << location.x_coord + 1<< "," <<location.y_coord + 1<< ")\t";

        return os;


    }







    bool getAbove()const{
        return above;

    }

    void setAbove ( bool a) {

        above = a;
    };


    bool getBelow()const{
        return below;

    }


    void setBelow ( bool b) {

        below = b;
    };



    bool getLeft()const{

        return left;

    }

    void setLeft ( bool l) {

        left = l;
    };


    bool getRight()const{
        return right;

    }
    void setRight ( bool r) {

        right = r;
    };




    void setName(char c){

        name = c;

    }

    char getName() const{
        return name;
    }


    int getCost() const{
        return cost;
    }

    void setCost(int c) {
        cost = c;
    }



   
    int getX() const{
        return x_coord;
    }

    void setX(int x) {
        x_coord = x;
    }


    int getY() const{
        return y_coord;
    }

    void setY(int y) {
        y_coord = y;
    }



    int getParentX()const {
        return parentX;
    }
    void setParentX(int x) {
        parentX = x;
    }


    int getParentY() const {
        return parentY;
    }
    void setParentY(int y) {
        parentY = y;
    }



    int getVisited()const {
        return isVisited;
    }
    void setVisited(bool boolean) {
        isVisited = boolean;
    }


    bool getHasParents() const{
        return hasParents;
    }

    void setHasParents(bool boolean){
        hasParents = boolean;
    }





};




