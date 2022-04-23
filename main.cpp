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

int main(){
    //Leer XML
    file<> file("test.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    SeparePathElements(&myDoc);

    vector<string> colors = {"#00008B", "#808080"};
    vector<string> points = {};

    //Document to String
    //string strXML;
    //print(back_inserter(strXML), myDoc, 0); //Copia el texto del Document en la variable
    //cout << strXML << endl;

    return 0;
}