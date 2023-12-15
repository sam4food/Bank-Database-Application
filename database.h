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
//  FILE:        database.h
//
//  DESCRIPTION:
//   This is the header file for database and its functions.
//
****************************************************************/

void addRecord(struct record **, int, char[ ], char[ ]);
void printAllRecords(struct record *);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char[ ]);
int readfile(struct record **, char[ ]);
void cleanup(struct record **);
