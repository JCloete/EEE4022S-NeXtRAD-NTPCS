// File with API commands to control the pedestal

#include "pedestal.h"

char set_azimuth(float angle, char block)
{
    char success;

    if (block)
    {
        printf("Movement is blocked, try again!");
        success = 0;
    } else {
        // Send through azimuth position
    }

    return success;
}

char set_elevation(float angle, char block)
{
    char success;

    if (block)
    {
        printf("Movement is blocked, try again!");
        success = 0;
    } else {
        // Send through elevation position
    }

    return success;
}

