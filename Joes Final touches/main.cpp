#include "test.h"
#include "position.h"
#include "simulation.h"
#include "uiInteract.h"

// This changes the number of pixels per meter. Smaller number means EACH PIXEL IS WORTH MORE METERS I THINK.
// hole numbers makes the world larger. This is inverse logic.
double Position::metersFromPixels = 3; //.7 WHEN POSITION DOWN BELOW IS 600, 500

/************************************
 * MAIN
 * There can be only one!
 ************************************/
int main()
{
    // Run tests (if any)
    testRunner();

    // 1. Define the simulation world in METERS.
    // This defines the maximum bounds of your simulation.
    Position worldSize(40000.0, 20500.0);

    // 2. Define the window size in PIXELS.
    // This defines the physical size of the window on your screen.
    Position windowSize(800.0, 500.0);

    // Set up the simulation with the correct objects
    Interface ui("Howitzer Sim", windowSize);
    Simulator s(worldSize); 

    // Run the UI with callback
    ui.run(Simulator::callBack, &s);

    return 0;
}
