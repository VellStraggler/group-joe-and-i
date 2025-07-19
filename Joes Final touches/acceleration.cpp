/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include <cmath>


 /*********************************************
  * ACCELERATION : SET
  *  set from angle and direction
  *********************************************/
void Acceleration::set(const Angle& angle, double magnitude)
{

   ddx = magnitude * sin(angle.radians);
   ddy = magnitude * cos(angle.radians);
}

/*********************************************
 * ACCELERATION : DEFAULT CONSTRUCTOR
 *********************************************/
Acceleration::Acceleration()
{
   ddx = 0.0;
   ddy = 0.0;
}

/*********************************************
 * ACCELERATION : NON-DEFAULT CONSTRUCTOR
 *********************************************/
Acceleration::Acceleration(double ddx, double ddy)
{
   this->ddx = ddx;
   this->ddy = ddy;
}

/*********************************************
 * ACCELERATION : ADD DDX
 *********************************************/
void Acceleration::addDDX(double ddx)
{
   this->ddx += ddx;
}

/*********************************************
 * ACCELERATION : ADD DDY
 *********************************************/
void Acceleration::addDDY(double ddy)
{
   this->ddy += ddy;
}

/*********************************************
 * ACCELERATION : ADD
 *********************************************/
void Acceleration::add(const Acceleration& rhs)
{
   ddx += rhs.ddx;
   ddy += rhs.ddy;
}

/*********************************************
 * ACCELERATION : GET DDX
 *********************************************/
double Acceleration::getDDX() const
{
   return ddx;
}

/*********************************************
 * ACCELERATION : GET DDY
 *********************************************/
double Acceleration::getDDY() const
{
   return ddy;
}

/*********************************************
 * ACCELERATION : SET DDX
 *********************************************/
void Acceleration::setDDX(double ddx)
{
   this->ddx = ddx;
}

/*********************************************
 * ACCELERATION : SET DDY
 *********************************************/
void Acceleration::setDDY(double ddy)
{
   this->ddy = ddy;
}
