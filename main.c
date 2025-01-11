/*Name: Saurabh Kumar
Description: Address Book Project in which we can  create contact, search contact, delete contact , edit contact, list contact*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <unistd.h>
#include "contact.h"
#include "file.h"
#include <string.h>

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    loadContactsFromFile(&addressBook);// Load the contact's
    printf("------------------------------------------------------------------------------------\n");
    printf("*      Welcome to the Address Book! Please enter the details below       *\n");
    printf("------------------------------------------------------------------------------------\n");

    do {
        // Display menu
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("Select the option given in the above list: ");
        scanf("%d", &choice);
        
        // Perform actions based on the user's choice
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exiting.....\n");
                break;
            default:
                printf("Invalid choice. Please Choose (1 to 7).\n");
        }
    } while (choice != 7); // Loop continues until the user chooses to exit
    
       return 0;
}