#include <stdio.h>
#include <stdlib.h>  // stdlib included so that we can use exit() in our tester
#include "readings.h"

// These definitions are in main because they are only here for testing purposes, and shouldn't
// be needed anywhere else!
#define EMF_MAX 5.0
#define EMF_MIN 0.0
#define THERMOMETER_MAX 100.0
#define THERMOMETER_MIN -50.0
#define MICROPHONE_MAX 150.0
#define MICROPHONE_MIN 0.0

/*
    You can use this main control flow for your testing.
    The populate functions are provided, but do not have error
    handling, so you will need to update them to include error handling.

    You may wish to write your own testing as well; we will use a different main() function 
    during assessment.
*/

int handle_not_implemented(int err, char const* fname);

int main() {
    struct Reading reading;
    struct ReadingCollection readings;
    struct Device emf, thermometer, microphone;
    int err;

    // Setup our test devices
    err = init_device(&emf, "EMF", EMF_MAX, EMF_MIN);
    err = handle_not_implemented(err, "init_device()");
    
    err = init_device(&thermometer, "Thermometer", THERMOMETER_MAX, THERMOMETER_MIN);
    err = init_device(&microphone, "Microphone", MICROPHONE_MAX, MICROPHONE_MIN);

    // We will start by creating a single reading and printing it
    // Then move on to adding them to the collection.

    err = init_reading(&reading, &emf, 1.5, "Living Room");
    err = handle_not_implemented(err, "init_reading()");

    err = print_reading(&reading);
    err = handle_not_implemented(err, "print_reading()");

    // Initialize our collections by passing pointers to our stack-allocated structures.
    err = init_reading_collection(&readings);
    err = handle_not_implemented(err, "init_reading_collection()");

    err = add_reading(&readings, reading);
    err = handle_not_implemented(err, "add_reading()");

    // Continue with the rest.
    init_reading(&reading, &thermometer, 23, "Living Room");
    add_reading(&readings, reading);
    init_reading(&reading, &microphone, 32, "Living Room");
    add_reading(&readings, reading);

    init_reading(&reading, &emf, 4.1, "Kitchen");
    add_reading(&readings, reading);
    init_reading(&reading, &emf, 4.1, "Kitchen");
    add_reading(&readings, reading);

    init_reading(&reading, &thermometer, -3, "Basement");
    add_reading(&readings, reading);
    init_reading(&reading, &thermometer, -21, "Basement");
    add_reading(&readings, reading);

    // Let's try some invalid values!
    err = init_reading(&reading, &thermometer, THERMOMETER_MAX + 1, "Invalid Room");
    if (err != ERR_INVALID_VALUE) {
        printf("[X] init_reading did not fail with invalid value (thermo max)!\n");
    }
    err = init_reading(&reading, &thermometer, THERMOMETER_MIN - 1, "Invalid Room");
    if (err != ERR_INVALID_VALUE) {
        printf("[X] init_reading did not fail with invalid value! (thermo min)\n");
    }
    err = init_reading(&reading, &emf, EMF_MIN - 1, "Invalid Room");
    if (err != ERR_INVALID_VALUE) {
        printf("[X] init_reading did not fail with invalid value! (emf min)\n");
    }

    // Now we'll add a bunch of duplicate readings to see if we reach out max capacity.
    init_reading(&reading, &emf, 4.5, "Room of Mirrors");

    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    add_reading(&readings, reading);
    err = add_reading(&readings, reading); // Should be one too many!

    if (err != ERR_MAX_CAPACITY) {
        printf("[X] add_reading did not fail with max capacity!\n");
    }
    
    err = print_reading_collection(&readings);
    err = handle_not_implemented(err, "print_reading_collection()");

    // Side Quest
    err = remove_duplicates(&readings);
    err = handle_not_implemented(err, "remove_duplicates()");

    printf("Side Quest: Removing duplicate entries...\n");
    print_reading_collection(&readings);
}

/* 
    Exits the program with a nice message if the function we're testing has not been implemented.

    in err: The error code we want to check.
    in fname: The name of the function we're testing.

    returns: The error code that was sent in, if it is not ERR_NOT_IMPLEMENTED.
*/
int handle_not_implemented(int err, char const* fname) {
    if (err == ERR_NOT_IMPLEMENTED) {
        printf("Function: [%s] is not implemented, exited tester.\n", fname);
        exit(0);
    }

    return err;   
}