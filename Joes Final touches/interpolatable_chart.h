/*David Wells, Joe Allen, Josh Palmer*/
#pragma once
#include <map>
#include <vector>
#include <stdexcept>

class InterpolatableChart {
protected:
   std::map<double, double> chart;

   /* Finds the closest x-values in gravityByKmm map */
   std::vector<double> getClosestXValues(double x) {
      if (chart.empty()) {
         throw std::runtime_error("Chart is empty — cannot get last key.");
      }
      double before = -1;
      double after = -1;
      // edge case: if x is less than 0, default to 0
      if (x < 0) {
         return { 0, 0 };
      }

      // Iterate through the chart to find the closest x-values
      for (const auto& pair : chart) {
         if (pair.first < x) {
            before = pair.first;
         }
         else if (pair.first > x) {
            after = pair.first;
            break;
         }
      }
      if (before == -1 || after == -1) {
         // Return first and last X keys to keep interpolation valid
         double first = chart.begin()->first;
         double last = chart.rbegin()->first;
         return { first, last };
      }
      return { before, after };
   }

   double interpolateForY(double x1, double x2, double midX) {
      double y1 = chart[x1];
      double y2 = chart[x2];
      // Linear interpolation formula
      return ((y2 - y1) / (x2 - x1)) * (midX - x1) + y1;
   }

public:
   // Add virtual to allow derived classes to override this method
   virtual double get(double x) {
      // Check if x is in the chart
      if (chart.find(x) != chart.end()) {
         return chart[x];
      }
      // Interpolate if x is not in the chart
      std::vector<double> closestXs = getClosestXValues(x);
      return interpolateForY(closestXs[0], closestXs[1], x);
   }
};