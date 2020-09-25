/*
DANIEL BOUND - S3719027

   The main approach and way I solved this problem was by using the pseudocode given. We start with an initial position. We then look around that position for potential other positions and if there are any we add them to the p list. Once this is done, the position we are 'at' is added to t. This is repeated until all the values in p have been focussed on, observed around and added to t. I some helper methods to aid in this process but not too much else was added.
   The main issues i encountered were initially wrapping my head around the pseudocode, and then moving on to the pointers. Once the pseudocode was put into code, and a deep copy was to be returned, i had trouble wrapping my head around why the values of the old list ('p') were being changed when calling the copy constructor. After watching a few tutorials and going back over the lecture slides, I managed to figure it out and fix my implementation.
   I chose to add a few helper methods in the PathPlanning class to deconjest the main 'getReachablePositions' method. I also chose to use an 'exists' boolean for the 'getReachablePositions' method as i found that it was the most intuitive way to implement the pseudocode, with it minimizing run time as the methods that checked positions the coordinate was already in the list.
   Although i havnt had time to finish milestone 3 (I was so close...) or milestone 4, I believe the quality of my code as of a high standard and is implemented well. There is little code redundancy and the methods and used effectively. I created minimal instance variables and the naming of variables is done clearly, making them easy to comprehend, given the skeleton code.
   
   (Hopefully I can get some marks toward milestone 3 I was so close but ran out of time... :'( )
   
   Thank you!!

*/




#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
  
   //all variables needed in PathPlanning are inititialised.
   this->maze = maze;
   this->rows = rows;
   this->cols = cols;
   p = new PDList();
   t = new PDList();
   p_m3 = new PDList();
   t_m3 = new PDList();
}

PathPlanning::~PathPlanning() {
}

void PathPlanning::initialPosition(int x, int y) {
   //initial position is added to p
   PDPtr initial = new PositionDistance(x, y, 0);
   p->addBack(initial);
}

PDList* PathPlanning::getReachablePositions() {
      
   bool exists = false;
   
   //while there still exists a new poisition
   while (!exists) {
      for (int i = 0; i < p->size(); i++) {
         
         //if 't' list contains this 'p' list coordinate
         exists = t->containsCoordinate(p->get(i)) ? true : false;
         
         if (!exists) {
            
            //checks above the 'p' list position for '.' character
            if(checkAbove(p->get(i))) {
               PDPtr pNew = new PositionDistance(p->get(i)->getX(), p->get(i)->getY() - 1, p->get(i)->getDistance() + 1);
               p->addBack(pNew);
            }
            
            //checks below the 'p' list position for '.' character
            if(checkBelow(p->get(i))) {
               PDPtr pNew = new PositionDistance(p->get(i)->getX(), p->get(i)->getY() + 1, p->get(i)->getDistance() + 1);
               p->addBack(pNew);
            }
            
            //checks left the 'p' list position for '.' character
            if(checkLeft(p->get(i))) {
               PDPtr pNew = new PositionDistance(p->get(i)->getX() - 1, p->get(i)->getY(), p->get(i)->getDistance() + 1);
               p->addBack(pNew);
            }
            
            //checks right the 'p' list position for '.' character
            if(checkRight(p->get(i))) {
               PDPtr pNew = new PositionDistance(p->get(i)->getX() + 1, p->get(i)->getY(), p->get(i)->getDistance() + 1);
               p->addBack(pNew);
            }
            //p is added to t
            t->addBack(p->get(i));
            break;
         }
      }
   }
   // return t as a deep copy;
   tCopy = new PDList(*t);
   return tCopy;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(int toX, int toY) {
   
   solvePath(p->get(0)->getX(), toX, p->get(0)->getY(), toY);
   
   PDList* pathSequence = new PDList(*t_m3);
   
   return pathSequence;
   
}
bool PathPlanning::checkAbove(PDPtr position) {
   if (maze[position->getY() - 1][position->getX()] == '.') {
      PDPtr tempPos = new PositionDistance(position->getX(), position->getY() - 1, position->getDistance() + 1);
      //makes sure the value is not already in p (no duplicates)
      if (!p->containsCoordinate(tempPos)) {
         delete tempPos;
         return true;
      }
   }
   return false;
}
bool PathPlanning::checkBelow(PDPtr position) {
   if (maze[position->getY() + 1][position->getX()] == '.') {
      PDPtr tempPos = new PositionDistance(position->getX(), position->getY() + 1, position->getDistance() + 1);
      //makes sure the value is not already in p (no duplicates)
      if (!p->containsCoordinate(tempPos)) {
         delete tempPos;
         return true;
      }   
   }
   return false;
}
bool PathPlanning::checkLeft(PDPtr position) {
   if (maze[position->getY()][position->getX() - 1] == '.') {
      PDPtr tempPos = new PositionDistance(position->getX() - 1, position->getY(), position->getDistance() + 1);
      //makes sure the value is not already in p (no duplicates)
      if (!(p->containsCoordinate(tempPos))) {
         delete tempPos;
         return true;
      }   
   }
   return false;
}
bool PathPlanning::checkRight(PDPtr position) {
   if (maze[position->getY()][position->getX() + 1] == '.') {
      PDPtr tempPos = new PositionDistance(position->getX() + 1, position->getY(), position->getDistance() + 1);
      //makes sure the value is not already in p (no duplicates)
      if (!p->containsCoordinate(tempPos)) {
         delete tempPos;
         return true;
      }
   }
   return false;
}
bool PathPlanning::solvePath(int x, int toX, int y, int toY) {
   
   if (x == toX && y == toY) {
      return true;
   }
   PDPtr p_m3Temp = new PositionDistance(x,y,0);
   if ((maze[y][x] == '~' || maze[y][x] == '=') || p_m3->containsCoordinate(p_m3Temp)) {
      return false;
   }
   p_m3->addBack(p_m3Temp);
   
   if (solvePath(x-1, toX, y, toY)) {
      PDPtr t_m3Temp = new PositionDistance(x,y,t_m3->size());
      t_m3->addBack(t_m3Temp);
      return true;
   }
   if (solvePath(x+1, toX, y, toY)) {
      PDPtr t_m3Temp = new PositionDistance(x,y,t_m3->size());
      t_m3->addBack(t_m3Temp);
      return true;
   }
   if (solvePath(x, toX, y-1, toY)) {
      PDPtr t_m3Temp = new PositionDistance(x,y,t_m3->size());
      t_m3->addBack(t_m3Temp);
      return true;
   }
   if (solvePath(x, toX, y+1, toY)) {
      PDPtr t_m3Temp = new PositionDistance(x,y,t_m3->size());
      t_m3->addBack(t_m3Temp);
      return true;
   }
   return false;
}
