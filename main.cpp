#include "ObserverPattern.h"
#include "selection.hpp"

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


void Seleccion(xml_document<>* myDoc, vector<float> points){
    vector<string> absolutes = {};
    vector<string> relatives = {};

    vector<path> pathsS = SeparePathElements(myDoc);
    vector<string> pathsD = SeparatePaths(pathsS);    //todos los paths D
    vector<string> idPaths = get_ids(pathsS);         //todos los paths ID
    //checkIfAbsolute(pathsD, absolutes, relatives);
    for (vector<string>::const_iterator i = idPaths.begin(); i != idPaths.end(); i++){
        cout << *i << " -> ";
    }
    cout << endl;
    vector<float>xs = {};
    vector<float>ys = {};
    //takeCoordsFromAbsolutePath(pathsD.at(1),idPaths.at(1));
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