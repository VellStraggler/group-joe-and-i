/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()

 /*********************************************
  * VELOCITY : ADD
  *  v = v_0 + a t
  *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx = dx + acceleration.getDDX() * time;
   dy = dy + acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{  //           ___________
   // speed = \/dx^2 + dy^2
   return sqrt(dx * dx + dy * dy);
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *  angle is in degrees
 *********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
   dx = magnitude * sin(angle.getRadians());  // horizontal
   dy = magnitude * cos(angle.getRadians());  // vertical
}
