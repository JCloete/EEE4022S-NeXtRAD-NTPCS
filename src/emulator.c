// This file emulates the functionality of the AZ/EQ-G Mount
#include "emulator.h"

#include "pedestal.h"

// Emulated Variables
double emulated_azimuth;
double emulated_elevation;

// Emulated Rate
double emulated_slew_rate = 4.8;
double emulated_rate_multiplier;

// Emulation of the pins. 1 = increase, 0 = decrease
char RA1_pin;
char RA0_pin;
char DEC1_pin;
char DEC0_pin;

// Function declarations
void increase_RA(void);
void decrease_RA(void);
void increase_DEC(void);
void decrease_DEC(void);

// Function used to emulate a RPi Pin being set high
// Pin 6 = RA- | Pin 5 = DEC- | Pin 4 = DEC+ | Pin 3 = RA+ | Pin 0 = Reset all to zero
void set_pin(char pin)
{
    if (pin == 6)
    {
        RA1_pin = 0;
        DEC1_pin = 0;
        DEC0_pin = 0;
        RA0_pin = 1;
    } else if (pin == 5){
        RA1_pin = 0;
        RA0_pin = 0;
        DEC1_pin = 0;
        DEC0_pin = 1;
    } else if (pin == 4){
        RA1_pin = 0;
        DEC0_pin = 0;
        RA0_pin = 0;
        DEC1_pin = 1;
    } else if (pin == 3){
        DEC1_pin = 0;
        DEC0_pin = 0;
        RA0_pin = 0;
        RA1_pin = 1;
    } else {
        RA1_pin = 0;
        DEC1_pin = 0;
        DEC0_pin = 0;
        RA0_pin = 0;
        //printf("Resetting all Pins!\n");
    }
}

// This function sets up the emulator
void emulator_setup(double starting_azimuth, double starting_elevation, double starting_emulated_rate_multiplier)
{
    emulated_azimuth = starting_azimuth;
    emulated_elevation = starting_elevation;
    emulated_rate_multiplier = starting_emulated_rate_multiplier;

    RA1_pin = 0;
    RA0_pin = 0;
    DEC1_pin = 0;
    DEC0_pin = 0;
}

// This is the function that starts emulation of the pedestal
void *runThread(void *vargp)
{
    struct timeval start, end;
    double elapsedTime;
    while(1)
    {
        // Get start of while loop
        gettimeofday(&start, NULL);

        increase_RA();
        decrease_RA();
        increase_DEC();
        decrease_DEC();
        //printf("Em_Azi: %lf\n", emulated_azimuth);
        
        // Check if 1 milisecond has elapsed
        // Potentially Implement error correction
        gettimeofday(&end, NULL);
        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        while(elapsedTime < 1.0)
        {
            gettimeofday(&end, NULL);
            elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        }

        // Testing of accuracy of timing.
        // printf("Elapsed Time: %lf \n", elapsedTime);
    }
}

void increase_RA(void)
{
    if(RA1_pin && !RA0_pin)
    {
        emulated_azimuth += emulated_slew_rate*emulated_rate_multiplier/1000.0;

        // Check for Wrap Around
        if (emulated_azimuth >= 360.0)
        {
            emulated_azimuth -= 360.0;
        }
    }
}

void decrease_RA(void)
{
    if(!RA1_pin && RA0_pin)
    {
        emulated_azimuth -= emulated_slew_rate*emulated_rate_multiplier/1000.0;

        // Check for Wrap Around
        if (emulated_azimuth < 0.0)
        {
            emulated_azimuth += 360.0;
        }
    }
}

void increase_DEC(void)
{
    if(DEC1_pin && !DEC0_pin)
    {
        emulated_elevation += emulated_slew_rate*emulated_rate_multiplier/1000.0;
    }
}

void decrease_DEC(void)
{
    if(!DEC1_pin && DEC0_pin)
    {
        emulated_elevation -= emulated_slew_rate*emulated_rate_multiplier/1000.0;
    }
}

void debug_parameters(void)
{
    printf("============================================================================================ \n");
    printf("EMULATOR DEBUG INFORMATION \n");
    printf("----------------------------- \n");
    printf("Reported Azimuth: %lf\n", current_azimuth);
    printf("Reported Elevation: %lf\n", current_elevation);
    printf("Emulated Azimuth: %lf\n", emulated_azimuth);
    printf("Emulated Elevation: %lf\n", emulated_elevation);
    // printf("Pins = RA-: %d | RA+: %d | DEC-: %d | DEC+: %d |\n", RA0_pin, RA1_pin, DEC0_pin, DEC1_pin);
    printf("============================================================================================ \n");
}