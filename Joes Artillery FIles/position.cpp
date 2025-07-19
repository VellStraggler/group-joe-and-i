/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <cassert>


Position::Position(double x, double y) : x(x), y(y) {}

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point. Please look ahead to
 * Week 12 C++ reading for an idea of how this works.
 * Basically, we are copying the data from posRHS
 * into this.
 *****************************************/
Position& Position::operator = (const Position& posRHS)
{
   this->x = posRHS.x;
   this->y = posRHS.y;
   return *this;
}

/************************************************************************
 * UPDATE POSITION
 * Update the current position based on the impulse of velocity
 * taking into account time dilation:
 *
 *   s = s_0 + vt + 1/2 at^2
 *
 *   INPUT  POSITION     The location of the item
 *          VELOCITY     The velocity of the item
 *          ACCELERATION The acceleration of the item
 *          TIME         How much time are we talking about?
 *   OUTPUT POSITION     The location, updated
 *
 *
 *  x = x + dx t + 1/2 ddx t^2
 *  y = y + dy t + 1/2 ddy t^2
 *************************************************************************/
void Position::add(const Acceleration& a, const Velocity& v, double t)
{
   x += v.getDX() * t + 0.5 * a.getDDX() * t * t;
   y += v.getDY() * t + 0.5 * a.getDDY() * t * t;
}


double Position::getZoom() const
{
   return metersFromPixels;
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Position& pt)
{
   out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
   return out;
}

/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Position& pt)
{
   double x;
   double y;
   in >> x >> y;

   pt.setMetersX(x);
   pt.setMetersY(y);

   return in;
}

/**************************************************
 * SET ZOOM
 * Set the static zoom level: meters per pixel.
 * This affects all instances of Position.
 * Input:  z - zoom factor in meters/pixel
 **************************************************/
void Position::setZoom(double z)
{
   metersFromPixels = z;
}

/**************************************************
 * SET PIXELS X
 * Set the X position by pixel value.
 * Converts pixel units to meters using zoom factor.
 * Input: xPixels - horizontal pixels from origin
 **************************************************/
void Position::setPixelsX(double xPixels)
{
   x = xPixels * metersFromPixels;
}

/**************************************************
 * SET PIXELS Y
 * Set the Y position by pixel value.
 * Converts pixel units to meters using zoom factor.
 * Input: yPixels - vertical pixels from origin
 **************************************************/
void Position::setPixelsY(double yPixels)
{
   y = yPixels * metersFromPixels;
}

/**************************************************
 * ADD METERS X
 * Move the X position by a distance in meters.
 * Input: dx - change in X in meters
 * Return: new X position
 **************************************************/
double Position::addMetersX(double dx)
{
   x += dx;
   return x;
}

/**************************************************
 * ADD METERS Y
 * Move the Y position by a distance in meters.
 * Input: dy - change in Y in meters
 * Return: new Y position
 **************************************************/
double Position::addMetersY(double dy)
{
   y += dy;
   return y;
}

/**************************************************
 * ADD PIXELS X
 * Move the X position by a number of pixels.
 * Converts pixel delta to meters.
 * Input: dxPixels - change in pixels
 * Return: new X position in meters
 **************************************************/
double Position::addPixelsX(double dxPixels)
{
   x += dxPixels * metersFromPixels;
   return x;
}

/**************************************************
 * ADD PIXELS Y
 * Move the Y position by a number of pixels.
 * Converts pixel delta to meters.
 * Input: dyPixels - change in pixels
 * Return: new Y position in meters
 **************************************************/
double Position::addPixelsY(double dyPixels)
{
   y += dyPixels * metersFromPixels;
   return y;
}

/**************************************************
 * GET PIXELS X
 * Convert the X coordinate from meters to pixels.
 * Output: horizontal pixels from origin
 **************************************************/
double Position::getPixelsX() const
{
   return x / metersFromPixels;
}

/**************************************************
 * GET PIXELS Y
 * Convert the Y coordinate from meters to pixels.
 * Output: vertical pixels from origin
 **************************************************/
double Position::getPixelsY() const
{
   return y / metersFromPixels;
}


