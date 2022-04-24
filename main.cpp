#include "main.hpp"
#include "ObserverPattern.h"
#include <typeinfo>

using namespace std;

//Recorre el elemento raíz del documento
void extractXMLData(xml_document<>* doc){
    xml_node<>* node = doc->first_node();

    cout << "Etiqueta: " << node->name() << endl;
    for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
        cout << " Atributo: " << attrib->name() << endl;
        cout << "\tValor: " << attrib->value() << endl;
  }
    extractNodeData(node);
}

//Recorre el resto de elementos del documento
void extractNodeData(xml_node<>* node){
    for (node = node->first_node(); node != NULL; node = node->next_sibling()){
        if (node->type() == node_element){
            cout << "Etiqueta: " << node->name() << endl;

            for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
                cout << "\tAtributo: " << attrib->name() << endl;
                cout << "\t-Valor: " << attrib->value() << endl;
            }

            extractNodeData(node);
        }
    }
}

void SeparePathElements(xml_document<>* myDoc){
    xml_node<>* path = myDoc->first_node()->first_node("g");
    for (path = path->first_node(); path != NULL; path = path->next_sibling()){
        cout << "Nombre:" << typeid(path->name()).name() << endl;
        xml_attribute<>* direction = path->first_attribute("d");
        cout << "Atributo: " << direction->name() << endl;
        cout << "Valor: " << direction->value() << endl;
    }
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

void Seleccion(){

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

    vector<string> splitted = {};
    string valor = "M2868.463,9.696C2111.527,298.25,780.675,781.621,5.718,1048.912C773.331,756.199,2104.345,273.336,2868.463,9.696z";
    splitted = split(valor,'C',splitted);
    cout << "Splitted by C: ";
    for (vector<string>::const_iterator i = splitted.begin(); i != splitted.end(); i++){
        cout << *i << " -> ";
    }
    cout << endl;
    //Document to String
    //string strXML;
    //print(back_inserter(strXML), myDoc, 0); //Copia el texto del Document en la variable
    //cout << strXML << endl;

    return 0;
}