#include "main.hpp"
#include "ObserverPattern.h"

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
    file<> file("logo_bluetooth.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    extractXMLData(&myDoc);

    return 0;
}