// File with API commands to control the pedestal
#include "pedestal.h"

// ==================================================================================================================
// System Control
char pedestal_setup(double starting_slew_rate, double starting_rate_multiplier, double starting_current_azimuth, double starting_current_elevation)
{
    char success = 0;

    current_azimuth = starting_current_azimuth;
    current_elevation = starting_current_elevation;
    slew_rate = starting_slew_rate; // Default value for this thesis is 4.8 degrees
    rate_multiplier = starting_rate_multiplier; // Default value is 1X

    // Default Tolerances
    azimuth_tolerance = 1.0;
    elevation_tolerance = 0.05;

    // Successfully setup pedestal
    success = 1;
    return success;
}

// ==================================================================================================================
// Manual Tweaking of pedestal
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

// ==================================================================================================================
// Status updates
// 0 = Ready for command | 1 = Tracking | 2 = Moving | 
char get_status()
{
    char status = 0;

    return status;
}

// ==================================================================================================================
// Pedestal Targeting Functions
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

// ==================================================================================================================
// Target functions
// Sets the targets position.
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

// ==================================================================================================================
// Tracking functions
char set_desired_tracking(void)
{
    char success = 0;

    desired_azimuth = calculate_azimuth(pedestal_latitude, target_latitude, pedestal_longitude, target_longitude);
    target_distance = calculate_distance(pedestal_latitude, target_latitude, pedestal_longitude, target_longitude);
    desired_elevation = calculate_elevation(pedestal_latitude, target_latitude, pedestal_longitude, target_longitude, pedestal_altitude, target_altitude);

    printf("Calculated Desired Azimuth: %lf\n", desired_azimuth);
    printf("Calculated Distance: %lf\n", target_distance);
    printf("Calculated Desired Elevation: %lf\n", desired_elevation);

    success = 1;
    return success;
}