#include <vector>
#include "route.hpp"
#include "Point.hpp"
#include <string>
#ifndef GENERATION
#define GENERATION

struct pathGeneration{
    string id;
    string fill;
    string pathP;
};

class Generation{
    protected:
        vector<route> routes;
        int documentCounter;
    public:
        Generation(){
            routes = {};
            documentCounter = 0;
        }
        Generation(vector<route> newRoutes, int counter){
            routes = newRoutes;
            documentCounter = counter;
        }
        void setRoutes(vector<route> newRoutes){
            newRoutes = newRoutes;
        }
        void setCounter(int newCounter){
            documentCounter = newCounter;
        }
        vector<route> getRoutes(){
            return this->routes;
        }
        string generatePath(){
            for(vector<route>::const_iterator i = routes.begin(); i != routes.end(); i++){
                route r = *i;
                vector<point> tmpPoints = r.getRoutePoints();
                string pathP = "M";
                int idCounter = 1;
                bool isFirst = true;
                string id = "_x" + to_string(idCounter);
                idCounter++;
                //cout << "Llegue" << endl;
                for(vector<point>::const_iterator i = tmpPoints.begin(); i != tmpPoints.end(); i++){
                    point pr = *i;
                    //pr.print();
                    float x = pr.get_x();
                    float y = pr.get_y();
                    //cout << x << " " << y << endl;
                    string id = "_x" + to_string(idCounter);
                    string xString = to_string(x);
                    string yString = to_string(y);
                    //cout << xString << " " << yString << endl;
                    if(isFirst){
                        pathP += xString;
                        pathP += ",";
                        pathP += yString;
                        pathP += "C";
                        isFirst = false;
                    }
                    else{
                        pathP += xString;
                        pathP += ",";
                        pathP += yString;
                        pathP += ",";
                    }
                    //cout << "ID:" << id << "Path:" << pathP << endl;
                }
                cout << "ID: " << id; 
                cout << " Path:" << pathP << endl;
            }
            cout << routes.size() << endl;
            return "";
        }
        /*bool generateSVG(){
            string name = "Archivo";
            string counterString = stoi(this->documentCounter);
            name += counterString;
            return true;
        }*/
};

#endif