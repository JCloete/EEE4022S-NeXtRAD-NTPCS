// Include file for Pedestal controller
// Author: Jason Cloete

#include "direction.h"

// Status Defines

// Pedestal Global Variables
// Pedestal Position
static double pedestal_latitude;
static double pedestal_longitude;
static double pedestal_altitude;

// Target Position
static double target_latitude;
static double target_longitude;
static double target_altitude;

// Current elevation/azimuth
static double current_azimuth;
static double current_elevation;

static double desired_azimuth;
static double desired_elevation;


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
