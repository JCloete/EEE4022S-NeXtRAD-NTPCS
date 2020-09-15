// File with API commands to control the pedestal
#include <stdio.h>
#include "pedestal.h"

char set_azimuth(double angle, char block)
{
    char success = 0;

    if (block)
    {
        printf("Movement is blocked, try again!");
    } else {
        // TODO: ADD CHECKING OF VALID ANGLES
        desired_azimuth = angle;
        success = 1;
    }

    return success;
}

char set_elevation(double angle, char block)
{
    char success = 0;

    if (block)
    {
        printf("Movement is blocked, try again!");
    } else {
        // TODO: ADD CHECKING OF VALID ANGLES
        desired_elevation = angle;
        success = 1;
    }

    return success;
}

double get_current_azimuth()
{
    return current_azimuth;
}

double get_current_elevation()
{
    return current_elevation;
}

double get_desired_azimuth()
{
    return desired_azimuth;
}

double get_desired_elevation()
{
    return desired_elevation;
}

char get_status()
{
    char status = 0;

    return status;
}

char set_pedestal_position(double latitude, double longitude, double altitude)
{
    char success = 0;

    pedestal_latitude = latitude;
    pedestal_longitude = longitude;
    pedestal_altitude = altitude;

    success = 1;

    return success;
}

double get_pedestal_position(char selection)
{
    double position = -1.0;

    if(selection < 0 || selection > 3)
    {
        printf("Choice out of range. Please choose 0 for print of all. 1 for latitude, 2 for longitude and 3 for altitiude! \n");
    }
    else
    {
        switch(selection) 
        {
            case 0:
                printf("Latitude: %f | Longitude: %f | Altitude: %f\n", pedestal_latitude, pedestal_longitude, pedestal_altitude);
                break;

            case 1:
                printf("Latitude: %f", pedestal_latitude);
                position = pedestal_latitude;
                break;

            case 2:
                printf("Longitude: %f", pedestal_longitude);
                position = pedestal_longitude;
                break;

            case 3:
                printf("Altitude: %f", pedestal_altitude);
                position = pedestal_altitude;
                break;
        }
    }
    
    return position;
}

char set_target_position(double latitude, double longitude, double altitude)
{
    char success = 0;

    // TODO: Add a check for within range of system
    target_latitude = latitude;
    target_longitude = longitude;
    target_altitude = altitude;

    success = 1;

    return success;
}

double get_target_position(char selection)
{
    double position = -1.0;

    if(selection < 0 || selection > 3)
    {
        printf("Choice out of range. Please choose 0 for print of all. 1 for latitude, 2 for longitude and 3 for altitiude! \n");
    }
    else
    {
        switch(selection) 
        {
            case 0:
                printf("Latitude: %f | Longitude: %f | Altitude: %f\n", target_latitude, target_longitude, target_altitude);
                break;

            case 1:
                printf("Latitude: %f", target_latitude);
                position = target_latitude;
                break;

            case 2:
                printf("Longitude: %f", target_longitude);
                position = target_longitude;
                break;

            case 3:
                printf("Altitude: %f", target_altitude);
                position = target_altitude;
                break;
        }
    }
    
    return position;
}