#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "contact.h"
#include "populate.h"
int contactCount;
// Function to initialize the address book
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0; // Initializing contactCount to 0 (no contacts yet)
     populateAddressBook(addressBook);
}
// Function to create and add a new contact
void createContact(AddressBook *addressBook) {
    
       // Pointer to the new contact that will be added
    Contact *newContact = &addressBook->contacts[addressBook->contactCount];

    // Loop for entering valid Name
    do {
        
// Prompt for Name and validate it
        printf("Enter Name: ");
        scanf(" %[^\n]", newContact->name);
        printf("\n");
        if (!valid_name(newContact->name)) {
            continue;
        } else {
            break; // Exit loop if name is valid
        }
    } while (1);

    // Loop for entering valid Phone Number
    do {
        printf("Enter Phone Number: ");
        scanf(" %[^\n]", newContact->phone);
        printf("\n");
        if (!(valid_phone(newContact->phone, addressBook))) {
            continue; // If invalid phone number, prompt again
        } else {
            break; // Exit loop if phone number is valid
        }
    } while (1);

    // Loop for entering valid Email
    do {
        printf("Enter Email: ");
        scanf(" %[^\n]", newContact->email);
        printf("\n");
        if (!valid_email(newContact->email, addressBook)) {
            continue; // If invalid email, prompt again
        } else {
            break; // Exit loop if email is valid
        }
    } while (1);

    // Increment contact count after adding the contact
    addressBook->contactCount++;
    printf("Contact added successfully!\n");
}

// Function to search a contact in the address book
int searchContact(AddressBook *addressBook) {
    // If no contacts exist
    if (addressBook->contactCount == 0) {
        printf("No contacts in the address book.\n");
        return -1;  // Return -1 to indicate no contacts
    }
    
    int choice, result = -1;

    do {
        // Menu for searching by different fields
        printf("\nSearch by:\n1. Name\t2. Phone Number\t3. Email\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        // Handle different search options
        switch (choice) {
            case 1: result = search_by_name(addressBook); break;
            case 2: result = search_by_phone(addressBook); break;
            case 3: result = search_by_email(addressBook); break;
            case 4: printf("Exiting search...\n"); return -1; // Exit search
            default: printf("Invalid choice. Please try again.\n");
        }

        if (result != -1) {
            return result; // Return the index of the found contact
        }
    } while (choice != 4); // Keep asking until the user chooses to exit

    return -1; // Default return value
}

// Function to search contact by Name
int search_by_name(AddressBook *addressBook) {
    char name[50];
    int indices[addressBook->contactCount];  // Array to store indices of matching contacts
    int count = 0;

    printf("\nEnter a Name: ");
    scanf(" %[^\n]", name);
    printf("==========================================================\n");
    printf("S.no\tName\tMobile number\tEmail id\n");
    printf("==========================================================\n");

    // Search through the address book for matching names
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            indices[count++] = i;  // Store index of matching contact
            printf("%d\t%s\t%s\t%s\n", count, addressBook->contacts[i].name,
                   addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("----------------------------------------------------------\n");
        }
    }
    if (count == 0) {
        printf("No contacts found.\n");
        return -1;
    }

    // If multiple matches, prompt user to select one
    if (count == 1) {
        return indices[0];  // Return index of single match
    }
    int choice;
    printf("\nThere are %d contacts found. Select any one (1-%d): ", count, count);
    scanf("%d", &choice);

    if (choice < 1 || choice > count) {
        printf("Invalid choice.\n");
        return -1;
    }

    return indices[choice - 1];  // Return selected index
}

// Function to search contact by Phone Number
int search_by_phone(AddressBook *addressBook) {
    char phone[50];

    printf("Enter a Mobile number: ");
    scanf(" %[^\n]", phone);

    // Search for matching phone numbers
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            printf("\nName: %s, Mobile number: %s, Email id: %s\n",
                   addressBook->contacts[i].name, addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return i;  // Return index of matched contact
        }
    }

    printf("No matches found.\n");
    return -1;
}

// Function to search contact by Email
int search_by_email(AddressBook *addressBook) {
    char email[50];

    printf("Enter an Email ID: ");
    scanf(" %[^\n]", email);

    // Search for matching email addresses
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            printf("\nName: %s, Mobile number: %s, Email id: %s\n",
                   addressBook->contacts[i].name, addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return i;  // Return index of matched contact
        }
    }

    printf("No matches found.\n");
    return -1;
}

