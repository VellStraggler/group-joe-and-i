/*David Wells, Joe Allen, Josh Palmer*/
#include "simulateProjectile.h"
#include "artillery.h"
#include "gravity.h"
#include "air_density.h"
#include "drag_coefficient.h"
#include "speed_of_sound.h"
#include <tuple>
#include <cmath>

using namespace std;


// Simulate the projectile and return (distance, hangTime)
tuple<double, double> simulateProjectile(double angleDegrees)
{
   // Constants
   const double TIME_INCREMENT = 0.01L; // seconds
   const double DIAMETER_M = PROJECTILE_DIAMETER / 1000.0L; // mm to meters
   const long double AREA = PI * std::powl(DIAMETER_M / 2.0L, 2);

   // Initial setup
   double angle = toRadians(angleDegrees);
   double verticalSpeed = getVertSpeedComponent(angle, INITIAL_SPEED);
   double horizontalSpeed = getHorizSpeedComponent(angle, INITIAL_SPEED);
   double altitude = 0.0;
   double distance = 0.0;
   double time = 0.0;

   Gravity gravity;
   AirDensity airDensity;
   SpeedOfSound speedOfSound;
   DragCoefficient dragCoefficient;

   double prevAltitude = altitude;
   double prevDistance = distance;
   double prevTime = time;

   while (altitude >= 0.0)
   {
      // Store previous state
      prevAltitude = altitude;
      prevDistance = distance;
      prevTime = time;

      // Get environmental values
      double g = gravity.get(altitude);
      double rho = airDensity.get(altitude);
      double v = getSpeedFromComponents(verticalSpeed, horizontalSpeed);

      // Speed of sound and Mach calculation with diagnostics
      double sos = speedOfSound.get(altitude);
      if (sos <= 0.0) {
         //std::cerr << "ERROR: Speed of sound at altitude " << altitude << " is " << sos << std::endl;
      }
      double mach = v / sos;

      // Drag coefficient and diagnostics
      double c = dragCoefficient.get(mach);
      if (std::isnan(c)) {
         //std::cerr << "ERROR: Drag coefficient for mach " << mach << " is nan!" << std::endl;
      }

      // Compute drag force and resulting acceleration
      double dragForce = 0.5 * c * rho * v * v * AREA;
      double dragAccel = dragForce / PROJECTILE_MASS;
      double dragAngle = atan2(horizontalSpeed, verticalSpeed);
      double ddy = -g - dragAccel * cos(dragAngle);
      double ddx = -dragAccel * sin(dragAngle);


      // Update position
      altitude = getDistance(altitude, verticalSpeed, TIME_INCREMENT, ddy);
      distance = getDistance(distance, horizontalSpeed, TIME_INCREMENT, ddx);

      // Update velocity
      verticalSpeed = getKinematics(verticalSpeed, ddy, TIME_INCREMENT);
      horizontalSpeed = getKinematics(horizontalSpeed, ddx, TIME_INCREMENT);

      // Advance simulation time
      time += TIME_INCREMENT;
   }
   // Interpolate to find exact impact time and distance
   double dy = altitude - prevAltitude;
   double dx = distance - prevDistance;
   double dt = time - prevTime;
   double ratio = -prevAltitude / dy; // linear interpolation factor

   double finalDistance = prevDistance + dx * ratio;
   double finalTime = prevTime + dt * ratio;

   return make_tuple(finalDistance, finalTime);
}
