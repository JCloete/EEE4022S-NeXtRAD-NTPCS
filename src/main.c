// NeXtRAD NTPCS

// Standard Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// User Includes
#include "pedestal.h"

// Emulation includes
#include "emulator.h"

void main()
{
    // System setup.
    // set up device drivers and such. Which currently dont exist.
    // Limits and the like would also be setup here.
    pedestal_setup(4.8, 1.0, 0.0, 0.0);

    // Emulation setup
    emulator_setup(0.0, 0.0, 1.0);

    // Thread ID's
    pthread_t tid[2];
    // Thread setup
    int err = pthread_create(&(tid[0]), NULL, runThread, NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");

    // Get initial GPS location
    // Get phone GPS working and perhaps have a config.ini to read our gps position.
    double plat = -33.906718;
    double plong = 18.446167;
    double tlat = -33.899073;
    double tlong = 18.443462;

    // Set Desired Azimuth
    set_azimuth(354.0, 0);
    set_elevation(20.0, 0);
    printf("Desired Azimuth: %lf\n", desired_azimuth);
    printf("Desired Elevation: %lf\n", desired_elevation);
    

    // Generate Control loop
    while(1)
    {
        begin_control();
    }

    // Debug the pedestal
    debug_parameters();

    // Stop Thread
    pthread_cancel(tid[0]);
}

// Testing Azimuth Calcs
    /*
    double azimuth = calculate_azimuth(plat, tlat, plong, tlong);
    double elevation = calculate_elevation(plat, tlat, plong, tlong, 1.0, 0.0);
    printf("Test Azimuth: %f \n", azimuth);
    printf("Test Elevation: %f \n", elevation);
    printf("===================================== \n");
    */

    // Debugging emulator
    /*
    struct timeval start, end;
    double elapsedTime;
    set_pin(3);
    int i = 0;
    while(i < 10)
    {
        gettimeofday(&start, NULL);
        gettimeofday(&end, NULL);

        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        while(elapsedTime < 1000)
        {
            gettimeofday(&end, NULL);
            elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        }
        i += 1;
    }
    */