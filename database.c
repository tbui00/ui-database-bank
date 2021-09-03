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
//    FILE:        database.c
//
//    DESCRIPTION:
//     This file contains the database.c functions for Project 1.
//     It contains the database functions that will execute
//     all the necessary methods that the user_interface
//     calls.
//
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record.h"
#include "database.h"
extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   An add record function
//                 This function will add a new record to
//                 the list.
//
//  Parameters:    **start (record) : contains the address of 
//                                    "start".
//
//                 uaccountno (int) : contains the account # that
//                                the user inputted.
//
//                 uname [char] : contains the name that the
//                               user inputted.
//
//                 uaddress [char] : contains the address that
//                                  the user inputted.
//
//  Return values:  0 : success
//                  1 : the value was not found
//
****************************************************************/

int addRecord(struct record **start, int uaccountno, char uname[ ], char uaddress[ ])
{
    struct record *current;
    struct record *prev;
    struct record *new;
    int location = 1;
    int added = 1;

    current = NULL;
    prev = NULL;

    new = (struct record *)malloc(sizeof(struct record));

    new->accountno = uaccountno;
    strcpy(new->name, uname);
    strcpy(new->address, uaddress);
    new->next = NULL;

    /* list is empty */
    if (*start == NULL)
    {
        *start = new;
        added = 0;
    }
    else
    {
        current = *start;

        /* traverse through list and find location to insert new record */
        while (current != NULL && location == 1)
        {
            /* if location to insert is found correctly */
            if (current->accountno <= new->accountno)
            {
                location = 0;
            }
            else
            {
                /* continue to search */
                prev = current;
                current = current->next;
            }
        }

        if (current == *start)
        {
            new->next = *start;
            *start = new;
            added = 0;
        }
        else
        {
            new->next = current;
            prev->next = new;
            added = 0;
        }
    }

    if (added == 0)
    {
        printf("Record with account # %d was added to list.\n", uaccountno);
    }

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: addRecord METHOD WAS CALLED.\n");
        printf("Parameters called:\n");
        printf("uaccountno: %d\n", uaccountno);
        printf("uname: %s\n", uname);
        printf("uaddress: %s\n", uaddress);
        printf("**********************************************\n");
    }

    return added;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   A find record function
//                 This function finds record(s) with a specified
//                 account # in the list.
//
//  Parameters:    *start (record) : contains the address to the
//                                   linked list.
//
//                 accNum (int) : contains the account # of the user.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/

int findRecord(struct record *start, int accNum)
{
    struct record *current;
    int found = 1;

    current = NULL;

    if (start == NULL)
    {
        found = 2;
    }
    else
    {
        current = start;

        while (current != NULL)
        {
            if (current != NULL && current->accountno == accNum)
            {
                printf("\nRecord Information:\n");
                printf("Account #: %d\n", current->accountno);
                printf("Name: %s\n", current->name);
                printf("Address: %s\n", current->address);
                found = 0;
            }
            else if (current == NULL)
            {
                found = 1;
            }

            current = current->next;
        }
    }

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: findRecord method was called.\n");
        printf("Parameters called:\naccNum: %d\n", accNum);
        printf("**********************************************\n");
    }

    return found;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   A print all records function
//                 This function will print all the records
//                 in the list.
//
//  Parameters:    *start (record) : contains the address to the
//                                   linked list.
//
//  Return values:  N/A
//
****************************************************************/

void printAllRecords(struct record *start)
{
    struct record *temp;

    temp = start;

    if (temp == NULL)
    {
        printf("The record list is empty, unable to print empty list.\n");
    }
    else
    {
        printf("\nAll of the records in the list:");

        while (temp != NULL)
        {
            printf("\n\nAccount #: %d\n", temp->accountno);
            printf("Name: %s\nAddress: %s", temp->name, temp->address);
            temp = temp->next;
        }
    }

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: printAllRecords method was called.\n");
        printf("**********************************************\n");
    }
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   A delete record function
//                 This function will delete an existing record(s)
//                 stored in the list with a specified account #.
//
//  Parameters:    **start (record) : contains the address of
//                                    "start".
//
//                 accNum (int) : contains the account # of the user.
//
//  Return values:  0 : success
//                  1 : the value was not found
//                  2 : the list is empty
//
****************************************************************/

