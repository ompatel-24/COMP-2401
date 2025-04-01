#include "subsystem.h"
#include <string.h>

/*
    This file should contain the implementations for Subsystem specific functionality.
    Initialization, printing, setting and getting data and statuses.
*/

int subsys_init(Subsystem *subsystem, const char *name, char status) {
    if (subsystem == NULL || name == NULL) {
        return ERR_NULL_POINTER;
    }

    strncpy(subsystem->name, name, MAX_STR);
    subsystem->status = status;
    subsystem->data = 0;

    return ERR_SUCCESS;
}

int subsys_print(Subsystem *subsystem) {
    if (subsystem == NULL) { return ERR_NULL_POINTER; }

    subsys_status_print(subsystem);

    return ERR_SUCCESS;
}

int subsys_status_set(Subsystem *subsystem, unsigned char status, unsigned char value) {
    if (subsystem == NULL) { return ERR_NULL_POINTER; }
    if (value > 3) { return ERR_INVALID_STATUS; }

    if (status == STATUS_POWER) {
        if (value > 1) { return ERR_INVALID_STATUS; }
        subsystem->status = (subsystem->status & ~(0x1 << 7)) | (value << 7);
    } else if (status == STATUS_DATA) {
        if (value > 1) { return ERR_INVALID_STATUS; }
        subsystem->status = (subsystem->status & ~(0x1 << 6)) | (value << 6);
    } else if (status == STATUS_ACTIVITY) {
        if (value > 1) { return ERR_INVALID_STATUS; }
        subsystem->status = (subsystem->status & ~(0x1 << 5)) | (value << 5);
    } else if (status == STATUS_ERROR) {
        if (value > 1) { return ERR_INVALID_STATUS; }
        subsystem->status = (subsystem->status & ~(0x1 << 4)) | (value << 4);
    } else if (status == STATUS_PERFORMANCE) {
        subsystem->status = (subsystem->status & ~(0x3 << 2)) | (value << 2);
    } else if (status == STATUS_RESOURCE) {
        subsystem->status = (subsystem->status & ~(0x3)) | value;
    } else {
      return ERR_INVALID_STATUS;
    }

    return ERR_SUCCESS;
}

int subsys_status_print(const Subsystem *subsystem) {
    if (subsystem == NULL) { return ERR_NULL_POINTER; }

    int pwr = (subsystem->status & (0x1 << 7)) >> 7;
    int data = (subsystem->status & (0x1 << 6)) >> 6;
    int act = (subsystem->status & (0x1 << 5)) >> 5;
    int err = (subsystem->status & (0x1 << 4)) >> 4;
    int perf = (subsystem->status & (0x3 << 2)) >> 2;
    int res = subsystem->status & 0x3;
    unsigned int bigData = 0;

    if (data == 1) {
        if (subsys_data_get((Subsystem *)subsystem, &bigData) != ERR_SUCCESS) {
            bigData = 0;
        }
        printf("Name: %15s, Status: ( PWR: %d | DATA: %d | ACT: %d | ERR: %d | PERF: %d | RES: %d ), Data: %08X\n", subsystem->name, pwr, data, act, err, perf, res, bigData);
    } else {
        printf("Name: %15s, Status: ( PWR: %d | DATA: %d | ACT: %d | ERR: %d | PERF: %d | RES: %d )\n", subsystem->name, pwr, data, act, err, perf, res);
    }

    return ERR_SUCCESS;
}

int subsys_data_set(Subsystem *subsystem, unsigned int new_data, unsigned int *old_data) {
    if (subsystem == NULL) { return ERR_NULL_POINTER; }

    if (old_data != NULL) {
      *old_data = subsystem->data;
    }

    subsystem->data = new_data;
    subsystem->status = (subsystem->status & ~(0x1 << 6)) | (0x1 << 6);

    return ERR_SUCCESS;
}

int subsys_data_get(Subsystem *subsystem, unsigned int *data) {
    if (subsystem == NULL) { return ERR_NULL_POINTER; }
    if (data == NULL) { return ERR_NULL_POINTER; }

    if (!(subsystem->status & (0x1 << 6))) {
        *data = 0;
        return ERR_NO_DATA;
    }

    *data = subsystem->data;
    subsystem->data = 0;
    subsystem->status = subsystem->status & ~(0x1 << 6);

    return ERR_SUCCESS;
}