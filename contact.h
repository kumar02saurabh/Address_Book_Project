#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;


//All Function Declaration
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
int search_by_name(AddressBook *addressBook);
int search_by_phone(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);
int valid_name(const char*name);
int valid_phone(const char*phone,AddressBook*);
int valid_email(const char*email,AddressBook*);

#endif