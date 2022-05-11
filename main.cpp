#include "ObserverPattern.h"
#include "selection.hpp"
#include "routing.hpp"
#include "main.hpp"
#include <tuple>
#include "generation.hpp"

using namespace std;

int main(){
    //Leer XML
    cout << "primera linea" << endl;
    file<> file("test2.svg"); // Lee y carga el archivo en memoria
    cout << "abri el archivo" << endl;
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    vector<float> UserPoints = {600, 300, 800, 300, 400, 500, 600, 700, 900, 100, 300, 500};
    vector<string> colors = {"#00008B", "#808080"};
    
    Selection selectionProcess;
    selectionProcess.createSelection(&myDoc, UserPoints);
    vector<path> prueba = selectionProcess.SeparePathElements(&myDoc);

    vector<path> pathsSelection = selectionProcess.getPathsAS();
    vector<string> stringPathsSelection = selectionProcess.SeparatePaths(pathsSelection);

    Routing routingProcess;
    routingProcess.pathsToPoints(stringPathsSelection);
    vector<route> vc = routingProcess.getRoutes();
    cout << "Lleguee" << endl;
    for (vector<route>::const_iterator i = vc.begin(); i != vc.end(); i++){
        route r = *i;
        vector<point> rp = r.getRoutePoints();
        for (vector<point>::const_iterator i = rp.begin(); i != rp.end(); i++){
            point pr = *i;
            pr.print();
        }
    }
    /*cout << "----------------------------------------------------------------------------------------------------------" << endl;
    Generation generacion(vc,1);
    generacion.generatePath();*/

    return 0;
}