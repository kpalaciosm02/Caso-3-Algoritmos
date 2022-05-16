#include "ObserverPattern.h"
#include "selection.hpp"
#include "routing.hpp"
#include "main.hpp"
#include <tuple>
#include "generation.hpp"

using namespace std;

int main(){
    //Leer XML
    char fileName[] = "test2.svg";
    file<> file(fileName); // Lee y carga el archivo en memoria
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
    /*for (vector<route>::const_iterator i = vc.begin(); i != vc.end(); i++){
        route r = *i;
        vector<point> rp = r.getRoutePoints();
        for (vector<point>::const_iterator i = rp.begin(); i != rp.end(); i++){
            point pr = *i;
            pr.print();
        }
    }*/
    
    Generation gen(vc,1);
    vector<pathGeneration> paths = gen.generatePath();
    /*for (int i = 0; i < paths.size(); i++){
        cout << "ID: " << paths.at(i).id << "   Path: " << paths.at(i).pathP << endl;
    }*/
    gen.generateSVG(fileName,paths);
    cout << endl << endl << "Hay un bug en generateSVG, se pasan bien los datos pero no entran bien al archivo" << endl;
    cout << "Arreglar que no todos los paths se metan a un archivo, en generate path hay que dividirlo por rutas" << endl;
    cout << "Preguntar a yuleisi si enrutamiento genera los paths para todos los archivos con una llamada o si lo tengo que llamar cada vez que voy a hacer un archivo" << endl;
    return 0;
}