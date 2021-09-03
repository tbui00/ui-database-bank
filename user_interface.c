/*****************************************************************
//    NAME:        Tracy Bui
//
//    HOMEWORK:    3
//
//    CLASS:       ICS 212
//
//    INSTRUCTOR:  Ravi Narayan
//
//    DATE:        November 3, 2020
//
//    FILE:        user_interface.c
//
//    DESCRIPTION:
//     This file contains the user_interface functions
//     for Project 1. It interacts with the user,
//     manages the customer's bank records stored in
//     their database and will call database functions.
//
//
//  ****************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "record.h"
#include "database.h"
int debugmode;

void getAddress(char address[], int max);
bool prefix(const char *, const char *);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A program start-up function
//                 This function is the entry point into the
//                 application for program execution.
//
//  Parameters:    argc (int) : contains the number of arguments
//                              passed to the program.
//
//                 *argv [char] : a pointer to a string array
//                                holding the actual parameters.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/

int main(int argc, char *argv[])
{
    struct record *start = NULL;

    int accNum;
    int return_Val = 1;
    int error = 0;
    char name[25];
    char address[80];
    char option[10];
    char filename[50];

    if (argc > 1)
    {
        if (argc == 2)
        {
            if (strcasecmp("debug", argv[1]) == 0)
            {
                debugmode = 1;
            }
            else
            {
                error = 1;
            }
        }
        else
        {
            error = 1;
        }
    }

    if (error)
    {
        printf("\n usage: %s [debug]\n", argv[0]);
        exit(1);
    }

    while (return_Val != 0)
    {
        printf("Enter a file to read: ");
        scanf("%s", filename);
        return_Val = readfile(&start, filename);

        if (return_Val == -1)
        {
            printf("ERROR: File could not be found or needs to end with \".txt\"\n");
            return_Val = -1;
        }
        else if (return_Val == 0)
        {
            printf("File was read and loaded onto the list.\n");
            return_Val = 0;
        }
    }

    printf("\nProgram will now start...\n");

    printf("\nHello and welcome to the bank. Here we are able to\n");
    printf("manage your bank records stored in the bank's database.");

    bool work = true;

    while (work)
    {
        printf("\n\nPlease select a menu option below to manage bank records:\n");
        printf("-------------------------------------------------------------\n");
        printf("1. add: Adds a new record\n");
        printf("2. printall: Prints all the records\n");
        printf("3. find: Find record(s) with specified account #\n");
        printf("4. delete: Delete existing record(s) using account #\n");
        printf("5. quit: Quit the program\n");
        printf("-------------------------------------------------------------\n");
        printf("\nEnter option: ");

        scanf("%s", option);

        if (prefix(option, "add") || prefix(option, "1"))
        {
            printf("Add new record option was selected.\n\n");
            printf("Adding a new record..Please wait...\n");
            printf("Enter an account #: ");
            scanf("%d", &accNum);
            getchar();

            if (accNum > 0)
            {
                printf("For name please stay within the 25 characters limit.\n");
                printf("Otherwise your name will not process properly.\n");
                printf("\nEnter a name: ");
                fgets(name, 24, stdin);

                if ((strcmp(name, "\n")) == 0)
                {
                    printf("ERROR: Do not enter only a newline (only white spaces allowed).\n");
                }
                else if (strchr(name, '\t') != NULL)
                {
                    printf("ERROR: Do not use tab (only white spaces allowed).\n");
                }
                else
                {
                    printf("\nFor address, please stay within the 80 characters limit.");
                    printf("\nOtherwise your record will not process properly.");
                    printf("\nWhen you are done entering your adddress, press enter two times.\n");
                    printf("\nEnter address(from empty line to finish): ");
                    getAddress(address, 80);

                    return_Val = 0;
                    return_Val = addRecord(&start, accNum, name, address);

                    if (return_Val != 0)
                    {
                        printf("\nRecord was unable to be added.\n");
                    }
                 }
             }
             else
             {
                 printf("ERROR: Account # needs to be greater than 0. Please try again.\n");
             }
        }
        else if (prefix(option, "printall") || prefix(option, "2"))
        {
            printf("Print all records option was selected.\n");
            printAllRecords(start);
        }
        else if (prefix(option, "find") || prefix(option, "3"))
        {
            printf("Find record option was selected.\n\n");
            printf("Finding a record, account # required...\n");
            printf("Enter an account #: ");
            scanf("%d", &accNum);

            if (accNum > 0)
            {
                return_Val = 11;

                return_Val = findRecord(start, accNum);

                if (return_Val == 1)
                {
                    printf("Acount # %d could not be found in the list.\n", accNum);
                }
                else if (return_Val == 0)
                {
                    printf("Record(s) with account # %d were found.", accNum);
                }
                else if (return_Val == 2)
                {
                    printf("The record list is empty, no records can be found.\n");
                }
            }
            else
            {
                printf("ERROR: Account # needs to be greater than 0. Please try again.\n");
            }
        }
        else if (prefix(option, "delete") || prefix(option, "4"))
        {
            printf("Delete a record option was selected.\n");
            printf("Deleting a record...account # required\n");
            printf("Enter an account #: ");
            scanf("%d", &accNum);

            if (accNum > 0)
            {
                return_Val = -1;

                return_Val = deleteRecord(&start, accNum);

                if (return_Val == 1)
                {
                    printf("Account #: %d does not exist in the list.\n", accNum);
                }
                else if (return_Val == 0)
                {
                    printf("Record(s) with Account # %d was successfully deleted.\n", accNum);
                }
                else if (return_Val == 2)
                {
                    printf("The record list is empty, no records can be deleted.\n");
                }
            }
            else
            {
                printf("ERROR: Account # needs to be greater than 0. Please try again.\n");
            }
        }
        else if (prefix(option, "quit") || prefix(option, "5"))
        {
            printf("Quit option was selected.\n");
            printf("\nThank you for using the bank program");
            printf("\nExiting Bank program now....\n\n");

            return_Val = 1;

            /* writing to file */
            while (return_Val != 0)
            {
                printf("Enter a file name to write to: ");
                scanf("%s", filename);
                return_Val = writefile(start, filename);

                if (return_Val == -1)
                {
                    printf("ERROR: File needs to end with \".txt\"\n");
                    return_Val = -1;
                }
                else if (return_Val == 0)
                {
                    printf("Records were written onto file \"%s\".\n", filename);
                    return_Val = 0;
                }
                else if (return_Val == 2)
                {
                    /* exit loop and exit program because user chose to quit */
                    /* And there is nothing to write into file */
                    return_Val = 0;
                }
            }

            cleanup(&start);

            work = false;
        }
        else
        {
            printf("Invalid menu option. Please try again...\n");
        }
    }

    return 0;
}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   A get address function
//                 This function retrieves the address that the
//                 user enters.
//
//  Parameters:    address [char] : contains the array of characters
//                                  of the address the user inputted.
//
//                 max (int) : the max amount of characters the
//                             user is able to input.
//
//  Return values:  N/A
//
****************************************************************/

