/*David Wells, Joe Allen, Josh Palmer*/


#pragma once
#include <iostream>
#include <cmath>
#include <tuple>
#include "gravity.h"

const double INITIAL_SPEED = 827.0;
const double PI = 3.1415926535897;
const int DEFAULT_ALTITUDE = 0;
const double PROJECTILE_MASS = 46.7; // in kg
const double PROJECTILE_DIAMETER = 154.89; // in mm

//Gravity g = Gravity();

inline double toRadians(double degrees) {
   return degrees * PI / 180.0;
}

inline double getVertSpeedComponent(double radians, double speed) {
   return speed * cos(radians);
}

inline double getHorizSpeedComponent(double radians, double speed) {
   return speed * sin(radians);
}

// Gravity is a class that gives you the gravity at a given altitude

/* This can give distance for either horizontal or vertical, but not both (don't use velocity!)*/
inline double getDistance(double initialDistance, double axisVelocity, double time, double acceleration) {
   return initialDistance + (axisVelocity * time) + (0.5 * acceleration * time * time);
}

/* Returns the new axis velocity (NOT TOTAL VELOCITY, at least not yet) */
inline double getKinematics(double initialVelocity, double acceleration, double time) {
   return initialVelocity + (acceleration * time);
}

inline double getAngleFromComponents(double verticalSpeed, double horizontalSpeed) {
   return atan2(horizontalSpeed, verticalSpeed);
}

/* Referenced as Pythagorean Theorem in Lab07 Description*/
inline double getSpeedFromComponents(double verticalSpeed, double horizontalSpeed) {
   return sqrt(pow(verticalSpeed, 2) + pow(horizontalSpeed, 2));
}

// Linear Interpolation is found in the InterpolatableChart class
// and all of its derived classes, such as Gravity.

// THIS PASSED
inline void step1() {
   double angle = toRadians(75.0);
   double verticalSpeed = getVertSpeedComponent(angle, INITIAL_SPEED);
   double horizontalSpeed = getHorizSpeedComponent(angle, INITIAL_SPEED);
   double horizontalDistance = horizontalSpeed * 20;
   double verticalDistance = verticalSpeed * 20;
   std::cout << horizontalDistance << " m distance" << std::endl;
   std::cout << verticalDistance << " m altitude" << std::endl;
}
// THIS PASSED
inline void step2() {
   const double CONST_GRAVITY = -9.8; // m/s^2
   const double TIME_UNIT = 1;
   double angle = toRadians(75.0);
   double acceleration = CONST_GRAVITY;
   double horizontalDistance = 0;
   double verticalDistance = DEFAULT_ALTITUDE;
   double velocity = INITIAL_SPEED;

   double verticalSpeed = getVertSpeedComponent(angle, velocity);
   double horizontalSpeed = getHorizSpeedComponent(angle, velocity);


   for (int i = 0; i < 20; i++) {
      std::cout << "iteration: " << i << std::endl;
      horizontalDistance += horizontalSpeed * TIME_UNIT;
      verticalDistance = getDistance(verticalDistance, verticalSpeed, TIME_UNIT, acceleration);

      // update for next iteration
      verticalSpeed = getKinematics(verticalSpeed, acceleration, TIME_UNIT);
      velocity = getSpeedFromComponents(verticalSpeed, horizontalSpeed);
      std::cout << "velocity: " << velocity << std::endl;
      std::cout << horizontalDistance << ", " << verticalDistance << std::endl;
   }

}
