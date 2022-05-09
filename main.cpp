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
    vector<path> prueba = selectionProcess.SeparePathElements(&myDoc);

    for (vector<path>::const_iterator i = prueba.begin(); i != prueba.end(); i++){
        path p = *i;
        p.print();
    }
    cout << endl;


    vector<path> pathsSelection = selectionProcess.getPathsAS();
    vector<string> stringPathsSelection = selectionProcess.SeparatePaths(pathsSelection);

    
    Routing routingProcess;
    vector<point> pointsAS = routingProcess.pathsToPoints(stringPathsSelection);
    routingProcess.calculateRoutesMovement(pointsAS);
    vector<route> vc = routingProcess.getRoutes();
    for(vector<route>::const_iterator i = vc.begin(); i != vc.end(); i++)
    {
        
    }    
    return 0;
}