#pragma once
#include <map>
#include "interpolatable_chart.h"

/*David Wells, Joe Allen, Josh Palmer*/
/*Air density changes by *altitude**/
class AirDensity : public InterpolatableChart {
public:
   // Air density vs altitude (kg/m� vs meters)
   AirDensity() {
      chart = {
       { 0,     1.225     },
       { 1000,  1.112     },
       { 2000,  1.007     },
       { 3000,  0.9093    },
       { 4000,  0.8194    },
       { 5000,  0.7364    },
       { 6000,  0.6601    },
       { 7000,  0.5900    },
       { 8000,  0.5258    },
       { 9000,  0.4671    },
       { 10000, 0.4135    },
       { 15000, 0.1948    },
       { 20000, 0.08891   },
       { 25000, 0.04008   },
       { 30000, 0.01841   },
       { 40000, 0.003996  },
       { 50000, 0.001027  },
       { 60000, 0.0003097 },
       { 70000, 0.0000828 },
       { 80000, 0.0000185 }
      };
   }
};