void getAddress(char address[], int max)
{
    int length = 0;
    bool work = true;

    while (work)
    {
        while (fgets(address + length, max, stdin))
        {
            if (strlen(address + length) == 1)
            {
                work = false;
            }

            length = strlen(address);
            max = max - length;
        }

        if (max <= 0)
        {
            work = false;
        }
    }

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: getAddress METHOD WAS CALLED.\n");
        printf("Parameters called:\n");
        printf("address: %smax: %d\n", address, max);
        printf("**********************************************\n");
    }
}

/*****************************************************************
//
//  Function name: prefix
//
//  DESCRIPTION:   A prefix comparison function
//                 This function compares characters that the
//                 user entered is equal to corresponding
//                 string or is a prefix of the corresponding
//                 string.
//
//  Parameters:    *pre (char) : contains the character(s) that the
//                               user entered to be compared to.
//
//                 *str (char) : contains the characters of the
//                               string being compared.
//
//  Return values:  0 : success, the character(s) is a prefix of 
//                      the string
//                 -1 : the value was not found 
//
****************************************************************/

bool prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;

    if (debugmode == 1)
    {
        printf("\n**********************************************\n");
        printf("DEBUG MODE: prefix METHOD IS CALLED.\n");
        printf("Parameters called:\npre: %s\n*str: %s\n", pre, str);
        printf("\n**********************************************\n");
    }
}
