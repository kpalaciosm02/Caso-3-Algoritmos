#include <iostream>
using namespace std;

#ifndef POINT
#define POINT

class point{
    private:
        float x;
        float y;
        string idPath;
    public:
        point(){
            this->x = 0;
            this->y = 0;
            this->idPath = "";
        }
        point(float _x, float _y, string _idPath){
            this->x = _x;
            this->y = _y;
            this->idPath = _idPath;
        }
        void set_x(float _x){
            this->x = _x;
        }
        void set_y(float _y){
            this->y = _y;
        }
        void set_idPath(string _idPath){
            this->idPath = _idPath;
        }
        float get_x(){
            return this->x;
        }
        float get_y(){
            return this->y;
        }
        string get_idPath(){
            return this->idPath;
        }
        void print(){//prints the data of the object
            if (this != NULL){
                cout << "X: " << x << " Y: " << y<< " Id Path: " << idPath << endl;
            }
        }
};

#endif