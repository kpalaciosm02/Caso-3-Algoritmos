#include "ObserverPattern.h"
#include "selection.hpp"
#include "routing.hpp"
#include "main.hpp"
#include <tuple>

using namespace std;

int main(){
    //Leer XML
    file<> file("test2.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    vector<float> UserPoints = {600, 300, 800, 300, 400, 500, 600, 700, 900, 100, 300, 500};
    vector<string> colors = {"#00008B", "#808080"};
    
    Selection selectionProcess;
    selectionProcess.createSelection(&myDoc, UserPoints);
    selectionProcess.getPathsAS();

    //Routing routingProcess;
    //routingProcess.calculateRoutes();

    return 0;
}