// NeXtRAD NTPCS

// Standard Includes
#include <stdio.h>

// User Includes
#include "pedestal.h"

// Emulation includes
#include "emulator.h"

void main()
{
    // System setup.
    // set up device drivers and such. Which currently dont exist.
    // Limits and the like would also be setup here.

    // Get initial GPS location
    // Get phone GPS working and perhaps have a config.ini to read our gps position.
    double plat = -33.906718;
    double plong = 18.446167;
    double tlat = -33.899073;
    double tlong = 18.443462;
    
    // Generate Control loop thread

    double azimuth = calculate_azimuth(plat, tlat, plong, tlong);
    double elevation = calculate_elevation(plat, tlat, plong, tlong, 0.0, 0.0);
    printf("Test Azimuth: %f \n", azimuth);
    printf("Test Elevation: %f \n", elevation);
    printf("===================================== \n");

    increase_RA();
}