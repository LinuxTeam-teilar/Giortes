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
#include "init.h"
#include "dates.h"
#include "search.h"
#include "gettext.h"

void setTomorrow(void)
{
    tomorrow_day = current_day + 1;
    tomorrow_month = after_tomorrow_month = current_month;
    if (tomorrow_day > monthDays(tomorrow_month, current_year))
    {
        tomorrow_day -= monthDays(tomorrow_month, current_year);
        tomorrow_month++;
        if (tomorrow_month > 12)
        {
            tomorrow_month = 1;
        }
    }

    after_tomorrow_day = current_day + 2;
    if (after_tomorrow_day > monthDays(after_tomorrow_month, current_year))
    {
        after_tomorrow_day -= monthDays(after_tomorrow_month, current_year);
        after_tomorrow_month++;
        if (after_tomorrow_month > 12)
        {
            after_tomorrow_month = 1;
        }
    }
}

int monthDays(int month, int year)
{
    if (month == 2)
    {
        if (leapYear(year) == 1)
            return 29;
        return 28;
    }
    if (month == 4 || month == 6 || month == 9 ||month == 11)
        return 30;
    else
        return 31;
}

int leapYear(int year)
{
    if (((year % 4 == 0 ) && (year % 100 !=0 )) || (year % 400 == 0))
        return 1;
    return 0;
}

int dayOfWeek(int mera, int minas, int xronos)
{
    int psifia = (xronos%10) + ((xronos/10)%10)*10;
    int temp = (int) psifia/4;
    int temp1=0;
    switch (minas)
    {
    case 1 :
        if (leapYear(xronos) == 1) temp1 = 6;
        else temp1 = 0;
        break;
    case 2 :
        if (leapYear(xronos) == 1) temp1 = 2;
        else temp1 = 3;
        break;
    case 3 :
    case 11 :
        temp1 = 3;
        break;
    case 4 :
    case 7 :
        temp1 = 6;
        break;
    case 5 :
        temp1 = 1;
        break;
    case 6 :
        temp1 = 4;
        break;
    case 8 :
        temp1 = 2;
        break;
    case 9 :
    case 12 :
        temp1 = 5;
        break;
    case 10 :
        temp1 = 0;
        break;
    }
    return (6+psifia+temp+temp1+mera)%7;
}


int getDateCLI(char *temp)
{
    char temp1[BUFFER];    /* Flawfinder: ignore */
    int flag = 0, i=0;
    int value=0;

    do
    {
        flag = 0;
        if (strcmp(temp, "month") == 0)
            fprintf(stdout, _("\nPlease enter the number of month: "));
        else if (strcmp(temp, "day") == 0)
            fprintf(stdout, _("\nPlease enter the number of day: "));
        else if (strcmp(temp, "year") == 0)
            fprintf(stdout, _("\nPlease enter the number of year: "));

        fgets(temp1, BUFFER, stdin);
        temp1[BUFFER-1] = '\0';
        for (i=0; i<strlen(temp1)-1; i++)
        {
            if (!isdigit(temp1[i]))
            {
                fprintf(stderr, _("\nPlease, type a number.\n"));
                flag = 1;
                break;
            }
        }
        if (flag==0)
        {
            value=atoi(temp1);    /* Flawfinder: ignore */
            if ((strcmp(temp, "day") == 0) && ((value>31) || value<1))
            {
                fprintf(stderr, _("\nPlease, type a valid number (1 to 31)"));
                flag = 1;
            }
            if ((strcmp(temp, "month") == 0) && ((value>12) || value<1))
            {
                fprintf(stderr, _("\nPlease, type a valid number (1 to 12)"));
                flag = 1;
            }
            if ((strcmp(temp, "year") == 0) && ((value>2099) || value<1901))
            {
                fprintf(stderr, _("\nPlease, type a valid number (1901 to 2099)"));
                flag = 1;
            }
        }
    }
    while (flag==1);

    return value;
}

void easter(int etos)
{
    easter_month = 4;
    easter_day = ((19*(etos%19)+16)%30)+((2*(etos%4))+(4*(etos%7))+(6*((19*(etos%19)+16)%30)))%7+3;

    if (easter_day>monthDays(easter_month, etos))
    {
        easter_day -= monthDays(easter_month, etos);
        easter_month++;
    }
}

void calculateEaster()
{
    int i;
    char temp[BUFFER];    /* Flawfinder: ignore */
#ifndef NO_GUI
    auto_close_flag = 1;
    i = getYearGUI();
    if (i == 0){
        showMainWindowGUI();
        return;
    }
#else
    i = getDateCLI("year");
#endif
    easter(i);
    if (easter_month == 4)
    {
        strncpy(temp, _("April"), BUFFER);
    }
    else
    {
        strncpy(temp, _("May"), BUFFER);
    }
#ifndef NO_GUI
    printEasterGUI(i, easter_day, temp);
#else
    fprintf(stdout, "\nOrthodox easter of year %d is at %d of %s\n\n", i, easter_day, temp);
#endif
    return;
}

void feastDays(int i)
{
#ifndef NO_GUI
    printFeastDaysGUI(i);
#else
    fprintf(stdout, "\nΣτις 1/1:\n");
    fprintf(stdout, "\tΠΡΩΤΟΧΡΟΝΙΑ\n");
    fprintf(stdout, "\nΣτις 6/1:\n");
    fprintf(stdout, "\tΘΕΟΦΑΝΕΙΑ\n");
    search("ΚΑΘΑΡΑ ΔΕΥΤΕΡΑ");
    fprintf(stdout, "\nΣτις 25/3:\n");
    fprintf(stdout, "\tΕΛΛΗΝΙΚΗ ΕΠΑΝΑΣΤΑΣΗ ΤΟΥ 1821\n");
    search("ΜΕΓΑΛΗ ΔΕΥΤΕΡΑ");
    search("ΜΕΓΑΛΗ ΠΑΡΑΣΚΕΥΗ");
    fprintf(stdout, "\nΣτις 1/5:\n");
    fprintf(stdout, "\tΠΡΩΤΟΜΑΓΙΑ\n");
    search("ΤΟΥ ΑΓΙΟΥ ΠΝ*");
    fprintf(stdout, "\nΣτις 15/8:\n");
    fprintf(stdout, "\tΚΟΙΜΗΣΕΩΣ ΤΗΣ ΘΕΤΟΚΟΥ\n");
    fprintf(stdout, "\nΣτις 28/10:\n");
    fprintf(stdout, "\tΕΠΕΤΕΙΟΣ ΤΟΥ ΟΧΙ\n");
    fprintf(stdout, "\nΣτις 25/12:\n");
    fprintf(stdout, "\tΓΕΝΝΗΣΗΣ ΤΟΥ ΧΡΙΣΤΟΥ\n");
    fprintf(stdout, "\nΣτις 26/12:\n");
    fprintf(stdout, "\tΔΕΥΤΕΡΗ ΜΕΡΑ ΤΩΝ ΧΡΙΣΤΟΥΓΕΝΝΩΝ\n");
#endif
}

void calculateFeast(int a)
{
    int i;

#ifndef NO_GUI
    auto_close_flag = 1;
    i = getYearGUI();
    if (i == 0){
        showMainWindowGUI();
        return;
    }
#else
    i = getDateCLI("year");
#endif


#ifndef NO_GUI
    createMainWindowTopGUI();
#endif

    easter(i);
    current_year = i;
    feastDays(i);

#ifndef NO_GUI
    if (a == 0)
    {
        createMainWindowEndGUI();
    }
#endif

    return;
}
