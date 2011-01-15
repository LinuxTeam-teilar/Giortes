/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef DATES_H_INCLUDED
#define DATES_H_INCLUDED

void setTomorrow(void);
int  monthDays(int, int);
int  leapYear(int);
int  dayOfWeek(int, int, int);
int  getDateCLI(char *);

void easter(int);
void calculateEaster(void);

void feastDays(int);
void calculateFeast(int);

int current_day, current_month, current_year;
int tomorrow_day, tomorrow_month;
int after_tomorrow_day, after_tomorrow_month;
char past[20];                 /* contain the last date got printed */      /* Flawfinder: ignore */
int  easter_day;               /* easter day   */
int  easter_month;             /* easter month */

#endif // DATES_H_INCLUDED
