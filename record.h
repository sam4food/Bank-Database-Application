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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This is the header file for homework3b. File contains 
//   structure of record, account number as int, char[30] for
//   owner's name, char[50] for address of the owner, and a 
//   record pointer for the next record. 
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
