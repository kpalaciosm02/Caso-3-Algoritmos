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
        float height = 100;
        float width = 100;
        string observer;
        vector<route> routes;
    public:
        Routing();
        Routing(string pObserver);
        string getObserver();
        void pathsToPoints(vector<string> pathsAfterSelection);
        vector<point> takeCoordsFromPath(string path, vector<point>points);
        void calculateRoutesMovement(vector<point> pointsFromSelection);
        route createRoute(point point);
        point createRouting(point pPoint, point origin, point Destiny);
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

void Routing::pathsToPoints(vector<string> pathsAfterSelection){
    vector<point> pointsS = {};
    for (int i = 0; i < pathsAfterSelection.size(); i++){
        pointsS = takeCoordsFromPath(pathsAfterSelection.at(i), pointsS);
        calculateRoutesMovement(pointsS);
        pointsS = {};
    }
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
    for(int i = 0; i < pointsFromSelection.size(); i++){
        point init = pointsFromSelection[i];
        route routePoint = createRoute(init);
        routes.push_back(routePoint);
    }
}

route Routing::createRoute(point pPoint){
    route newRoute = route();
    newRoute.addPointToRoute(pPoint);

    float angle = 50;
    int frames = 2;
    float sizeMove = 0;
    bool createRoute = true;

    point origin(cos(angle), sin(angle));
    point movement(this->width/2, this->height/2);

    if(movement.get_x() == movement.get_y())
        sizeMove = movement.get_x();
    if(movement.get_x() < movement.get_y())
        sizeMove = movement.get_x();
    if(movement.get_x() > movement.get_y())
        sizeMove = movement.get_y();

    point Destiny(movement.get_x() + (sizeMove * origin.get_x()), movement.get_y() - (sizeMove * origin.get_y()));

    int counter = 0;

    while(createRoute){
        counter++;
        point tempLastPoint = newRoute.getLastPoint();

        point pointToAdd = createRouting(tempLastPoint, origin, Destiny);

        newRoute.addPointToRoute(pointToAdd);

        if(counter == 2)
            createRoute = false;
    }
    return newRoute;
}

point Routing::createRouting(point pPoint, point origin, point Destiny){
    point newPoint;
    float newX = pPoint.get_x() + Destiny.get_x();
    float newY = pPoint.get_y() + Destiny.get_y();
    
    if(newX > origin.get_x()){
        if(newY > origin.get_y()){
            newPoint = point(newX, newY);
        }
        else{
            newPoint = point(newX, Destiny.get_y());
        }
            
    }else{
        if(newY > origin.get_y()){
            newPoint = point(Destiny.get_x(), newY);
        }
        else{
            newPoint = point(Destiny.get_x(), Destiny.get_y());
        }
    }
    return newPoint;
}

vector<route> Routing::getRoutes(){
    return routes;
}