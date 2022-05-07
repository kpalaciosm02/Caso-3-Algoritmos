#include <iostream>
#include <vector>
#include "Point.hpp"
using namespace std;

#ifndef ROUTE
#define ROUTE

class route{
    private:
        vector<point> routePoints;

    public:
        point getLastPoint();
        void addPointToRoute(point pointToAdd);
        vector<point> getRoutePoints();
};

point route::getLastPoint(){
    point lastPoint = routePoints.back();

    return lastPoint;
}

void route::addPointToRoute(point pointToAdd){
    routePoints.push_back(pointToAdd);
}

vector<point> route::getRoutePoints(){
    return routePoints;
}

#endif