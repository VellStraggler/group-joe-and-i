/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich,
 *    David Wells
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI
#include "acceleration.h"

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   friend class Acceleration;


   // Constructors
   Angle() { radians = 0.0; }
   Angle(const Angle& rhs) { radians = rhs.radians; }
   Angle(double degrees) { radians = normalize(convertToRadians(degrees)); }

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }
   double getDx() const;
   double getDy() const;
   bool isRight() const;
   bool isLeft() const;

   // Setters
   void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }
   void setRadians(double radians) { this->radians = normalize(radians); }

   void setUp() { radians = 0.0; }
   void setDown() { radians = M_PI; }
   void setRight() { radians = M_PI_2; }
   void setLeft() { radians = M_PI + M_PI_2; }

   void reverse() { radians = normalize(radians + M_PI); }

   void setDxDy(double dx, double dy);

   Angle& add(double delta)
   {
      radians = normalize(radians + delta);
      return *this;
   }

private:
   double normalize(double radians) const;

   double convertToDegrees(double radians) const
   {
      return radians * (180.0 / M_PI);
   }

   double convertToRadians(double degrees) const
   {
      return degrees * (M_PI / 180.0);
   }

   double radians;   // 360 degrees equals 2 PI radians
};
