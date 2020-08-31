// Include file for Pedestal controller
// Author: Jason Cloete

// Manual Tweaking of pedestal
char set_azimuth(float pos, char block);
char set_elevation(float pos, char block);
float get_azimuth();
float get_elevation();

// Status updates
char get_status();

// Target functions
char set_target_position(float longitude, float latitude, float MAMSL); // MAMSL = Meters Above Mean Sea Level
char get_target_position();

// Pedestal Targeting Functions
char set_position(float longitude, float latitude, float MAMSL);
int* get_position();
int* get_current_position();

// Tracking functions
char set_tracking(char enable_tracking);
char get_tracking();

// Tolerance Functions
char set_azimuth_tracking_tolerance(float tolerance);
char set_elevation_tracking_tolerance(float tolerance);
char set_tracking_tolerance(float azimuth_tolerance, float elevation_tolerance);
char get_tracking_tolerance();
