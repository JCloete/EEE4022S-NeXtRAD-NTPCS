// These functions are used to calculate the Azimuth and Elevation to be used by the pedestal controlling functions.
#include "direction.h"

#define RADIUS_EARTH 6371000.0

double calculate_azimuth(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude)
{
    // Translate coords to rads
    double plat = pedestal_latitude * (M_PI/180.0);
    double tlat = target_latitude * (M_PI/180.0);
    double plong = pedestal_longitude * (M_PI/180.0);
    double tlong = target_longitude * (M_PI/180.0);

    // Great Circle Bearing
    double x = sin(tlong - plong) * cos(tlat);
    double y = cos(plat) * sin(tlat) - sin(plat) * cos(tlat) * cos(tlong - plong);

    double azimuth = atan2(y, x);
    azimuth = fmod(450.0 - azimuth * (180.0/M_PI), 360); // Get the compass bearing
    return azimuth;
}

double calculate_distance(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude)
{
    double plat = pedestal_latitude * (M_PI/180.0);
    double tlat = target_latitude * (M_PI/180.0);
    double plong = pedestal_longitude * (M_PI/180.0);
    double tlong = target_longitude * (M_PI/180.0);

    double distance = 2.0*RADIUS_EARTH*asin(sqrt(sin((tlat - plat)/2.0)*sin((tlat - plat)/2.0) + cos(plat)*cos(tlat)*sin((tlong - plong)/2.0)*sin((tlong - plong)/2.0))); // Calculate straight line distance between the 2 points

    return distance;
}

double calculate_elevation(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude, double pedestal_altitude, double target_altitude)
{
    double distance = calculate_distance(pedestal_latitude, target_latitude, pedestal_longitude, target_longitude);
    double elevation = atan2(target_altitude - pedestal_altitude, distance);
    elevation = elevation * (180.0/M_PI); // Convert from radians to degrees

    return elevation;
}
