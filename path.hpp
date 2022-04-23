#include <iostream>
using namespace std;

#ifndef PATH
#define PATH

class path{
    private:
        string id;
        string opacity;
        string d;
    public:
        path(){
            this->id = "";
            this->opacity = "";
            this->d = "";
        }
        path(string _id, string _opacity, string _d){
            this->id = _id;
            this->opacity = _opacity;
            this->d = _d;
        }
        void set_id(string _id){
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
        void print(){
            if (this != NULL){
                cout << "ID: " << id << " Opacity: " << opacity << " D: " << d << endl;
            }
        }
};

#endif