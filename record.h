/*****************************************************************
//
//  NAME:        Tracy Bui
//
//  HOMEWORK:    6
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 3, 2020
//
//  FILE:        record.h
//
//  DESCRIPTION:
//  This file contains the data structure of record for
//  for Project 1.
//
//
****************************************************************/

#include <stdio.h>

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};
