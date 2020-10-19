// These functions are used to calculate the Azimuth and Elevation to be used by the pedestal controlling functions.
#ifndef DIRECTION_H
#define DIRECTION_H

#include <math.h>

double calculate_azimuth(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude);
double calculate_distance(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude);
double calculate_elevation(double pedestal_latitude, double target_latitude, double pedestal_longitude, double target_longitude, double pedestal_altitude, double target_altitude);

#endif /* DIRECTION_H */