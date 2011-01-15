/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef NO_GUI
#include "interface.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "check.h"
#include "dates.h"
#include "files.h"
#include "init.h"
#include "search.h"
#include "options.h"
#include "gettext.h"


int checkNumber(char *num, int size)
{
    int i, temp;
    for (i=0;i<size;i++)
    {
        if (!isdigit(num[i]))
        {
            return -1;
        }
    }
    temp = atoi(num);
    if (temp > INT_MAX || temp < INT_MIN) 
        return -1;
    return temp;
}

void checkKiniti(char *kiniti, int *mera, int *minas, char *onoma)
{
    if (kiniti[0] != '*')
    {
        if ((*mera == 11 && *minas == 12) || strcmp(onoma, "ΧΛΟΗ") == 0)
        {
            if (dayOfWeek(*mera, *minas, current_year) != 0)
            {
                *mera = *mera + (7-(dayOfWeek(*mera, *minas, current_year)));
            }
        }
        else
        {
            *mera = easter_day + atoi(kiniti);      /* Flawfinder: ignore */
            *minas = easter_month;
        }
        while (*mera < 0)
        {
            *mera += monthDays(*minas-1, current_year);
            *minas = *minas-1;
        }
        while (*mera > monthDays(*minas, current_year))
        {
            *mera -= monthDays(*minas, current_year);
            *minas = *minas+1;
        }
        if (strcmp(onoma, "ΓΕΩΡΓΙΑ") == 0 || strcmp(onoma, "ΓΕΩΡΓΙΟΣ") == 0)
        {
            if (easter_day < 24 && easter_month < 5)
            {
                *mera = 23;
                *minas = 4;
            }
        }
        if (strcmp(onoma, "ΜΑΡΚΟΣ") == 0)
        {
            if (easter_day < 24 && easter_month < 5)
            {
                *mera = 25;
                *minas = 4;
            }
        }
    }
}

int checkDate(int mera, int minas, int etos)
{
    if (mera > monthDays(minas, etos))
    {
        return 1;
    }
    return 0;
}

void checkAllDays(void)
{
    int cur_add_day;
    /* Search the database X days after today */
    for (cur_add_day=0; cur_add_day<X; cur_add_day++)
    {

        /* Call the find function with the right arguments */
        find(1, cur_add_day);

    }
}

void checkPersonal(void) {
    FILE *file;

    file = fopen(personal, "r");  /* Flawfinder: ignore */

    if (!file) {
        if (quiet == 0) {
#ifndef NO_GUI
            checkPersonalErrorGUI();
#else
            int i, flag = 0;
            fprintf(stderr, _("\nCould not locate personal database file with filename <%s>.\n"), personal);
            do {
                flag = 0;
                fprintf(stdout, _("Would you like to create the list now? (y/n): "));
                i = getchar();
                getchar();
                if (i == 'y' || i == 'Y') {
                    createPersonalText();
                } else if (i == 'n' || i == 'N') {
                    return;
                } else {
                    fprintf(stderr, _("Wrong selection, please try again.\n"));
                    flag = 1;
                }
            } while (flag == 1);
#endif
        }
        return;
    }
    fclose(file);
}


void checkInternationalDays(void) {
    FILE *file;

    file = fopen(internat, "r");    /* Flawfinder: ignore */

    if (!file) {
        if (quiet == 0) {
#ifndef NO_GUI
        checkInternationalDaysErrorGUI();
#else
            int i, flag = 0;

            fprintf(stderr, _("\nCould not find international days database file with filename <%s>.\n"), internat);
            do {
                flag = 0;
                fprintf(stdout, _("Would you like to create the list now? (y/n): "));
                i = getchar();
                getchar();
                if (i == 'y' || i == 'Y') {
                    createInternationalDaysText();
                } else if (i == 'n' || i == 'N') {
                    return;
                } else {
                    fprintf(stderr, _("Wrong selection, please try again.\n"));
                    flag = 1;
                }
            } while (flag == 1);
#endif
        }
        return;
    }
    fclose(file);
}


int checkFile(char *filename) {
    FILE *temp;

    temp = fopen(filename, "rb");    /* Flawfinder: ignore */
    if (!temp) {
        if (quiet == 0) {
#ifndef NO_GUI
            checkFileErrorGUI(filename);
#else
            fprintf(stderr, _("Could not locate file <%s>.\n"), filename);
#endif
        }
        return 1;
    }
    fclose(temp);
    return 0;
}
