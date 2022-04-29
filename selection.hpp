#include "Point.hpp"
#include "path.hpp"
#include <vector>
#include "main.hpp"
using namespace std;

/*Function that opens the XML document, extract the data from the XML document,
inserts this data in a vector and returns this vector*/
vector<path> SeparePathElements(xml_document<>* myDoc){
    vector<path> paths;
    xml_node<>* pathXML = myDoc->first_node()->first_node("g");
    for (pathXML = pathXML->first_node(); pathXML != NULL; pathXML = pathXML->next_sibling()){
        string id_value = pathXML->first_attribute("id")->value();
        string opacity_value = pathXML->first_attribute("opacity")->value();
        string direction_value = pathXML->first_attribute("d")->value();

        path p(id_value, opacity_value, direction_value);
        paths.push_back(p);
    }
    return paths;
}

/*Function that gets the d atributte of a path and insert them in a vector and return this vector.*/
vector<string> SeparatePaths(vector<path> paths){
    int counter = 0;
    vector<string> pathsD = {};

    for (vector<path>::const_iterator i = paths.begin(); i != paths.end(); i++){
        path path = paths.at(counter);
        counter++;
        pathsD.push_back(path.get_d());
    }
    return pathsD;
}

/*Function that checks if a path is absolute or relative*/
void checkIfAbsolute(vector<string> paths, vector<string> absolutes, vector<string> relatives){//recibe el vector de paths d y llena los vectores de paths absolutos y relativos
    cout << "Largo absolutos: " << absolutes.size() << " Largo relativos: " << relatives.size() << endl;
    for (vector<string>::const_iterator i = paths.begin(); i != paths.end(); i++){
        string path = *i;
        if (path.find('-') != -1){
            relatives.push_back(path);
        }
        else{
            absolutes.push_back(path);
        }
    }
    cout << "Largo absolutos: " << absolutes.size() << " Largo relativos: " << relatives.size() << endl;
}

/*Function that takes the coords from an absolute path and separe them in vectors of x and y*/
void takeCoordsFromAbsolutePath(string path, vector<float> x, vector<float> y){//agarra un path absoluto y saca todas las x y todas las y y las mete en vectores
    int pathLarge = path.size();//encontrar la manera de sacar estos 2 vectores de la funcion para usarlos luego
    string sNumber = "";
    float fNumber = 0.0;
    bool isX = true;
    for (int i = 0; i < pathLarge; i++){
        if (path[i] == 'M' || path[i] == 'L' || path[i] == 'H' || path[i] == 'V' || path[i] == 'C' || path[i] == 'S' || path[i] == 'Q' || path[i] == 'T' || path[i] == 'A' || path[i] == 'z' || path[i] == ','){
            if (i != 0){
                //cout << "sNumber: " << sNumber << endl;
                fNumber = stof(sNumber);
                if (isX){
                    x.push_back(fNumber);
                    isX = false;
                }
                else{
                    y.push_back(fNumber);
                    isX = true;
                }
                fNumber = 0.0;
                sNumber = "";
            }
            
        }
        else {
            sNumber += path[i];
        }
    }
}

/*Function that determine the max and the min of a serie of absolute points*/
vector<float> MaxAndMin(vector<float> PathPoints){
    float max = PathPoints[0];
    float min = PathPoints[0];
    vector<float> MaxMin = {};

    for(size_t i = 0; i < PathPoints.size() ; i++){
        if(PathPoints[i] > max)
            max = PathPoints[i];
        if(PathPoints[i] < min)
            min = PathPoints[i];
    }
    MaxMin.push_back(min);
    MaxMin.push_back(max);

    return MaxMin;
}

/*Function that compares the points given by the user with the max x, min x, max y, min y of the SVG*/
void compareUserAndSvgPoints(vector<float> MaxMinX, vector<float> MaxMinY, vector<float> points){
    bool isX = true;
    for(size_t i = 0; i < points.size(); i++){
        if(isX){
            if(points[i] > MaxMinX[i] || points[i] < MaxMinX[i+1]){
                isX = false;

            }
        }
        else{
            if(points[i] > MaxMinY[i] || points[i] < MaxMinY[i+1]){
                isX = true;

            }
        }
    }
}