/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    David Wells, Joe Allen
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream> 
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;


/*********************************************
 * Position
 * A single position on the field in Meters
 *********************************************/
class Position
{
public:
   friend ::TestPosition;
   friend ::TestGround;
   friend ::TestHowitzer;
   friend ::TestProjectile;


   // constructors
   Position() : x(0.0), y(0.0) {}
   Position(double x, double y);
   Position(const Position& pt) : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX() const { return x; }
   double getMetersY() const { return y; }
   double getZoom() const;


   double getPixelsX() const;
   double getPixelsY() const;

   // setters
   void setMeters(double xMeters, double yMeters) { x = xMeters; y = yMeters; }
   void setMetersX(double xMeters) { x = xMeters; }
   void setMetersY(double yMeters) { y = yMeters; }
   void setPixelsX(double xPixels);
   void setPixelsY(double yPixels);
   void setZoom(double z);
   double addMetersX(double dx);
   double addMetersY(double dy);
   double addPixelsX(double dxPixels);
   double addPixelsY(double dyPixels);

   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() { x = -x; y = -y; }


private:
   double x; // horizontal position
   double y; // vertical position
   static double metersFromPixels;
};






/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};
