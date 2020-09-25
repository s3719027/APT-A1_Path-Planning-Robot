
#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>


PDList::PDList() : positions(), numPositions(0){
}
PDList::PDList(PDList& other) : positions() {
   //start it at 1 to it does not return the initial position
   PDPtr position;
   //on coreteaching servers, positions[0] and positions[1] are not set to null but the rest of the array is. It works perfectly on my machine (they get set to null)... Had to manually set them to null.
   positions[0] = nullptr;
   positions[1] = nullptr;
   for (int i = 1; i < other.size(); i++) {
      position = new PositionDistance(*(other.get(i)));
      addBack(position);
   }
   //delete position;
}

PDList::~PDList() {
}

int PDList::size() {
   return numPositions;
}

PDPtr PDList::get(int i) {
   return positions[i];
}

void PDList::addBack(PDPtr position) {
   
   for (int i = 0; i < PDLIST_SIZE; i++) {
      if (positions[i] == nullptr) {
         positions[i] = position;
         break;
      }
   }
   numPositions++;
}

bool PDList::containsCoordinate(PDPtr position) {
   
   for (int i = 0; i < numPositions; i++) {
      if (position->getX() == positions[i]->getX()) {
         if (position->getY() == positions[i]->getY()) {
               return true;
         }
      }
   }
   return false;
}

void PDList::clear() {
}
