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
#include "search.h"
#include "files.h"
#include "init.h"
#include "check.h"
#include "print.h"
#include "dates.h"
#include "gettext.h"

int  search_flag;

void search(char* anaz)
{
    FILE *input;
    struct event giorti;
    char filename[BUFFER];    /* Flawfinder: ignore */
    int flag, i, j, thesi=-1;
    int size;

    if (strlen(anaz) < 7) strncpy(anaz, "---", sizeof(anaz));

    /* Check if there is a wildcard character into the search string */
    for (i=0;i<strlen(anaz);i++)
    {
        if (anaz[i]=='*')
        {
            thesi = i;
            break;
        }
    }

    flag = 0;

    input = fopen(database, "rb");    /* Flawfinder: ignore */

    /* Search into the name database for the string provided */
    if (!input)
    {
        if (quiet == 0)
        {
#ifndef NO_GUI
            checkFileErrorGUI(database);
#else
            fprintf(stderr, _("Could not locate database file with name <%s>.\n"), database);
#endif
        }
    }
    else
    {

#ifndef NO_GUI
        strncpy(label_str, "", labelBUFFER);
#endif

        while (!feof(input))
        {
            fread(&giorti, sizeof(struct event), 1, input);
            if (!feof(input))
            {
                if (strncmp(giorti.onoma, anaz, thesi)==0) {
                    checkKiniti(giorti.kiniti, &giorti.mera, &giorti.minas, giorti.onoma);
                    print(giorti);
                    flag = 1;
                }
            }
        }
        fclose(input);

#ifndef NO_GUI
        insertResultIntoLabelGUI();
#endif

    }

    for (j=0;j<2;j++)
    {
        if (j==0) strncpy(filename, personal, BUFFER);
        if (j==1) strncpy(filename, internat, BUFFER);

        input = fopen(filename, "rb");    /* Flawfinder: ignore */

        /* Search into the personal and international days database for the string provided */
        if (!input)
        {
            if (quiet == 0)
            {
#ifndef NO_GUI
            checkFileErrorGUI(database);
#else
                fprintf(stderr, _("Could not locate database file with name <%s>.\n"), filename);
#endif
            }
        }
        else
        {

#ifndef NO_GUI
            strncpy(label_str, "", labelBUFFER);
#endif

            while (!feof(input))
            {
                fgets(giorti.onoma, 200, input);
                if (!feof(input) && giorti.onoma[0]!='#')
                {
                    sscanf(giorti.onoma, "%d %d", &giorti.mera, &giorti.minas);
                    size = strlen(giorti.onoma)-1;
                    for (i=0;i<size-6;i++)
                    {
                        giorti.onoma[i]=giorti.onoma[i+6];
                    }
                    giorti.onoma[i]='\0';
                    strncpy(giorti.paragoga, "", 400);
                    giorti.paragoga[399]='\0';
                    strncpy(giorti.kiniti, "", 4);
                    giorti.kiniti[3]='\0';
                    if (thesi == -1)
                    {
                        if (strcmp(giorti.onoma, anaz)==0)
                        {
                            print(giorti);
                            flag = 1;
                        }
                    }
                    else
                    {
                        if (strncmp(giorti.onoma, anaz, thesi)==0)
                        {
                            print(giorti);
                            flag = 1;
                        }
                    }
                }
            }
            fclose(input);
#ifndef NO_GUI
            insertResultIntoLabelGUI();
#endif
        }
    }

    if ( flag == 0 )
    {

#ifndef NO_GUI
        strncpy(label_str, _("\nSearch returned no results.\n\n"), labelBUFFER);
        insertResultIntoLabelGUI();
#else
        fprintf(stdout, _("\nSearch returned no results.\n\n"));
#endif
    }
}



void find(int flag, int cur_add_day)
{
    FILE *input;

    struct event giorti;
    int max_day, flag1=0;
    int mera, minas, etos;
    int verbose=0;      /* when NOT called by the user (-f parameter) the */
    /* user must not see the results of the search    */

    mera = current_day+cur_add_day;
    minas = current_month;
    etos = current_year;

    if (flag == 0)
    {
        verbose = 1;

#ifndef NO_GUI
        hideMainWindowGUI();
#endif

        do
        {
            flag = 0;
#ifndef NO_GUI
            auto_close_flag = 1;
            getDateForFindGUI(&mera, &minas);
#else
            minas= getDateCLI("month");
            mera = getDateCLI("day");
#endif
            flag = checkDate(mera, minas, current_year);
            if (flag == 1)
            {

#ifndef NO_GUI
                invalidDateMsgGUI();
#else
                fprintf(stderr, _("Please try again.\n"));
#endif

            }
        }
        while (flag == 1);
    }

    while ((max_day=monthDays(minas, etos)) < mera)
    {
        mera-=max_day;
        minas++;
        if (minas > 12)
        {
            minas = 1;
            etos++;
        }
    }

    if (no_database != 'p' && no_database != 'a')
    {
        readFile(personal, mera, minas);
    }

    if (no_database != 'i' && no_database != 'a')
    {
        readFile(internat, mera, minas);
    }

    input = fopen(database, "rb");    /* Flawfinder: ignore */
    if (!input)
    {
        if (flag == 0 && quiet == 1 )
        {
            fprintf(stderr, _("Could not locate database file with name <%s>.\n"), database);
        }
        return;
    }

    flag = 0;

    /* search the database from the beginning till the date we search is bigger*/
    /* than database's readed month+2 (because database is sorted and the max */
    /* celebration which depends on east is 56 days after) */
    while (!feof(input) && flag1==0)
    {
        flag1 = 0;
        fread(&giorti, sizeof(struct event), 1, input);

        /* if a celebration depends an the easter day change it's day/month */
        checkKiniti(giorti.kiniti, &giorti.mera, &giorti.minas, giorti.onoma);

        if (!feof(input))
        {
            if (minas == giorti.minas)
            {
                if (mera == giorti.mera)
                {
                    print(giorti);
                    flag = 1;
                }
            }
            if (minas+2 < giorti.minas)
            {
                flag1 = 1;
            }
        }
    }

    fclose(input);

#ifndef NO_GUI
    insertResultIntoLabelGUI();
    strncpy(label_str, "", labelBUFFER);
#endif

    /* If called with the -f parameter print the "no results" message */
    if (verbose == 1 && flag == 0)
    {
#ifndef NO_GUI
        strncpy(label_str, _("\nSearch returned no results.\n\n"), labelBUFFER);
        insertResultIntoLabelGUI();
#else
        fprintf(stdout, _("\nSearch returned no results.\n\n"));
#endif
    }
}
