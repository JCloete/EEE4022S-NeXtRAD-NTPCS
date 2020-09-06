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
        // TODO: ADD CHECKING OF VALID ANGLES
        target_azimuth = angle;
    }

    return success;
}

char set_elevation(float angle, char block)
{
    char success = 0;

    if (block)
    {
        printf("Movement is blocked, try again!");
    } else {
        // TODO: ADD CHECKING OF VALID ANGLES
        target_elevation = angle;
        success = 1;
    }

    return success;
}

float get__current_azimuth()
{
    return current_azimuth;
}

float get_current_elevation()
{
    return current_elevation;
}

float get_target_azimuth()
{
    return target_azimuth;
}

float get_target_elevation()
{
    return target_elevation;
}

char get_status()
{
    char status = 0;

    return status;
}