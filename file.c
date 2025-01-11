#include <stdio.h>
#include "file.h"
#include "contact.h"

// Function to save the contacts from the AddressBook to a CSV file
void saveContactsToFile(AddressBook *addressBook) {
    // Open file contact.csv in write mode
    FILE *file = fopen("contact.csv", "w");
    
    // Check if the file was opened successfully
    if (file == NULL) {
        printf("File does't Exist.\n");
        return;
    }

    // Write the number of contacts to the file
    fprintf(file, "%d\n", addressBook->contactCount);

    // Loop through all the contacts in the address book and write them to the file
    for (int i = 0; i < addressBook->contactCount; i++) {
        // Format: name, phone, email
        fprintf(file, "%s, %s, %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    // Close the file after writing
    fclose(file);

    // Confirmation message after successful save
    printf("\nContacts saved successfully......\n");
}

// Function to load contacts from the CSV file into the AddressBook structure
void loadContactsFromFile(AddressBook *addressBook) {
    // Open file .csv in read mode
    FILE *file = fopen("Contact.csv", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("No saved contacts found.\n");
        return;
    }

    // Read the number of contacts saved in the file
    fscanf(file, "%d\n", &addressBook->contactCount);

    // Read each contact's data (name, phone, email) and store in the addressBook structure
    for (int i = 0; i < addressBook->contactCount; i++) {
        // Read and store each contact's name, phone, and email from the file
        fscanf(file, "%[^,], %[^,], %[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    // Close the file after reading
    fclose(file);
}