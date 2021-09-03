/*****************************************************************
//    NAME:        Tracy Bui
//  
//    HOMEWORK:    6
//
//    CLASS:	   ICS 212
//
//    INSTRUCTOR:  Ravi Narayan
//
//    DATE:        November 3, 2020
//  
//    FILE:        database.h
//
//    DESCRIPTION:
//     This file contains the database headers for the database.c
//     source file for Project 1.
//
//
//  ****************************************************************/

#include <stdio.h>

int addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
int writefile(struct record *, char []);
void cleanup(struct record **);
