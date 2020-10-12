// Include file for Pedestal controller
// Author: Jason Cloete
#ifndef PEDESTAL_H
#define PEDESTAL_H

#include "direction.h"

// Status Defines

// Pedestal Global Variables
// Pedestal Position
double pedestal_latitude;
double pedestal_longitude;
double pedestal_altitude;

// Target Position
double target_latitude;
double target_longitude;
double target_altitude;

// Current elevation/azimuth
double current_azimuth;
double current_elevation;

double desired_azimuth;
double desired_elevation;

// Characteristics
double slew_rate;
double rate_multiplier;


// Manual Tweaking of pedestal
char set_azimuth(double pos, char block);
char set_elevation(double pos, char block);
double get_current_azimuth();
double get_current_elevation();
double get_desired_azimuth();
double get_desired_elevation();

// Status updates
char get_status();

// Pedestal Targeting Functions
char set_pedestal_position(double latitude, double longitude, double altitude);
double get_pedestal_position(char selection);

// Target functions
char set_target_position(double latitude, double longitude, double altitude); // MAMSL = Meters Above Mean Sea Level
double get_target_position(char selection);

// Tracking functions
char set_tracking(char enable_tracking);
char get_tracking();

// Tolerance Functions
char set_azimuth_tracking_tolerance(double tolerance);
char set_elevation_tracking_tolerance(double tolerance);
char set_tracking_tolerance(double azimuth_tolerance, double elevation_tolerance);
char get_tracking_tolerance();

#endif /* PEDESTAL_H */
