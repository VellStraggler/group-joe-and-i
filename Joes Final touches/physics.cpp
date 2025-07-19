/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/

#include "physics.h"  // for the prototypes

 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   // If domain is out of bounds, return the closest endpoint
   if (domain <= mapping[0].domain)
      return mapping[0].range;
   if (domain >= mapping[numMapping - 1].domain)
      return mapping[numMapping - 1].range;

   // Search for bounding pair [i-1] and [i]
   for (int i = 1; i < numMapping; ++i)
   {
      if (mapping[i].domain >= domain)
      {
         double d0 = mapping[i - 1].domain;
         double r0 = mapping[i - 1].range;
         double d1 = mapping[i].domain;
         double r1 = mapping[i].range;
         return linearInterpolation(d0, r0, d1, r1, domain);
      }
   }

   // Should not reach here
   assert(false);
   return -99.9;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   const Mapping gravityMap[] =
   {
      {    0.0, 9.80700 },
      { 3666.0, 9.79500 },
      { 5500.0, 9.78950 },
      { 8848.0, 9.77945 },
      {10000.0, 9.77600 },
      {20000.0, 9.74500 },
      {30000.0, 9.71500 },
      {40000.0, 9.68400 },
      {50000.0, 9.65400 },
      {60000.0, 9.62400 },
      {70000.0, 9.59400 },
      {80000.0, 9.56400 }
   };

   const int numValues = sizeof(gravityMap) / sizeof(gravityMap[0]);
   return linearInterpolation(gravityMap, numValues, altitude);
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   const Mapping densityMap[] =
   {
      {     0.0, 1.2250000 },
      { 3666.0, 0.8493720 },
      { 5500.0, 0.6982500 },
      { 8848.0, 0.4759719 },
      {10000.0, 0.4135000 },
      {20000.0, 0.0889100 },
      {30000.0, 0.0184100 },
      {40000.0, 0.0039960 },
      {50000.0, 0.0010270 },
      {60000.0, 0.0003097 },
      {70000.0, 0.0000828 },
      {80000.0, 0.0000185 }
   };

   const int numValues = sizeof(densityMap) / sizeof(densityMap[0]);
   return linearInterpolation(densityMap, numValues, altitude);
}


/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   const Mapping soundMap[] =
   {
      {    0.0, 340.0 },
      { 3666.0, 325.336 },
      { 5500.0, 318.0 },
      { 8848.0, 303.76 },
      {10000.0, 299.0 },
      {20000.0, 295.1 },
      {30000.0, 305.0 },
      {40000.0, 322.8335},
      {50000.0, 339.3335},
      {60000.0, 331.3 },
      {70000.0, 329.8 },
      {80000.0, 269.0 }
   };

   const int numValues = sizeof(soundMap) / sizeof(soundMap[0]);
   return linearInterpolation(soundMap, numValues, altitude);
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   const Mapping dragMap[] =
   {
      { 0.000, 0.0000 },
      { 0.100, 0.0543 },
      { 0.300, 0.1000 },
      { 0.500, 0.2500 },
      { 0.600, 0.1845 },
      { 0.700, 0.2000 },
      { 0.890, 0.3500 },
      { 0.920, 0.3500 },
      { 0.960, 0.4000 },
      { 0.980, 0.4250 },
      { 1.000, 0.4500 },
      { 1.020, 0.4750 },
      { 1.060, 0.5000 },
      { 1.240, 0.4500 },
      { 1.530, 0.4000 },
      { 1.990, 0.3500 },
      { 2.870, 0.3000 },
      { 2.890, 0.3000 },
      { 3.14159, 0.2347 },
      { 5.000, 0.2656 }
   };

   const int numValues = sizeof(dragMap) / sizeof(dragMap[0]);
   return linearInterpolation(dragMap, numValues, speedMach);
}

