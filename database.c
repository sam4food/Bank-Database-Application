/*****************************************************************
//
//  NAME:        Samuel Yang
//
//  HOMEWORK:    Project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 23, 2023
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   File for Project1 database
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
extern int debugMode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds record to database.
//
//  Parameters:    database (struct record**) : Pointer to a pointer to the database.
//                 accountnumber (int) : The account number.
//                 name (char[]) : Account owner name.
//                 address (char[]) : Account owner address.
//
//  Return values:  void
//
****************************************************************/

void addRecord(struct record** database, int accountnumber, char name[], char address[])
{
    struct record* newRecord;
    struct record* checker;
    checker = *database;
    while (checker != NULL)
    {
        if (checker->accountno == accountnumber)
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: Account number exists already\n");
            }
            printf("Duplicate accounts are not allowed.\n");
            return;
        }
        checker = checker->next;
    }
    if (debugMode == 1)
    {
        printf("\nDebugMsg: addRecord was called");
        printf(" with the account number: %d,", accountnumber);
        printf(" with the name: %s,", name);
        printf(" and the address: \n%s\n", address);
    }
    newRecord = (struct record*)malloc(sizeof(struct record));
    newRecord->accountno = accountnumber;
    strncpy(newRecord->name, name, 30);
    strncpy(newRecord->address, address, 50);

    if (*database == NULL || accountnumber > (*database)->accountno)
    {
        struct record* temp;
        temp = *database;
        *database = newRecord;
        (*database)->next = temp;
    }
    else
    {
        struct record* currRecord;
        struct record* nexRecord;

        currRecord = (*database)->next;
        nexRecord = *database;

        while (currRecord != NULL && accountnumber < currRecord->accountno)
        {
            currRecord = currRecord->next;
            nexRecord = nexRecord->next;
        }
        nexRecord->next = newRecord;
        newRecord->next = currRecord;
    }
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all the records
//
//  Parameters:    database (struct record*) : pointer to the database 
//
//  Return values:  void
//
****************************************************************/

void printAllRecords(struct record* database)
{
    struct record* currRecord = database;
    if (debugMode == 1)
    {
        printf("\nDebugMsg: printAllRecords was called\n");
    }

    while (currRecord != NULL)
    {
        printf("--------------\n");
        printf("Account Number: %d\n", currRecord->accountno);
        printf("Account Owner: %s\n", currRecord->name);
        printf("Account Owner Address: %s\n", currRecord->address);
        printf("--------------\n");
        currRecord = currRecord->next;
    }
    printf("Records have been printed\n");

    if (debugMode == 1)
    {
        printf("\nDebugMsg: printAllRecords has been completed\n");
    }

    return;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds record and returns 0 or 1 for if an account exists
//
//  Parameters:    database (struct record*) : Pointer to the database.
//                 accountnumber (int) : The account number.
//
//  Return values:  0 : account number doesn't exist 
//                  1 : account number exists
//
****************************************************************/

int findRecord(struct record* database, int accountnumber)
{
    struct record* curr = database;
    int success = 0;

    if (debugMode == 1)
    {
        printf("\nDebugMsg: findRecord was called with the account number %d\n", accountnumber);
    }

    while (curr != NULL)
    {
        if (curr->accountno == accountnumber)
        {
            printf("\nAccount Number: %d\n", curr->accountno);
            printf("Account Owner: %s\n", curr->name);
            printf("Account Owner Address: %s\n", curr->address);
            success = 1;
        }
        curr = curr->next;
    }
    if (debugMode == 1)
    {
        printf("\nDebugMsg: findRecord completed.\n");
    }

    return success;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes record in database for account number.
//
//  Parameters:    database (struct record**) : Pointer to a pointer to the database.
//                 accountnumber (int) : The account number.
//
//  Return values:  0 : remove record successful
//                 -1 : remove record failed. No such record.
//
****************************************************************/

int deleteRecord(struct record** database, int accountnumber)
{
    struct record* curr;
    struct record* prev;
    struct record* after;
    int success = -1;

    if (debugMode == 1)
    {
        printf("\nDebugMsg: deleteRecord was called with the account number %d", accountnumber);
    }

    if (*database != NULL)
    {
        curr = *database;
        prev = NULL;

        do
        {
            after = curr->next;
            if (curr->accountno == accountnumber)
            {
                success = 0;

                if ((*database)->accountno == accountnumber)
                {
                    *database = after;
                    curr->next = NULL;
                    free(curr);
                    curr = *database;
                }
                else
                {
                    prev->next = after;
                    curr->next = NULL;
                    free(curr);
                }
                curr = after;
            }
            else
            {
                prev = curr;
                curr = after;
            }
        }
        while (curr != NULL);
        printf("Record was deleted");
    }
    if (debugMode == 1)
    {
        printf("\nDebugMsg: deleteRecord completed\n");
    }
    return success;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Saves the records into a file.
//
//  Parameters:    database (struct record*) : Pointer to the database.
//                 filename (char []) : Name of file.
//
//  Return values:  0 : file opened successfully
//                 -1 : file failed to open
//
****************************************************************/

int writefile(struct record* database, char filename[])
{
    int success = 0;
    FILE *file;
    if ((file = fopen(filename, "w")) == NULL)
    {
        success = -1;
    }
    else
    {
        while (database != NULL)
        {
            fprintf(file, "%d\n", database->accountno);
            fprintf(file, "%s\n", database->name);
            fprintf(file, "%s/", database->address);
            database = database->next;
        }
        fclose(file);
    }
    if (debugMode == 1)
    {
        printf("\nDebugMsg: writefile was called. Finished writing records\n");
    }
    return success;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Retrieves the records from the saved file.
//
//  Parameters:    database (struct record*) : Pointer to the database.
//                 filename (char []) : Name of file.
//
//  Return values:  0 : file opened successfully
//                 -1 : file failed to open
//
****************************************************************/

int readfile(struct record** database, char filename[])
{
    int success = 0;
    FILE *file;
    if (debugMode == 1)
    {
        printf("\nDebugMsg: readfile called. Reading from %s\n", filename);
    }
    if ((file = fopen(filename, "r")) == NULL)
    {
        success = -1;
    }
    else
    {
        int numbers;
        while (fscanf(file, "%d", &numbers) != EOF)
        {
            char names[30] = "";
            char addresses[50] = "";
            int index = 0;
            char letter;
            fgetc(file);
            fgets(names, 30, file);
            names[strlen(names) - 1] = '\0';
            while ((letter = fgetc(file)) != '/')
            {
                addresses[index] = letter;
                index++;
            }
            addRecord(database, numbers, names, addresses);
        }
        fclose(file);
    }
    if (debugMode == 1)
    {
        printf("\nDebugMsg: All records have been read. readfile complete.\n");
    }
    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Releases all allocated spaces in heap memory.
//
//  Parameters:    database (struct record**) : Pointer to a pointer to the database.
//
//  Return values:  void
//
****************************************************************/

void cleanup(struct record** database)
{
    while (*database != NULL)
    {
        struct record* temp;
        temp = (*database)->next;
        (*database)->next = NULL;
        free(*database);
        *database = temp;
    }
    return;
}
