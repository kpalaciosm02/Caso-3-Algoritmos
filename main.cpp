#include "main.hpp"
#include "ObserverPattern.h"
#include "path.hpp"
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

vector<string> splitt_with_array(string path, char limits[18], vector<string> splitted){ //Possible limits: mlhvcsqta
    path += '$';
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

void Seleccion(xml_document<>* myDoc, vector<string> points, vector<string> colors){
    SeparePathElements(myDoc);
    
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

void SeparatePaths(vector<path> paths){
    int counter = 0;
    vector<string> pathsM = {};
    vector<string> pathsC = {};

    for (vector<path>::const_iterator i = paths.begin(); i != paths.end(); i++){
        path path = paths.at(counter);
        counter++;
        string d = path.get_d();
    }
}

int main(){
    //Leer XML
    file<> file("test.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    vector<path> paths = SeparePathElements(&myDoc);

    vector<string> colors = {"#00008B", "#808080"};
    vector<string> points = {};

    vector<string> splitted = {};
    string valor = "M2868.463,9.696C2111.527,298.25,780.675,781.621,5.718,1048.912C773.331,756.199,2104.345,273.336,2868.463,9.696z";
    splitted = split(valor,'C',splitted);
    cout << "Splitted by C: ";
    for (vector<string>::const_iterator i = splitted.begin(); i != splitted.end(); i++){
        cout << *i << " -> ";
    }
    cout << endl;

    char array_char[] = {'m','l','h','v','c','s','q','t','a'};
    vector<string> splitted2 = splitt_with_array(valor,array_char,splitted2);
    for (vector<string>::const_iterator i = splitted2.begin(); i != splitted2.end(); i++){
        cout << *i << " -> ";
    }
    cout << endl;

    //Document to String
    //string strXML;
    //print(back_inserter(strXML), myDoc, 0); //Copia el texto del Document en la variable
    //cout << strXML << endl;

    return 0;
}