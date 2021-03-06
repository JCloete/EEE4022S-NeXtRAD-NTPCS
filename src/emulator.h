// Access to the functions
#ifndef EMULATOR_H
#define EMULATOR_H

// Includes
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void set_pin(char pin);
void emulator_setup(double starting_azimuth, double starting_elevation, double starting_emulated_rate_multiplier);
void *runThread(void *vargp);

void debug_parameters(void);

#endif /* EMULATOR_H */