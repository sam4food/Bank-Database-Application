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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   The user interface file for Project1.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
void getaddress(char[], int);
#include "record.h"
#include "database.h"

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Is the user interface that manages the
//                 records for the database and gives users 
//                 instructions on how to use the menu. 
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//                 -1 : ended 
//
****************************************************************/

int debugMode = 0;

int main(int argc, char* argv[])
{
    struct record* start = NULL;
    char name[30];
    char address[50];
    char buffer[100];
    char option[10] = "blank";
    int accountnum = 0;

    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugMode = 1;
        printf("\ndebugMode is on\n");
    }

    else if (argc > 1)
    {
        printf("\nInvalid option, try again please.\n");
        return -1;
    }

    else
    {
        printf("\ndebugMode is off\n");
    }

    printf("\n------------Welcome to the Bank Database Application------------\n\n");
    readfile(&start, "records.txt");

    while (strncmp(option, "quit", strlen(option)) != 0)
    {
        int track;
        int index = 0;

        printf("\nBelow are the possible options:\n");
        printf("\nadd: adds a new record in the database.\n");
        printf("printall: prints all records in the database.\n");
        printf("find: find record(s) with specified account #.\n");
        printf("delete: delete existing record(s) from database using account # as a key.\n");
        printf("quit: quits the program.\n");

        printf("\n---------Choose an option---------\n");
        scanf("%s", option);
        fgets(buffer, 100, stdin);

        if (strncmp(option, "quit", strlen(option)) == 0)
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: User Input %s\n", option);
            }

            printf("Thank you, come again\n");
        }

        else if (strncmp(option, "add", strlen(option)) == 0)
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: User Input %s\n", option);
            }

            printf("------Please Enter Account Number------\n");

            do
            {
                scanf("%d", &accountnum);
                if (accountnum < 1)
                {
                    printf("ErrorMessage: Invalid Input. Enter positive integer\n");
                }
                fgets(buffer, 100, stdin);
            }
            while (accountnum < 1);

            printf("------Please Enter Account Owner's Name------\n");
            while (((track = fgetc(stdin))) != '\n')
            {
                if (index < 29)
                {
                    name[index] = track;
                    index++;
                }
            }
            name[strcspn(name, "\n")] = 0;

            printf("------Please Enter Address------\n");
            getaddress(address, 50);

            addRecord(&start, accountnum, name, address);
            if (debugMode == 1)
            {
                printf("\nDebugMsg: Added %s as a new account with address %s\n", name, address);
            }
            printf("\nA new account has been added\n");
        }

        else if (strncmp(option, "printall", strlen(option)) == 0)
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: User Input %s\n", option);
            }

            if (start == NULL)
            {
                printf("\nThere is no records. List empty.\n");
            }
            else
            {
                printf("Below are all the records:\n");
                printAllRecords(start);
            }
        }

        else if (strncmp(option, "find", strlen(option)) == 0)
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: User Input %s\n", option);
            }

            printf("------Enter Account Number to Find------\n");

            do
            {
                scanf("%d", &accountnum);

                if (debugMode == 1)
                {
                    printf("DebugMsg: Searching for account number %d\n", accountnum);
                }

                if (accountnum <1)
                {
                    printf("ErrorMessage: Invalid Input. Enter positive integer\n");
                }
                fgets(buffer, 100, stdin);
            }
            while (accountnum < 1);

            if (findRecord(start, accountnum) == 0)
            {
                printf("The record was not found.\n");
            }
            else
            {
                printf("The record was found");
            }
        }

        else if (strncmp(option, "delete", strlen(option)) == 0)
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: User Input %s\n", option);
            }

            printf("------Enter Account Number to Delete------\n");

            do
            {
                scanf("%d", &accountnum);
                if (debugMode == 1)
                {
                    printf("DebugMsg: Searching to delete account number %d\n", accountnum);
                }
                if (accountnum < 1)
                {
                    printf("ErrorMessage: Invalid Input. Enter positive integer\n");
                }
                fgets(buffer, 100, stdin);
            }
            while (accountnum < 1);
            if (deleteRecord(&start, accountnum) != 0)
            {
                printf("\nRecord does not exist\n");
            }
            else
            {
                printf("\nRecord deleted successfully\n");
            }
        }

        else
        {
            if (debugMode == 1)
            {
                printf("DebugMsg: User Input %s\n", option);
            }

            printf("Invalid option, try again using the available options listed below:\n");
            printf("\nadd, printall, find, delete, quit\n");
        }
        accountnum = 0;
    }

    writefile(start, "records.txt");
    cleanup(&start);
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   This is the getaddress function and it
//                 takes an address that was inputed by the user.
//
//  Parameters:    str (char[]) : Address location
//                 length (int) : Length of array
//
//  Return values:  void 
//
****************************************************************/

void getaddress(char str[], int length)
{
    char bufferr[50];
    char letter;
    int tracker = 0;

    printf("Type \'/\' when finished\n");
    printf("Exceeding address size will cause address to be cut off.\n");

    while (letter != '/' && tracker < 50)
    {
        letter = fgetc(stdin);
        if (letter != '/')
        {
            strncat(bufferr, &letter, 1);
        }
    }
    if (tracker > 49)
    {
        printf("WARNING! Max address size reached");

        while (letter != '\n' && letter != EOF)
        {
            letter = fgetc(stdin);
        }
    }

    if (debugMode == 1)
    {
        printf("\nDebugMsg: %s was saved\n", bufferr);
        if (tracker > 49)
        {
            printf("Maximum address size was reached. Address was cut off\n");
        }
    }

    strncpy(str, bufferr, length);
    return;
}
