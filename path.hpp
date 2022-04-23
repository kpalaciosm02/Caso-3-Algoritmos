#include <iostream>
using namespace std;

#ifndef PATH
#define PATH

class path{
    //class for saving the svg's paths
    private:
        string id;
        string opacity;
        string d;
    public:
        path(){//Constructor method
            this->id = "";
            this->opacity = "";
            this->d = "";
        }
        path(string _id, string _opacity, string _d){//constructor method with paramethers
            this->id = _id;
            this->opacity = _opacity;
            this->d = _d;
        }
        void set_id(string _id){//setters and getters
            this->id = _id;
        }
        void set_opacity(string _opacity){
            this->opacity = _opacity;
        }
        void set_d(string _d){
            this->d = _d;
        }
        string get_id(){
            return this->id;
        }
        string get_opacity(){
            return this->opacity;
        }
        string get_d(){
            return this->d;
        }
        void print(){//prints the data of the object
            if (this != NULL){
                cout << "ID: " << id << " Opacity: " << opacity << " D: " << d << endl;
            }
        }
};

#endif