// These functions are used to calculate the Azimuth and Elevation to be used by the pedestal controlling functions.
#include "direction.h"

double calculate_azimuth(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude)
{
    double azimuth = atan2(target_latitude - pedestal_latitude, target_longitude - pedestal_longitude);
    azimuth = fmod(450 - azimuth * (180.0/M_PI), 360); // Get the compass bearing
    
    return azimuth;
}

double calculate_elevation(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude, double pedestal_altitude, double target_altitude)
{
    double distance = sqrt(pow(target_latitude - pedestal_latitude, 2.0) + pow(target_longitude - pedestal_longitude, 2.0)); // Calculate straight line distance between the 2 points
    double elevation = atan2(target_altitude - pedestal_altitude, distance);
    elevation = elevation * (180.0/M_PI); // Convert from radians to degrees

    return elevation;
}
