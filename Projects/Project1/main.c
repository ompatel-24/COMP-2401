#include <stdio.h>
#include <stdlib.h>

#include "subsystem.h"

#define MENU_ADD 1
#define MENU_PRINT 2
#define MENU_PRINTALL 3
#define MENU_STATUS 4
#define MENU_REMOVE 5
#define MENU_FILTER 6
#define MENU_DATA 7
#define MENU_EXIT 0
#define MENU_MIN 0
#define MENU_MAX 7

int print_menu(int *choice);

int main() {
    SubsystemCollection subsystems;
    subsys_collection_init(&subsystems);

    int choice = -1;

    while (choice != MENU_EXIT) {
        print_menu(&choice);

        if (choice == MENU_ADD) {
            char name[MAX_STR];
            Subsystem subsystem;
            printf("Name of subsystem: \n");
            scanf("%s", name);
            subsys_init(&subsystem, name, 0x0);
            if (subsys_append(&subsystems, &subsystem) == ERR_SUCCESS) {
                printf("Added subsystem %s\n", subsystem.name);
            } else {
                printf("Failed to add subsystem.\n");
            }

        } else if (choice == MENU_PRINT) {
            char name[MAX_STR];
            printf("Name of subsystem to print: \n");
            scanf("%s", name);
            subsys_print(&subsystems.subsystems[subsys_find(&subsystems, name)]);

        } else if (choice == MENU_PRINTALL) {

            subsys_collection_print(&subsystems);

        } else if (choice == MENU_STATUS) {
            char name[MAX_STR];
            int statusID, newValue;
            printf("Enter: <Subsystem Name> <Status ID (7, 6, 5, 4, 3, 2, 1, 0)> <New Value (0 - 3)>\n");
            scanf("%s %d %d", name, &statusID, &newValue);
            subsys_status_set(&subsystems.subsystems[subsys_find(&subsystems, name)], statusID, newValue);

        } else if (choice == MENU_REMOVE) {
            char name[MAX_STR];
            printf("Name of subsystem to remove: \n");
            scanf("%s", name);
            subsys_remove(&subsystems, subsys_find(&subsystems, name));

        } else if (choice == MENU_FILTER) {
            char filter[9];
            printf("Enter filter string (8 chars of 0, 1, or *): \n");
            scanf("%8s", filter);
            SubsystemCollection subsystemsF;
            subsys_collection_init(&subsystemsF);
            subsys_filter(&subsystems, &subsystemsF, (const unsigned char *)filter);
            subsys_collection_print(&subsystemsF);

        } else if (choice == MENU_DATA) {
            char name[MAX_STR];
            unsigned int data = 0;
            printf("Enter <Subsystem Name> <Data, uppercase hex without 0x>: \n");
            scanf("%s %08x", name, &data);
            subsys_data_set(&subsystems.subsystems[subsys_find(&subsystems, name)], data, NULL);
        } else if (choice == MENU_EXIT) {
            break;
        }
    }
    return 0;
}

/* 
    Prints a menu to the user and prompts them until they enter a valid menu option.

    out: *choice, an integer corresponding to a MENU_ definition defining the choice made by the user.

    Returns: 
        - ERR_SUCCESS if there is no error
        - ERR_NULL_POINTER if `choice` is NULL

*/
int print_menu(int *choice) {
    if (choice == NULL) {
        return ERR_NULL_POINTER;
    }

    *choice = 0;

    do {
        printf("\n--- Subsystem Management Menu ---\n");
        printf("%d. Add Subsystem\n", MENU_ADD);
        printf("%d. Print Subsystem\n", MENU_PRINT);
        printf("%d. Print All Subsystems\n", MENU_PRINTALL);
        printf("%d. Set Subsystem Status\n", MENU_STATUS);
        printf("%d. Remove Subsystem\n", MENU_REMOVE);
        printf("%d. Filter Subsystems\n", MENU_FILTER);
        printf("%d. Set Subsystem Data\n", MENU_DATA);
        printf("%d. Exit\n", MENU_EXIT);
        printf("Select an option: ");
        scanf("%d", choice);
        while (getchar() != '\n');

        if (*choice < MENU_MIN || *choice > MENU_MAX) {
            printf("Error: Invalid choice. Please try again.\n");
        }
    } while (*choice < MENU_MIN || *choice > MENU_MAX);

    return ERR_SUCCESS;
}