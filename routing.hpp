#include <vector>
#include "main.hpp"
#include "route.hpp"
#include <string>
#include <math.h>
#include <time.h>
#define PI 3.14159265358979323846

using namespace std;

class Routing{
    protected:
        string observer;
        vector<route> routes;
        float height = 1066.6667;
        float width = 1066.6667;
    public:
        Routing();
        Routing(string pObserver);
        string getObserver();
        bool randomTypeRoute();
        void calculateRoutesMovement(vector<point> pPointsFromSelection);
        route createRoute(point pPoint, int pMovement);
        point createRouting(point pPoint, int pAngle, bool pLine, float xOrigin, float yOrigin, float xDestiny, float yDestiny);
        float getHeight();
        void setHeight(float pHeight);
        float getWidth();
        void setWidth(float pWidth);
        vector<route> getRoutes();
};

Routing::Routing(){
    observer = "";
}

Routing::Routing(string pObserver){
    observer = pObserver;
}

bool Routing::randomTypeRoute(){
    int routeSelector = rand() % 2;
    bool routeType;
    srand(time(NULL));

    if(routeSelector == 0){
        routeType = true;
    }else{
        routeType = false;
    }

    return routeType;
}

void Routing::calculateRoutesMovement(vector<point> pPointsFromSelection){
    int sizeMovement = (this->height + this->width)/21;
    for(int i = 0; i < pPointsFromSelection.size(); i++){
        point init = pPointsFromSelection[i];
        route routePoint = createRoute(init, sizeMovement);
        routes.push_back(routePoint);
    }
}

route Routing::createRoute(point pPoint, int pMovement){
    route newRoute = route();
    newRoute.addPointToRoute(pPoint);

    int angle = 60;
    bool line = randomTypeRoute();
    float xMovement;
    float yMovement;
    float angleToRad = angle * PI / 100;

    if(angle < 90){
        xMovement = cos(angleToRad) * pMovement;
        yMovement = sin(angleToRad) * pMovement;
    }else{
        xMovement = sin(angleToRad) * pMovement;
        yMovement = cos(angleToRad) * pMovement; 
    }

    float xDestiny = pPoint.get_x() + xMovement;
    float yDestiny = pPoint.get_y() + yMovement;
    int frames = 4;
    bool creatingRoute = true;
    float xOrigin = ceil(xMovement/frames);
    float yOrigin = ceil(yMovement/frames);

    cout << "xMove: " << xMovement << "yMove" << yMovement << endl;
    cout << "xToMove: " << xOrigin << "yToMove: " << yOrigin << endl;
    cout << "xDestino: " << xDestiny << "yDes: " << yDestiny << endl;

    while(creatingRoute){
        point tempLastPoint = newRoute.getLastPoint();
        point pointToAdd = createRouting(tempLastPoint, angle, line, xOrigin, yOrigin, xDestiny, yDestiny);

        newRoute.addPointToRoute(pointToAdd);

        if(pointToAdd.get_x() == xDestiny && pointToAdd.get_y() == yDestiny)
            creatingRoute = false;
    }
}

point Routing::createRouting(point pPoint, int pAngle, bool pLine, float xOrigin, float yOrigin, float xDestiny, float yDestiny){
    float newX = pPoint.get_x() + xOrigin;
    float newY = pPoint.get_y() + yOrigin;
    point newPoint;

    if(xDestiny - newX > xOrigin){
        if(yDestiny - newY > yOrigin)
            newPoint = point(newX, newY);
        else
            newPoint = point(newX, yDestiny);
    }else{
        if(yDestiny - newY > yOrigin)
            newPoint = point(xDestiny, newY);
        else
            newPoint = point(xDestiny, yDestiny);
    }
    return newPoint;
}

vector<route> Routing::getRoutes(){
    return routes;
}