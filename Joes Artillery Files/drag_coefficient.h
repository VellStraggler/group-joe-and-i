/*David Wells, Joe Allen, Josh Palmer*/
#pragma once
#include <map>
#include "interpolatable_chart.h"

/*Drag Coefficient changes by *mach speed**/
class DragCoefficient : public InterpolatableChart {
public:
   // Drag Coefficient vs Mach number (source data)
   DragCoefficient() {
      chart = {
       { 0    , 0      },
       { 0.300, 0.1629 },
       { 0.500, 0.1659 },
       { 0.700, 0.2031 },
       { 0.890, 0.2597 },
       { 0.920, 0.3010 },
       { 0.960, 0.3287 },
       { 0.980, 0.4002 },
       { 1.000, 0.4258 },
       { 1.020, 0.4335 },
       { 1.060, 0.4483 },
       { 1.240, 0.4064 },
       { 1.530, 0.3663 },
       { 1.990, 0.2897 },
       { 2.870, 0.2297 },
       { 2.890, 0.2306 },
       { 5.000, 0.2656 }
      };
   }
};