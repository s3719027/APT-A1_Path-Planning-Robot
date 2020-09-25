
#ifndef COSC_ASS_ONE_POSITION
#define COSC_ASS_ONE_POSITION

#include "Types.h"

class PositionDistance {
public:

   /*                                           */
   /* DO NOT MODIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // x-co-ordinate
   int getX();

   // y-co-ordinate
   int getY();

   // Distance
   int getDistance();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   // PositionDistance constructor
   PositionDistance(int _x, int _y, int _distance);
   PositionDistance(PositionDistance& other);
   ~PositionDistance();
   
private:
   
   int x;
   int y;
   int distance;
   
};

/*                                           */
/* DO NOT MODIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef PositionDistance* PDPtr;

#endif // COSC_ASS_ONE_POSITION