// Function to edit a contact's information
void editContact(AddressBook *addressBook) {
    // If no contacts exist, display message and return
    if (addressBook->contactCount == 0) {
        printf("No contacts in the address book.\n");
        return;
    } 

    // Search for contact to edit
    int index = searchContact(addressBook);
    if (index < 0) {
        if (index == -1) {
            printf("Contact not found for editing\n");
            return;
        }
        printf("Contact selected successfully......\n");
    }

    // Menu for choosing what to edit (Name, Phone, Email)
    int choice;
    printf("\nWhat do you want to edit:\n1. Name\n2. Phone Number\n3. Email\n4. Exit\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // To consume the newline character left by scanf

    switch (choice) {
        case 1: 
            char name[50];
            name:
            printf("\nEnter Name to edit: ");
            scanf(" %[^\n]", name);
            if (valid_name(name)) {
                strcpy(addressBook->contacts[index].name, name);
                printf("\nName updated successfully...\n");
            } else {
                goto name;
            }
            break;
        
        case 2: 
            char phone[20];
            mob:
            printf("\nEnter Phone Number to edit: ");
            scanf(" %[^\n]", phone);
            if (valid_phone(phone, addressBook)) {
                strcpy(addressBook->contacts[index].phone, phone);
                printf("\nMobile number updated successfully.....\n");
            } else {
                goto mob;
            }
            break;
        
        case 3: 
            char email[50];
            mail:
            printf("\nEnter Email to update: ");
            scanf(" %[^\n]", email);
            if (valid_email(email, addressBook)) {
                strcpy(addressBook->contacts[index].email, email);
                printf("Mail id updated successfully....\n");
            } else {
                goto mail;
            }
            break;
        
        case 4 :
            return;

        default:
            printf("Invalid choice.\n");
            return;
    }
}

// Function to delete a contact from the address book
void deleteContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts available to delete.\n");
        return;
    }

    // Search for the contact to delete
    int index = search_by_name(addressBook);
    if (index < 0) {
        printf("Contact not found for deleting.\n");
        return;
    }
    
    printf("\nContact deleted successfully......\n");

    // Shift remaining contacts in the array to remove the deleted one
    if (index == addressBook->contactCount - 1) {
        addressBook->contactCount--;
        return;
    }

    for (int i = index; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
}

// Function to list all contacts in the address book
void listContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts in the address book.\n");
        return;
    }

    // Print header for contact list
    printf("------------------------------------------------------------\n");
    printf("%-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("------------------------------------------------------------\n");

    // Print details of each contact
    for (int i = 0; i < addressBook->contactCount; i++) {
        Contact *contact = &addressBook->contacts[i];
        printf("%-20s %-15s %-30s\n", contact->name, contact->phone, contact->email);
        printf("------------------------------------------------------------\n");
    }
}

// Function to validate the Name (Only letters, spaces, and periods allowed)
int valid_name(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != '.' && name[i] != ' ') {
            printf("Error: Invalid name! Only alphabetic characters are allowed.\n");
            return 0;
        }
    }
    return 1;
}

// Function to validate the Phone Number
int valid_phone(const char *phone, AddressBook *addressBook) {
    int i, count = 0;
    for (i = 0; phone[i] != '\0'; i++) {
        if (isdigit(phone[i])) {
            count++;
        }
    }
    if (i != 10) {
        printf("Please enter 10-digit number.\n");
        return 0; // Must be 10 digits
    }
    if (count != 10) {
        printf("Please try again enter digit only.\n");
        return 0;
    }

    // Check for duplicates
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            printf("Contact already found in address book\n");
            return 0;
        }
    }
    return 1;
}

// Function to validate the Email
int valid_email(const char *email, AddressBook *addressBook) {
    int lower = 0;

    // Check if the email contains '@'
    const char *at = strchr(email, '@');
    const char *dot = strstr(email, ".com");

    // Check if '@' exists
    if (at == NULL) {
        printf("\nEntered email id must contain '@'\n\n");
        return 0;
    } else {
        // Ensure alphanumeric character before '@'
        if (!(isalnum(*(at - 1)))) {
            printf("\nEntered email id must contain alphabet or digit before '@' \n\n");
            return 0;
        }
    }

    // Check if '.com' exists in the email
    if (dot == NULL) {
        printf("\nEntered email id must contain '.com'\n\n");
        return 0;
    } else {
        // Ensure an alphabet before '.com'
        if (!(isalpha(*(dot - 1)))) {
            printf("\nEntered email id must contain alphabet before '.com'\n\n");
            return 0;
        }
    }

    // Check for lowercase letters in email
    for (int i = 0; email[i] != '\0'; i++) {
        if (islower(email[i])) {
            lower = 1;
        }
    }

    if (lower == 0) {
        printf("\nEntered email id must contain one lowercase alphabet\n");
        return 0;
    }

    // Check if the email already exists
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            printf("\nEntered email id already exists\n\n");
            return 0;
        }
    }
    return 1; // Email is valid
    
contactCount++;
}

