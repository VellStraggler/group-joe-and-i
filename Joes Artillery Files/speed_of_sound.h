/*David Wells, Joe Allen, Josh Palmer*/
#pragma once
#include <map>
#include "interpolatable_chart.h"

/*Speed of sound changes by *altitude**/
class SpeedOfSound : public InterpolatableChart {
public:
   SpeedOfSound() {
      chart = {
         { 0,     340 },
         { 1000,  336 },
         { 2000,  332 },
         { 3000,  328 },
         { 4000,  324 },
         { 5000,  320 },
         { 6000,  316 },
         { 7000,  312 },
         { 8000,  308 },
         { 9000,  303 },
         { 10000, 299 },
         { 15000, 295 },
         { 20000, 295 },
         { 25000, 295 },
         { 30000, 305 },
         { 40000, 324 },
         { 50000, 337 },
         { 60000, 319 },
         { 70000, 289 },
         { 80000, 269 }
      };
   }
};
