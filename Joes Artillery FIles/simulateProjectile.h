/*David Wells, Joe Allen, Josh Palmer*/
#pragma once
#include <tuple>

// Function to simulate the projectile's motion
// Returns a tuple: (distance in meters, hang time in seconds)
std::tuple<double, double> simulateProjectile(double angleDegrees);