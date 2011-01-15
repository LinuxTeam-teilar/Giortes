/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef NO_GUI
#include "interface.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "options.h"
#include "init.h"
#include "check.h"
#include "files.h"
#include "print.h"
#include "gettext.h"

int readOptions(char *path)
{
    FILE *opt;
    char buf[400];    /* Flawfinder: ignore */
    char option[200];    /* Flawfinder: ignore */
    char value[200];    /* Flawfinder: ignore */
    int temp1=0;
    int temp2=0;
    int i, k, buf_len;    /* Flawfinder: ignore */

    opt = fopen(settings, "r");    /* Flawfinder: ignore */

    if (!opt)
    {
        if ( (quiet == 0) && (strcmp(path, "") != 0) )
        {
            fprintf(stderr, _("Could not locate settings file\n"));
            fprintf(stdout, _("Creating folder: %s\n"), path);
#ifdef _WIN32
            mkdir(path);
#else
            mkdir(path, (S_IRWXU | S_IRWXG | S_IRWXO));
#endif

            fprintf(stdout, _("Creating file: %s\n"), personal);
            createPersonalText();
            fprintf(stdout, _("Creating file: %s\n"), internat);
            createInternationalDaysText();
            fprintf(stdout, _("Saving options: %s\n"), settings);
            writeOptions();
        }
        return 1;
    }

    while (!feof(opt))
    {
        fgets(buf, 400, opt);
        buf[399] = '\0';
        if (!feof(opt) && (buf[0]!='#' && buf[0]!='\n'))
        {
            sscanf(buf, "%200s : %200s", option, value);

            /* value may have space, keep string between "" */
            buf_len=strlen(buf);
            for(i=0; i < buf_len && buf[i]!='"'; i++);
            i++;
            for(k=0;i<buf_len&&buf[i]!='"';value[k++]=buf[i++]);

            value[k]='\0';   /* terminate the value string */

            if (strcmp(option, "quiet") == 0)
            {
                if (strcmp(value, "TRUE") == 0)
                {
                    quiet=1;
                }
                else if (strcmp(value, "FALSE") == 0)
                {
                    quiet=0;
                }
                else
                {
                    if (quiet == 0)
                    {
                        fprintf(stderr, _("Invalid value at quiet setting in options file: %s\n"), value);
                    }
                }
            }
            else if (strcmp(option, "show_X_next_days") == 0)
            {
                X = checkNumber(value, strlen(value));
                if (X>365)
                {
                    while(X>365) X-=365;
                    if (quiet == 0)
                    {
                        fprintf(stderr, _("Very big number at show_X_next_days setting in options file: %s\nChanging to %d\n"), value, X);
                    }

                }
                if (X<=0)
                {
                    if (quiet == 0)
                    {
                        fprintf(stderr, _("Invalid value at show_X_next_days setting in options file: %s\n"), value);
                    }
                    X = 5;
                }
            }
            else if (strcmp(option, "name_database_file") == 0)
            {
                strncpy(database, value, BUFFER);
            }
            else if (strcmp(option, "personal_database_file") == 0)
            {
                strncpy(personal, value, BUFFER);
            }
            else if (strcmp(option, "international_days_database_file") == 0)
            {
                strncpy(internat, value, BUFFER);
            }

#ifndef NO_GUI
            else if (strcmp(option, "autoclose_after_X_seconds") == 0)
            {
                auto_close = checkNumber(value, strlen(value));
                if (auto_close == 0)
                {
                    auto_close_flag = 1;
                }
            }
#endif
            else if (strcmp(option, "show_personal_database") == 0)
            {
                if (strcmp(value, "TRUE") == 0)
                {
                    temp1=0;
                }
                else if (strcmp(value, "FALSE") == 0)
                {
                    temp1=1;
                }
                else
                {
                    if (quiet == 0)
                    {
                        fprintf(stderr, _("Invalid value at show_personal_database setting in options file: %s\n"), value);
                    }
                }
            }
            else if (strcmp(option, "show_international_days_database") == 0)
            {
                if (strcmp(value, "TRUE") == 0)
                {
                    temp2=0;
                }
                else if (strcmp(value, "FALSE") == 0)
                {
                    temp2=1;
                }
                else
                {
                    if (quiet == 0)
                    {
                        fprintf(stderr, _("Invalid value at show_international_days_database setting in options file: %s\n"), value);
                    }
                }
            }
            else
            {
                if (quiet == 0)
                {
                    fprintf(stderr, _("Unknown settings in your options file:\n%s\n"), buf);
                }
            }
        }
    }

    if (temp1==1 && temp2==1)
    {
        no_database = 'a';
    }
    else if (temp1==0 && temp2==1)
    {
        no_database = 'i';
    }
    else if (temp1==1 && temp2==0)
    {
        no_database = 'p';
    }
    else no_database = 'n';

    fclose(opt);
    return 0;
}

void writeOptions()
{
    FILE *opt;
    char temp1[6]="TRUE";    /* Flawfinder: ignore */
    char temp2[6]="TRUE";    /* Flawfinder: ignore */

    opt = fopen(settings, "w");    /* Flawfinder: ignore */

    if (!opt)
    {
        if (quiet == 0)
        {
            fprintf(stdout, "Error creating options file <%s>\n", settings);
        }
        return;
    }

    fprintf(opt, "#Σε αυτό το αρχείο μπορείτε να βάλετε τις προεπιλεγμένες ρυθμίσεις.\n");
    fprintf(opt, "#Οι ρυθμίσεις πρέπει να είναι μέσα σε διπλά εισαγωγικά \"\".\n");
    fprintf(opt, "#Οι γραμμές που ξεκινάν με \"#\" παραλείπονται\n\n");
    fprintf(opt, "show_X_next_days : \"%d\"\n", X);
    fprintf(opt, "name_database_file : \"%s\"\n", database);
    fprintf(opt, "personal_database_file : \"%s\"\n", personal);
    fprintf(opt, "international_days_database_file : \"%s\"\n", internat);
    if (no_database == 'a')
    {
        strcpy(temp1, "FALSE");    /* Flawfinder: ignore */
        strcpy(temp2, "FALSE");    /* Flawfinder: ignore */
    }
    else if (no_database == 'p')
    {
        strcpy(temp1, "FALSE");    /* Flawfinder: ignore */
    }
    else if (no_database == 'i')
    {
        strcpy(temp2, "FALSE");    /* Flawfinder: ignore */
    }

    fprintf(opt, "show_personal_database : \"%s\"\n", temp1);
    fprintf(opt, "show_international_days_database : \"%s\"\n", temp2);
    if (quiet == 0)
    {
        strcpy(temp1, "FALSE");    /* Flawfinder: ignore */
    }
    fprintf(opt, "quiet : \"%s\"\n", temp1);
#ifndef NO_GUI
    fprintf(opt, "autoclose_after_X_seconds : \"%d\"\n", auto_close);
#endif

    fclose(opt);
}