int deleteRecord(struct record **start, int accNum)
{
    struct record *current;
    struct record *prev;
    int return_Val = 2;
    int count = 0;
    current = NULL;
    prev = NULL;

    /* empty list */
    if (*start == NULL)
    {
        return_Val = 2;
    }
    else
    {
        current = *start;

        while (current != NULL)
        {
            while (current != NULL && current->accountno != accNum)
            {
                prev = current;
                current = current->next;
            }

            if (current != NULL && current == *start && (*start)->accountno == accNum)
            {
                *start = (*start)->next;
                free(current);
                count++;
            }
            else if (current != NULL && current->accountno == accNum)
            {
                prev->next = current->next;
                free(current);
                current = prev->next;
                count++;
            }
            else if (current == NULL)
            {
                return_Val = 1;
                count = -1;
            }
        }
    }

    if (count >= 1)
    {
        return_Val = 0;
    }
    else if (count == -1)
    {
        return_Val = 1;
    }

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: deleteRecord METHOD WAS CALLED.\n");
        printf("Parameters called:\naccNum: %d\n", accNum);
        printf("**********************************************\n");
    }

    return return_Val;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   A read file function
//                 This function will read from a file and store
//                 the records into the list.
//
//  Parameters:    **start (record) : contains the address of
//                                    "start".
//
//                 filename [char]: contains the name of the file.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/

int readfile(struct record **start, char filename[])
{
    char *end_ext = strrchr(filename, '.');
    int check = strcmp(end_ext, ".txt");
    int return_Val = 0;
    int uaccountno = 0;
    char uaccountno1[21];
    char uname[26];
    char uaddress[81];
    FILE *fileptr;
    fileptr = fopen(filename, "r");

    if (fileptr == NULL || check != 0)
    {
        return_Val = -1;
    }
    else if (fileptr != NULL && check == 0)
    {
        while (fscanf(fileptr, "%20[^\n]%*c%25[^\n]%*c%80[^\n]%*c", uaccountno1, uname, uaddress) != EOF)
        {
            uaccountno = atoi(uaccountno1);
            addRecord(start, uaccountno, uname, uaddress);
        }

        fclose(fileptr);
        return_Val = 0;
    }

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: readfile METHOD WAS CALLED.\n");
        printf("Parameters called:\nfilename: %s\n", filename);
        printf("**********************************************\n");
    }

    return return_Val;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   A write file function
//                 This function will write all data stored in the
//                 list into a text file.
//
//  Parameters:    *start (record) : contains the address to the
//                                   linked list.
//
//                 filename [char]: contains the name of the file.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//                  2 : The list is empty so nothing can be written
//
****************************************************************/

int writefile(struct record *start, char filename[])
{
    char *end_ext = strrchr(filename, '.');
    int check = strcmp(end_ext, ".txt");
    struct record *current;
    int return_Val = 1;
    FILE *fileptr;
    fileptr = fopen(filename, "w");

    current = NULL;

    if (fileptr == NULL || check != 0)
    {
        return_Val = -1;
    }
    else if (start == NULL)
    {
        printf("There is nothing in the list to be written.\n");
        return_Val = 2;
    }
    else if (fileptr != NULL && check == 0)
    {
        current = start;

        while (current != NULL)
        {
            fprintf(fileptr, "%d\n%s\n%s\n", current->accountno, current->name, current->address);
            current = current->next;
        }

        fclose(fileptr);
        return_Val = 0;
    }

    if (debugmode == 1)
    {
        printf("**********************************************\n");
        printf("DEBUG MODE: writefile METHOD WAS CALLED.\n");
        printf("Parameters called:\nfilename: %s\n", filename);
        printf("**********************************************\n");
    }

    return return_Val;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   A cleanup function
//                 This function will release all allocated space
//                 in the heap memory and assign NULL to start.
//
//  Parameters:    **start (record) : contains the address of
//                                    "start".
//
//  Return values:  N/A
//
****************************************************************/

void cleanup(struct record **start)
{
    struct record *temp;

    temp = *start;

    while (temp != NULL)
    {
        free(temp);
        temp = temp->next;
    }

    *start = NULL;

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: cleanup METHOD WAS CALLED.\n");
        printf("**********************************************\n");
    }
}
