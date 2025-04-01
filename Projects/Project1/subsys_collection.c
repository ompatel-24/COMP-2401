#include "subsystem.h"
#include <string.h>

/*
    This file should contain your documentation and implementations for SubsystemCollection 
    specific functionality; initialization, appending, removal, printing, finding, and filtering.
*/

int subsys_collection_init(SubsystemCollection *subsystems) {
    if (subsystems == NULL) {
        return ERR_NULL_POINTER;
    }

    subsystems->size = 0;

    return ERR_SUCCESS;
}

int subsys_append(SubsystemCollection *subsystems, const Subsystem *subsystem) {
    if (subsystems == NULL || subsystem == NULL) {
        return ERR_NULL_POINTER;
    }

    if (subsystems->size >= MAX_ARR) {
        return ERR_MAX_CAPACITY;
    }

    subsystems->subsystems[subsystems->size] = *subsystem;

    subsystems->size++;
    return ERR_SUCCESS;
}

int subsys_find(const SubsystemCollection *subsystems, const char *name) {
    if (subsystems == NULL || name == NULL) { return ERR_NULL_POINTER; }

    for (unsigned int i = 0; i < subsystems->size; i++) {
        if (strcmp(subsystems->subsystems[i].name, name) == 0) {
            return i;
        }
    }

    printf("Subsystem not found\n");
    return ERR_SYS_NOT_FOUND;
}

int subsys_collection_print(SubsystemCollection *subsystems) {
    if (subsystems == NULL) { return ERR_NULL_POINTER; }

    for (unsigned int i =0; i < subsystems->size; i++) {
        subsys_print(&subsystems->subsystems[i]);
    }

    return ERR_SUCCESS;
}

int subsys_remove(SubsystemCollection *subsystems, int index) {
    if (subsystems == NULL) { return ERR_NULL_POINTER; }
    if (subsystems->size == 0) { return ERR_NO_DATA; }
    if ((unsigned int)index >= subsystems->size || index < 0) { return ERR_INVALID_INDEX; }

    for (unsigned int i = index; i < subsystems-> size - 1; i++) {
        subsystems->subsystems[i] = subsystems->subsystems[i + 1];
    }
    subsystems->size--;

    return ERR_SUCCESS;
}

int subsys_filter(const SubsystemCollection *src, SubsystemCollection *dest, const unsigned char *filter) {
    if (src == NULL || dest == NULL || filter == NULL) { return ERR_NULL_POINTER; }

    char filterM = 0;
    char wildCardM = 0;

    for (int i = 0; i < 8; i++) {
        if (filter[i] == '1') {
            filterM = filterM | (0x1 << (7 - i));
        }

        if (filter[i] == '*') {
            wildCardM = wildCardM | (0x1 << (7 - i));
        }
    }

    filterM = ~filterM;

    for (unsigned int i = 0; i < src->size; i++) {
        char finalS = ((filterM) ^ (src->subsystems[i].status)) | wildCardM;

        if (~(finalS) == 0x0) {
            subsys_append(dest, &src->subsystems[i]);
        }
    }

    return ERR_SUCCESS;
}