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
        float height = 800;
        float width = 800;
        string observer;
        vector<route> routes;
    public:
        Routing();
        Routing(string pObserver);
        string getObserver();
        vector<point> pathsToPoints(vector<string> pathsAfterSelection);
        vector<point> takeCoordsFromPath(string path, vector<point>points);
        void calculateRoutesMovement(vector<point> pointsFromSelection);
        route createRoute(point point, int movement);
        point createRouting(point point, float xOrigin, float yOrigin, float xDestiny, float yDestiny);
        float getHeight();
        void setHeight(float height);
        float getWidth();
        void setWidth(float width);
        vector<route> getRoutes();
};

Routing::Routing(){
    observer = "";
}

Routing::Routing(string pObserver){
    observer = pObserver;
    
}

vector<point> Routing::pathsToPoints(vector<string> pathsAfterSelection){
    vector<point> pointsS = {};
    vector<point> pointsAS = {};
    for (int i = 0; i < pathsAfterSelection.size(); i++){
        pointsS = takeCoordsFromPath(pathsAfterSelection.at(i), pointsS);
        pointsAS = pointsS;
        pointsS = {};
    }
    return pointsAS;
}

vector<point> Routing::takeCoordsFromPath(string path, vector<point>points){
    int pathLarge = path.size();
    string sNumber = "";
    float fNumber = 0.0;
    bool isX = true;
    vector<float> x;
    vector<float> y;
    for (int i = 0; i < pathLarge; i++){
        if (path[i] == 'M' || path[i] == 'L' || path[i] == 'H' || path[i] == 'V' || path[i] == 'C' || path[i] == 'S' || path[i] == 'Q' 
            || path[i] == 'T' || path[i] == 'A' || path[i] == 'z' || path[i] == ',' || path[i] == 'Z'){
            if (i != 0){
                fNumber = stof(sNumber);
                if (isX){
                    x.push_back(fNumber);
                    isX = false;
                }
                else{
                    y.push_back(fNumber);
                    isX = true;
                }
                fNumber = 0.0;
                sNumber = "";
            }
            
        }
        else {
            sNumber += path[i];
        }
    }
    for (int i = 0; i < x.size(); i++){
        point point(x.at(i),y.at(i));
        points.push_back(point);
        //point.print();
    }
    return points;
}

void Routing::calculateRoutesMovement(vector<point> pointsFromSelection){
    int sizeMovement = (this->height + this->width)/8;
    for(int i = 0; i < pointsFromSelection.size(); i++){
        point init = pointsFromSelection[i];
        route routePoint = createRoute(init, sizeMovement);
        routes.push_back(routePoint);
    }
}

route Routing::createRoute(point pPoint, int movement){
    route newRoute = route();
    newRoute.addPointToRoute(pPoint);

    int angle = 60;
    float angleToRad = angle * PI / 180;

    float xMovement;
    float yMovement;

    float xDestiny = pPoint.get_x() + xMovement;
    float yDestiny = pPoint.get_y() + yMovement;

    int frames = 10;
    bool createRoute = true;

    float xOrigin = ceil(xMovement/frames);
    float yOrigin = ceil(yMovement/frames);

    if(angle < 180){
        xMovement = cos(angleToRad) * movement;
        yMovement = sin(angleToRad) * movement;
    }else{
        xMovement = sin(angleToRad) * movement;
        yMovement = cos(angleToRad) * movement; 
    }

    while(createRoute){
        point tempLastPoint = newRoute.getLastPoint();
        point pointToAdd = createRouting(tempLastPoint, xOrigin, yOrigin, xDestiny, yDestiny);

        newRoute.addPointToRoute(pointToAdd);

        if(pointToAdd.get_x() == xDestiny && pointToAdd.get_y() == yDestiny)
            createRoute = false;
    }
    return newRoute;
}

point Routing::createRouting(point pPoint, float xOrigin, float yOrigin, float xDestiny, float yDestiny){
    point newPoint;
    float newX = pPoint.get_x() + xOrigin;
    float newY = pPoint.get_y() + yOrigin;
    
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