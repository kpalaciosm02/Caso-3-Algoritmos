#include "ObserverPattern.h"
#include "selection.hpp"
#include "main.hpp"
#include <tuple>

using namespace std;


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


/*void RelativeToAbsolute(vector<string> relatives){
    char array_char[] = {'m','l','h','v','c','s','q','t','a'};
    vector<string> splitted = {};
    for(vector<string>::const_iterator i = relatives.begin(); i != relatives.end(); i++){
        string path = *i;
        splitt_with_array(path, array_char, splitted);
    }
}*/


vector<path> Seleccion(xml_document<>* myDoc, vector<float> points){
    vector<string> absolutes = {};
    vector<string> relatives = {};
    vector<point> pointsS = {};

    vector<path> pathsS = SeparePathElements(myDoc);
    //aqui se debe cambiar de relativo a absoluto
    vector<string> pathsD = SeparatePaths(pathsS);    //todos los paths D
    vector<string> idPaths = get_ids(pathsS);         //todos los paths ID
    for (vector<string>::const_iterator i = idPaths.begin(); i != idPaths.end(); i++){
        cout << *i << " -> ";
    }
    cout << endl;
    vector<float> xs = {};
    vector<float> ys = {};
    vector<path> pathsAfterSelection = {};
    //pointsS = takeCoordsFromAbsolutePath(pathsD.at(0),idPaths.at(0), pointsS);
    for (int i = 0; i < pathsD.size(); i++){
        pointsS = takeCoordsFromAbsolutePath(pathsD.at(i), idPaths.at(0), pointsS);
        vector<point>MinMaxX = MaxAndMinX(pointsS);
        vector<point>MinMaxY = MaxAndMinY(pointsS);
        pathsAfterSelection = compareUserAndSvgPoints(MinMaxX, MinMaxY, points, pathsS, pathsAfterSelection);
        pointsS = {};
    }
    return pathsAfterSelection;
}

bool IsRelativePath(string path){//returns 1 if the path is relative (true)
    int path_size = path.size();
    for (int i = 0; i < path_size; i++){
        if (path.at(i) == '-')
            return true;
    }
    return false;
}

tuple<float,float> ExtractAbsolutesFromRelativePath(string path){//extracts the first 2 coords from a path
    float AbsoluteX = 0.0;
    float AbsoluteY = 0.0;
    int pathSize = path.size();
    string number = "";
    for (int i = 1; i < pathSize; i++){
        char character = path.at(i);
        if (character == 'c'){
            AbsoluteY = stof(number);
            break;
        }
        else if (character == ','){
            AbsoluteX = stof(number);
            number = "";
        }
        else{
            number += character;
        }    
    };
    return {AbsoluteX,AbsoluteY};
}

string RelativeToAbsolutePath(string path){//Function that recieves a string (relative path) and returns the same path but in its absolute form
    auto [AbsoluteX, AbsoluteY] = ExtractAbsolutesFromRelativePath(path);
    int pathSize = path.size();
    string number = "";// + to_string(AbsoluteX) + to_string(AbsoluteY);
    int startIndex = 0;
    int finalIndex = 0;
    bool firstLetterFound = false;
    string finalPath = "M" + to_string(AbsoluteX) + to_string(AbsoluteY);//esperar a tener svg mas homogeneo
    for (int i = 0; i < pathSize; i++){
        if (!firstLetterFound){
            if (path[i] == 'M')
                firstLetterFound = true;
        }
    }
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
    file<> file("test2.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    vector<float> UserPoints = {600, 300, 800, 300, 400, 500, 600, 700, 900, 100, 300, 500};
    vector<string> colors = {"#00008B", "#808080"};
     
    Seleccion(&myDoc, UserPoints);

    string pathTest = "M4613.561,735.186c-816.044-148.961-2238.165-431.319-3058.823-607.843C2382.307,278.323,3804.335,561.206,4613.561,735.186z";
    auto [AbsoluteX, AbsoluteY] = ExtractAbsolutesFromRelativePath(pathTest);
    cout << "Coordenadas absolutas:" << AbsoluteX << ":" << AbsoluteY << endl;
    cout << IsRelativePath("M593.953,539.108C1437.484,448,2914.226,311.023,3770.424,244.99C2914.896,337.478,1438.109,473.921,593.953,539.108z") << endl;
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
    //hacer funcion que llama con todos los paths (for)
    //calcular ruta de cada punto?
    //ver el video en la parte de enrutamiento
    return 0;
}