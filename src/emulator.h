// Access to the functions

void set_pin(char pin);
void setup(double starting_azimuth, double starting_elevation, double starting_emulated_rate_multiplier);
void *runThread(void *vargp);

void debug_parameters(void);