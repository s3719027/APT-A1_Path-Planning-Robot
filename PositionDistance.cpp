
#include "PositionDistance.h"
#include <iostream>

PositionDistance::PositionDistance(int _x, int _y, int _distance) {
   x = _x;
   y = _y;
   distance = _distance;
}
PositionDistance::PositionDistance(PositionDistance& other) {
   this->x = other.x;
   this->y = other.y;
   this->distance = other.distance;
}
PositionDistance::~PositionDistance() {
   
}

int PositionDistance::getX() {
   return x;
}

int PositionDistance::getY() {
   return y;
}

int PositionDistance::getDistance() {
   return distance;
}
