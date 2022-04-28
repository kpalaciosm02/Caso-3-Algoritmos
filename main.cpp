#include "main.hpp"
#include "ObserverPattern.h"
#include "path.hpp"
#include "Point.hpp"
#include <vector>

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

/*Function that splits a path in subsections, depending in the given limit. 
This subsections are inserted in a vector and returns this vector*/
vector<string> split(string path, char limit, vector<string> splitted){
    path += limit;
    string tmp = "";
    for (int i = 0; i < path.length(); i++){
        if (path[i] == limit){
            splitted.push_back(tmp);
            tmp = "";
            //i++;
        }
        tmp += path[i];
    }
    return splitted;
}

/*Function that splits a path in subsections, depending in the given array with limits. 
This subsections are inserted in a vector and returns this vector*/
vector<string> splitt_with_array(string path, char limits[18], vector<string> splitted){ //Possible limits: mlhvcsqta
    //path += '$';
    string tmp = "";
    for (int i = 0; i < path.length(); i++){
        for (int j = 0; j < 18; j++){
            if (path[i] == limits[j] || path[i] == '$'){
                splitted.push_back(tmp);
                tmp = "";
            }
            tmp += path[i];
        }
    }
    return splitted;
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

/**/
void takeNumbers(string path){// recibe la d
    int startIndex = 0;
    int finalIndex = 0;
    for (int i = 0; i < path.length(); i++){
        if (path[i] == 'C' || path[i] == 'S' || path[i] == 'M'){
            startIndex = i + 1;
        }
        else if (path[i] == ','){
            finalIndex = i;
            string number = path.substr(startIndex,finalIndex);
            cout << "Numero sacado: " << number << endl;
            //break;
        }
    }
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

/*void RelativeToAbsolute(vector<string> relatives){
    char array_char[] = {'m','l','h','v','c','s','q','t','a'};
    vector<string> splitted = {};
    for(vector<string>::const_iterator i = relatives.begin(); i != relatives.end(); i++){
        string path = *i;
        splitt_with_array(path, array_char, splitted);
    }
}*/

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

void Seleccion(xml_document<>* myDoc, vector<float> points){
    vector<string> absolutes = {};
    vector<string> relatives = {};

    vector<path> pathsS = SeparePathElements(myDoc);
    vector<string> pathsD = SeparatePaths(pathsS);
    checkIfAbsolute(pathsD, absolutes, relatives);
    
}

class AnimationGenerator : public Observer{
public:
    AnimationGenerator(){}
    ~AnimationGenerator(){}
};

class Selection : public Subject{
private:
public:
    Selection(){}
    ~Selection(){}
};

class Routing : public Subject{
private:
public:
    Routing(){}
    ~Routing(){}
};

class Generation : public Subject{
private:
public:
    Generation(){}
    ~Generation(){}
};

int main(){
    //Leer XML
    file<> file("test.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    vector<float> UserPoints = {500, 700, 800, 200, 400, 500, 600, 700, 900, 100, 300, 500};
    vector<string> colors = {"#00008B", "#808080"};
     
    Seleccion(&myDoc, UserPoints);


   /*
    for (vector<path>::const_iterator i = paths.begin(); i != paths.end(); i++){
        path p = *i;
        pathsD.push_back(p.get_d());
    }

    vector<string> splitted = {};
    string valor = "M2868.463,9.696C2111.527,298.25,780.675,781.621,5.718,1048.912C773.331,756.199,2104.345,273.336,2868.463,9.696z";
    splitted = split(valor,'C',splitted);
    cout << "Splitted by C: ";
    /*for (vector<string>::const_iterator i = splitted.begin(); i != splitted.end(); i++){
        cout << *i << " -> ";
    }
    cout << endl;*/

    /*char array_char[] = {'m','l','h','v','c','s','q','t','a'};
    vector<string> splitted2 = splitt_with_array(valor,array_char,splitted2);
    for (vector<string>::const_iterator i = splitted2.begin(); i != splitted2.end(); i++){
        cout << *i << " -> ";
    }*/

    return 0;
}