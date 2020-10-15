// File with commands to control the pedestal movement
// Author: Jason Cloete

// Includes
#include "controller.h"

// Function prototypes
char start_azimuth_control(char direction);
char start_elevation_control(char direction);

// Function definitions
void begin_control()
{
    // 1 is the positive direction. 0 is negative.
    if((desired_azimuth - current_azimuth) > 5.0)
    {
        start_azimuth_control(1);
    } else if ((desired_azimuth - current_azimuth) < -5.0) {
        start_azimuth_control(0);
    }

    // 1 is the positive direction. 0 is negative.
    if((desired_elevation - current_elevation) > 5.0)
    {
        start_elevation_control(1);
    } else if ((desired_elevation - current_elevation) < -5.0) {
        start_elevation_control(0);
    }
}

// Azimuth control function
// 0 = RA- | 1 = RA+
char start_azimuth_control(char direction)
{
    char success = 1;

    // Variable declarations
    struct timeval start, end;
    double elapsedTime;

    double difference = desired_azimuth - current_azimuth;
    double time_taken = difference/slew_rate*1000;

    // Measure amount of time spent turning
    gettimeofday(&start, NULL);

    // Turn in direction specified
    if (direction == 0)
    {
        set_pin(6);
    } else if (direction == 1) {
        set_pin(3);
    } else {
        printf("Invalid direction. Select another direction.");
        set_pin(0);
        success = 0;
    }
    

    // End the control function if no valid pin is chosen
    if (success)
    {
        gettimeofday(&end, NULL);
        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        while(elapsedTime < time_taken)
        {
            gettimeofday(&end, NULL);
            elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        }

        set_pin(0);
        gettimeofday(&end, NULL);
        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);

        current_azimuth = slew_rate/1000 * elapsedTime;
        printf("Current Azimuth: %lf\n", current_azimuth);

        // For debugging
        debug_parameters();
        asm("NOP");
    }
    
    return success;
}

// Elevation Control Function
// 0 = DEC+ | 1 = DEC-
char start_elevation_control(char direction)
{
    char success = 1;

    // Variable declarations
    struct timeval start, end;
    double elapsedTime;

    double difference = desired_elevation - current_elevation;
    double time_taken = difference/slew_rate*1000;

    // Measure amount of time spent turning
    gettimeofday(&start, NULL);

    // Turn in direction specified
    if (direction == 0)
    {
        set_pin(5);
    } else if (direction == 1) {
        set_pin(4);
    } else {
        printf("Invalid direction. Select another direction.");
        set_pin(0);
        success = 0;
    }
    

    // End the control function if no valid pin is chosen
    if (success)
    {
        gettimeofday(&end, NULL);
        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        while(elapsedTime < time_taken)
        {
            gettimeofday(&end, NULL);
            elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        }

        set_pin(0);
        gettimeofday(&end, NULL);
        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);

        current_elevation = slew_rate/1000 * elapsedTime;
        printf("Current Elevation: %lf\n", current_elevation);

        // For debugging
        debug_parameters();
        asm("NOP");
    }
    
    return success;
}