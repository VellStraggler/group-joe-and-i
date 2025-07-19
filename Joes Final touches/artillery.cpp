




///*David Wells, Joe Allen, Josh Palmer*/
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include "simulateProjectile.h"  // Only need this one include for simulation
//
//using namespace std;
//
//int main()
//{
//   cout << fixed << setprecision(1);
//
//   while (true)
//   {
//      cout << "\nWhat is the angle of the howitzer where 0 is up? ";
//      string input;
//      cin >> input;
//
//      for (char& c : input) c = tolower(c);
//
//      if (input == "end")
//         break;
//      else if (input == "test") {
//         int angles[] = { 0, 30, 60, -45 };
//         for (int angle : angles) {
//            auto [d, t] = simulateProjectile(angle);
//            cout << "\nAngle: " << angle << " deg  Distance: " << d << " m  Hang Time: " << t << " s\n";
//         }
//         continue;
//      }
//
//      try {
//         double angle = stod(input);
//         auto [distance, time] = simulateProjectile(angle);
//         cout << "Distance: " << distance << " m\n";
//         cout << "Hang Time: " << time << " s\n";
//      }
//      catch (...) {
//         cout << "Invalid input. Enter a number, 'test', or 'end'.\n";
//      }
//   }
//
//   cout << "Program ended.\n";
//   return 0;
//}
