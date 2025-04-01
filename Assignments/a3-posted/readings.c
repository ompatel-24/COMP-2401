#include <stdio.h>
#include <string.h>
#include "readings.h"

int init_device(struct Device *device, char *name, float max, float min) {
    for (int i = 0; i < MAX_STR; i++) {
        device->name[i] = name[i];
    }

    device->max = max;
    device->min = min;

    return ERR_OK;
}

int init_reading(struct Reading *reading, struct Device *device, float value, char const* room) {
    reading->device = device;
    reading->value = value;

    valid_device_reading(device, value);

    for (int i = 0; i < MAX_STR; i++) {
        reading->room[i] = room[i];
    }

    return ERR_OK;
}

int valid_device_reading(struct Device *device, float value) {
    if (value > device->max || value < device->min) {
        return ERR_INVALID_VALUE;
    }

    return ERR_OK;
}

int init_reading_collection(struct ReadingCollection *readings) {
    readings->size = 0;

    return ERR_OK;
}

int add_reading(struct ReadingCollection *readings, struct Reading reading) {
    if (readings->size >= MAX_READINGS) {
        return ERR_MAX_CAPACITY;
    }

    readings->elements[readings->size] = reading;
    readings->size = readings->size + 1;

    return ERR_OK;
}

int print_reading(const struct Reading *reading) {
    printf("Reading: ", reading->device->name, reading->value, reading->room);
    return ERR_OK;
}

int print_reading_collection(struct ReadingCollection *readings) {
    for (int i = 0; i < readings->size; i++) {
        print_reading(&readings->elements[i]);
    }

    return ERR_OK;
}

// Side Quest Function
int remove_duplicates(struct ReadingCollection *readings) {
    return ERR_NOT_IMPLEMENTED;
}