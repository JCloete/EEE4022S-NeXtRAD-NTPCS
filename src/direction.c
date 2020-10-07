// These functions are used to calculate the Azimuth and Elevation to be used by the pedestal controlling functions.
#include "direction.h"

#define RADIUS_EARTH 6371000.0

double calculate_azimuth(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude)
{
    double azimuth = atan2(target_latitude - pedestal_latitude, target_longitude - pedestal_longitude);
    azimuth = fmod(450 - azimuth * (180.0/M_PI), 360); // Get the compass bearing

    return azimuth;
}

double calculate_elevation(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude, double pedestal_altitude, double target_altitude)
{
    double plat = pedestal_latitude * (M_PI/180.0);
    double tlat = target_latitude * (M_PI/180.0);
    double plong = pedestal_longitude * (M_PI/180.0);
    double tlong = target_longitude * (M_PI/180.0);
    
    double distance = 2.0*RADIUS_EARTH*asin(sqrt(sin((tlat - plat)/2.0)*sin((tlat - plat)/2.0) + cos(plat)*cos(tlat)*sin((tlong - plong)/2.0)*sin((tlong - plong)/2.0))); // Calculate straight line distance between the 2 points
    double elevation = atan2(target_altitude - pedestal_altitude, distance);
    elevation = elevation * (180.0/M_PI); // Convert from radians to degrees

    return elevation;
}
