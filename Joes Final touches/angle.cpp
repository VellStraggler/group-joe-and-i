/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich,
 *    David Wells
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor(), M_PI
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
   while (radians < 0.0)
      radians += 2.0 * M_PI;

   while (radians >= 2.0 * M_PI)
      radians -= 2.0 * M_PI;

   return radians;
}
/* Get the horizontal component of an angle, assuming a unit circle. */
double Angle::getDx() const {
   return sin(radians);
}
/* Get the vertical component of an angle. */
double Angle::getDy() const {
   return cos(radians);
}
bool Angle::isRight() const {
   return radians - M_PI_2 <= 0;
}
bool Angle::isLeft() const {
   return !isRight();
}
void Angle::setDxDy(double dx, double dy) {
   // We don't need to store dx or dy, just radians
   // atan2 allows for two arguments and returns from any of the 4 quadrants
   // handles by-zero division automatically
   double newRad = (M_PI_2 - atan2(dy, dx));
   this->radians = normalize(newRad);
}