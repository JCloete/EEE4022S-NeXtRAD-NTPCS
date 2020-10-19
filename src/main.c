// NeXtRAD NTPCS

// Standard Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// User Includes
#include "pedestal.h"
#include "controller.h"

// Emulation includes
#include "emulator.h"

// Function prototypes
double get_azimuth_input();
double get_elevation_input();

void main()
{
    // Creation of input buffer and answer value
    char input_buffer[256];
    char user_input;

    // System Welcome
    printf("Welcome to NeXtRAD Control System! \n");
    printf("This program was created by Jason Cloete as part of a UCT EBE Final Year Project. \n");
    printf("Are you ready to proceed? y/n \n");

    /*
    // Get User input
    fgets(input_buffer, sizeof(input_buffer) - 1, stdin);
    sscanf(input_buffer, "%c", &user_input);
    */

    // Get user input
    scanf("%c", &user_input);

    // Stop Program
    if (user_input == 'n')
    {
        return;
    }

    printf("Proceeding with Setup. Please Wait...");

    // System setup.
    // set up device drivers and such. Which currently dont exist.
    // Limits and the like would also be setup here.
    pedestal_setup(4.8, 1.0, 0.0, 0.0);

    // Emulation setup
    emulator_setup(0.0, 0.0, 1.0);

    // Thread ID's
    pthread_t tid[2];
    // Thread setup
    int err = pthread_create(&(tid[0]), NULL, runThread, NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");

    // Get initial GPS location
    // Get phone GPS working and perhaps have a config.ini to read our gps position.
    double plat = -33.906718;
    double plong = 18.446167;
    double palt = 1.0;

    double tlat = -33.899073;
    double tlong = 18.443462;
    double talt = 0.0;

    // Set Pedestal Positions
    set_pedestal_position(plat, plong, palt);

    // Set Target Positions
    set_target_position(tlat, tlong, talt);

    // Set Desired Azimuth
    /*
    set_azimuth(354.0, 0);
    set_elevation(20.0, 0);
    printf("Desired Azimuth: %lf\n", desired_azimuth);
    printf("Desired Elevation: %lf\n", desired_elevation);
    */

    double azimuth_input;
    double elevation_input;
    // Generate Control loop
    while(user_input != 'q')
    {
        printf("Control Menu \n");
        printf("--------------------------- \n");
        printf("1 - Manual Control \n");
        printf("2 - Automatic Control \n");
        printf("q - Quit the Program \n");

        /*
        // Get User input
        fgets(input_buffer, sizeof(input_buffer) - 1, stdin);
        sscanf(input_buffer, "%c", &user_input);
        */

        // Get User Input
        scanf(" %c", &user_input);

        if (user_input == '1')
        {
            azimuth_input = get_azimuth_input();
            elevation_input = get_elevation_input();

            set_azimuth(azimuth_input, 0);
            set_elevation(elevation_input, 0);

            start_controller(0);

            printf("Finished Movement. \n");
            debug_parameters();
        } else if (user_input == '2') {
            start_controller(1);
            printf("Finished Movement. \n");
        } else if (user_input == 'q') {
            printf("Quitting out the program! \n");
        } else {
            printf("Invalid Selection. \n");
            while ( (check = getchar()) != EOF && check != '\n' );
        }
    }

    // Debug the pedestal
    debug_parameters();

    // Stop Thread
    pthread_cancel(tid[0]);
}

double get_azimuth_input()
{
    double input;
    char check;
    char valid_input = 0;
    
    while (valid_input != 1)
    {
        printf("Enter an Azimuth Value: ");
        check = scanf(" %lf", &input);

        if (check)
        {
            if (input >= 0.0 && input < 360.0)
            {
                valid_input = 1;
            } else {
                printf("Azimuth out of range! \n");
            }
        } else {
            printf("Invalid input. Enter a valid number. \n");
            while ( (check = getchar()) != EOF && check != '\n' );
        }
    }

    return input;
}

double get_elevation_input()
{
    double input;
    char check;
    char valid_input = 0;
    
    while (valid_input != 1)
    {
        printf("Enter an Elevation Value: ");
        check = scanf(" %lf", &input);

        if (check)
        {
            if (input >= -45.0 && input <= 45.0)
            {
                valid_input = 1;
            } else {
                printf("Elevation out of range! \n");
            }
        } else {
            printf("Invalid input. Enter a valid number. \n");
            while ( (check = getchar()) != EOF && check != '\n' );
        }
    }

    return input;
}

// Testing Azimuth Calcs
    /*
    double azimuth = calculate_azimuth(plat, tlat, plong, tlong);
    double elevation = calculate_elevation(plat, tlat, plong, tlong, 1.0, 0.0);
    printf("Test Azimuth: %f \n", azimuth);
    printf("Test Elevation: %f \n", elevation);
    printf("===================================== \n");
    */

    // Debugging emulator
    /*
    struct timeval start, end;
    double elapsedTime;
    set_pin(3);
    int i = 0;
    while(i < 10)
    {
        gettimeofday(&start, NULL);
        gettimeofday(&end, NULL);

        elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        while(elapsedTime < 1000)
        {
            gettimeofday(&end, NULL);
            elapsedTime = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
        }
        i += 1;
    }
    */