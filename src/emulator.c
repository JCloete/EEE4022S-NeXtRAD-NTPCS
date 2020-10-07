// This file emulates the functionality of the AZ/EQ-G Mount
#include <unistd.h>
#include <sys/time.h>
#include "emulator.h"

// Emulated Variables
double emulated_azimuth;
double emulated_elevation;

// Emulated Rate
double slew_rate;
double rate_multiplier;

// Emulation of the pins. 1 = increase, 0 = decrease
char RA1_pin;
char RA0_pin;
char DEC1_pin;
char DEC0_pin;

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
        printf("Not a valid pin");
    }
}

void setup(double starting_azimuth, double starting_elevation, double starting_rate_multiplier)
{
    emulated_azimuth = starting_azimuth;
    emulated_elevation = starting_elevation;
    rate_multiplier = starting_rate_multiplier;

    RA1_pin = 0;
    RA0_pin = 0;
    DEC1_pin = 0;
    DEC0_pin = 0;
}

// This is the function that starts emulation of the pedestal
void run(void)
{
    while(1)
    {
        increase_RA();
        decrease_RA();
        increase_DEC();
        decrease_DEC();
    }
}

void increase_RA(void)
{
    while(RA1_pin && !RA0_pin)
    {
        emulated_azimuth += slew_rate*rate_multiplier/1000;
        usleep(1000);
    }
}

void decrease_RA(void)
{
    while(!RA1_pin && RA0_pin)
    {
        emulated_azimuth -= slew_rate*rate_multiplier/1000;
        usleep(1000);
    }
}

void increase_DEC(void)
{
    while(DEC1_pin && !DEC0_pin)
    {
        emulated_elevation += slew_rate*rate_multiplier/1000;
        usleep(1000);
    }
}

void decrease_DEC(void)
{
    while(!DEC1_pin && DEC0_pin)
    {
        emulated_elevation -= slew_rate*rate_multiplier/1000;
        usleep(1000);
    }
}