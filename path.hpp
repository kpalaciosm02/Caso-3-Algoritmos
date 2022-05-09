#include <iostream>
using namespace std;

#ifndef PATH
#define PATH

class path{
    //class for saving the svg's paths
    private:
        string id;
        string fill;
        string d;
    public:
        path(){//Constructor method
            this->id = "";
            this->fill = "";
            this->d = "";
        }
        path(string _id, string _fill, string _d){//constructor method with paramethers
            this->id = _id;
            this->fill = _fill;
            this->d = _d;
        }
        void set_id(string _id){//setters and getters
            this->id = _id;
        }
        void set_fill(string _fill){
            this->fill = _fill;
        }
        void set_d(string _d){
            this->d = _d;
        }
        string get_id(){
            return this->id;
        }
        string get_fill(){
            return this->fill;
        }
        string get_d(){
            return this->d;
        }
        void print(){//prints the data of the object
            if (this != NULL){
                cout << "ID: " << id << " Fill: " << fill << " D: " << d << endl;
            }
        }
};

#endif