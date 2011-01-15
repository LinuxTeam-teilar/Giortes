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
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "init.h"
#include "dates.h"
#include "files.h"
#include "options.h"

void Initialize()
{
    char path[BUFFER];
    struct tm sys_date;
    time_t date;
    time(&date);
    sys_date = *localtime(&date);

    quiet = 0;
    X = 5;
    no_database = 'n';

    path[0] = '\0';
#ifdef _WIN32
    strncpy(path, getenv("PROGRAMFILES"), BUFFER);
    strncat(path, "\\giortes", BUFFER-strlen(path));
    strncpy(database, path, BUFFER);
#else
    strncpy(path, getenv("HOME"), BUFFER);
    strncat(path, "/.giortes", BUFFER-strlen(path));
#endif

    strncpy(personal, path, BUFFER);
    strncpy(internat, path, BUFFER);
    strncpy(settings, path, BUFFER);

#ifdef _WIN32
    strncat(database, "\\database.dat", BUFFER-strlen(database));
    strncat(personal, "\\personal.txt", BUFFER-strlen(personal));
    strncat(internat, "\\int_days.txt", BUFFER-strlen(internat));
    strncat(settings, "\\settings.txt", BUFFER-strlen(settings));
#else
    strncpy(database, DATADIR"/database.dat", BUFFER);
    strncat(personal, "/personal.txt", BUFFER-strlen(personal));
    strncat(internat, "/int_days.txt", BUFFER-strlen(internat));
    strncat(settings, "/settings.txt", BUFFER-strlen(settings));
#endif

    current_year = sys_date.tm_year+1900;
    current_day = sys_date.tm_mday;
    current_month = sys_date.tm_mon + 1;
    setTomorrow();
    easter(current_year);

#ifndef NO_GUI
    auto_close_flag=0;
    auto_close=30;
#endif

    readOptions(path);
}
