#include <vector>
#include "route.hpp"
#include "Point.hpp"
#include <string>
#include <fstream>
//#include "tinyxml2-master/tinyxml2.h"
//using namespace tinyxml2;
#ifndef GENERATION
#define GENERATION

struct pathGeneration{
    string id;
    string opacity;
    string pathP;
};

class Generation{
    protected:
        vector<route> routes;
        int documentCounter;
    public:
        Generation(){
            routes = {};
            documentCounter = 1;
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
        void incCounter(){
            documentCounter++;
        }
        vector<route> getRoutes(){
            return this->routes;
        }
        vector<pathGeneration> generatePath(){
            int idCounter = 1;
            vector<pathGeneration> paths;
            for(vector<route>::const_iterator i = routes.begin(); i != routes.end(); i++){
                route r = *i;
                vector<point> tmpPoints = r.getRoutePoints();
                
                string pathP = "M";
                bool isFirst = true;
                string id = "_x" + to_string(idCounter);
                idCounter++;
                for(vector<point>::const_iterator i = tmpPoints.begin(); i != tmpPoints.end(); i++){
                    point pr = *i;
                    float x = pr.get_x();
                    float y = pr.get_y();
                    string id = "_x" + to_string(idCounter);
                    string xString = to_string(x);
                    string yString = to_string(y);
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
                }
                pathP = pathP.substr(0,pathP.size()-1);
                //cout << "ID:" << id << "Path:" << pathP << endl;
                pathGeneration path;
                path.id = id;
                path.opacity = "0.502";
                path.pathP = pathP;
                paths.push_back(path);
            }
            return paths;
        }
        string generateSVGName(string name){//function that recieves the svg name and add the counter to it. F.e: test.svg->test1.svg
            name = name.substr(0,name.size()-4);
            string counterString = to_string(this->documentCounter);
            name = name + counterString + ".svg";
            cout << name << endl;
            return name;
        }
        void generateSVG(string name, vector<pathGeneration> paths){
            string fileName = generateSVGName(name);
            //incCounter();
            //ofstream MyFile(fileName);
            //MyFile.close();
            xml_document<> doc;
            xml_node<>* dec1 = doc.allocate_node(node_declaration);
            dec1->append_attribute(doc.allocate_attribute("version","1.0"));
            dec1->append_attribute(doc.allocate_attribute("encoding","utf-8"));
            doc.append_node(dec1);

            xml_node<>* root = doc.allocate_node(node_element,"svg");
            root->append_attribute(doc.allocate_attribute("version","1.1"));
            root->append_attribute(doc.allocate_attribute("id","Layer_1"));
            root->append_attribute(doc.allocate_attribute("xmlns","http://www.w3.org/2000/svg"));
            root->append_attribute(doc.allocate_attribute("xmlns:xlink","http://www.w3.org/1999/xlink"));
            root->append_attribute(doc.allocate_attribute("x","opx"));
            root->append_attribute(doc.allocate_attribute("y","opx"));
            root->append_attribute(doc.allocate_attribute("viewBox","0 0 5011.389 4110.461"));
            root->append_attribute(doc.allocate_attribute("enable-background","new 0 0 5011.389 4110.461"));
            root->append_attribute(doc.allocate_attribute("xml:space","preserve"));
            doc.append_node(root);

            xml_node<>* child = doc.allocate_node(node_element,"g");
            for (int i = 0; i < paths.size(); i++){
                xml_node<>* currentPath = doc.allocate_node(node_element,"path");
                pathGeneration pathi = paths.at(i);
                cout << "ID: " << pathi.id << "    Path: " << pathi.pathP << endl;
                //cout << pathi.id.c_str() << endl;
                currentPath->append_attribute(doc.allocate_attribute("id",pathi.id.c_str()));
                currentPath->append_attribute(doc.allocate_attribute("opacity",pathi.opacity.c_str()));
                currentPath->append_attribute(doc.allocate_attribute("d",pathi.pathP.c_str()));
                child->append_node(currentPath);
            }
            root->append_node(child);

            ofstream file_stored(fileName);
            file_stored << doc;
            file_stored.close();
            doc.clear();
            incCounter();
        }
};

#endif