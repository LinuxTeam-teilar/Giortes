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
#include "init.h"
#include "dates.h"
#include "gettext.h"

void print(struct event giorti)
{
    char current[20];    /* Flawfinder: ignore */

    if (giorti.mera == current_day && giorti.minas == current_month)
    {
        snprintf(current, sizeof(current), _("Today:"));
    }
    else if (giorti.mera == tomorrow_day && giorti.minas == tomorrow_month)
    {
        snprintf(current, sizeof(current), _("Tomorrow:"));
    }
    else if (giorti.mera == after_tomorrow_day && giorti.minas == after_tomorrow_month)
    {
        snprintf(current, sizeof(current), _("Two days after: "));
    }
    else
    {
        snprintf(current, sizeof(current), _("On %d/%d: "), giorti.mera, giorti.minas);
    }

#ifndef NO_GUI
    fillLabelGUI(giorti, current);
#else
    if (strcmp(current, past)!=0)
    {
        fprintf(stdout, "\n%s\n", current);
    }
    fprintf(stdout, "\t%s ", giorti.onoma);
    fprintf(stdout, "%s\n", giorti.paragoga);
#endif

    strncpy(past, current, 20);
    past[19] = '\0';
}
