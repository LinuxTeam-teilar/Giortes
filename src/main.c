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

int auto_close_flag;
int auto_close;

char label_str[labelBUFFER];    /* Flawfinder: ignore */
GtkWidget *main_window;
GtkWidget *vbox;
GtkWidget *label;
GdkPixbuf *pixbuf;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include "init.h"
#include "check.h"
#include "files.h"
#include "help.h"
#include "search.h"
#include "options.h"
#include "dates.h"
#include "gettext.h"

int  quiet;
char no_database;
int  X;

char database[BUFFER];         /* default filenames */    /* Flawfinder: ignore */
char personal[BUFFER];                                    /* Flawfinder: ignore */
char internat[BUFFER];                                    /* Flawfinder: ignore */
char settings[BUFFER];                                    /* Flawfinder: ignore */

int main(int argc, char *argv[])
{
    int c;
    char temp[BUFFER]="";    /* Flawfinder: ignore */
    int search_flag=0;

#ifdef ENABLE_NLS
    setlocale (LC_ALL, "");

#ifdef _WIN32
    char localePath[BUFFER];
    strncpy(localePath, getenv("PROGRAMFILES"), BUFFER);
    strncat(localePath, "\\giortes", BUFFER-strlen(localePath));
    bindtextdomain (PACKAGE, localePath);
#else
    bindtextdomain (PACKAGE, LOCALEDIR);
#endif

    bind_textdomain_codeset(PACKAGE, "UTF-8");
    textdomain (PACKAGE);
#endif

#ifdef GTK_GUI
    gtk_init (&argc, &argv);
#endif
#ifndef NO_GUI
    createMainWindowTopGUI();
#endif

    Initialize();

    while ((c = getopt (argc, argv, "hvkaqn:m:d:x:p:i:sfec:w")) != -1)      /* Flawfinder: ignore */
    {
        switch (c)
        {
        case 'h':
            help();
            return 0;
        case 'v':
            version();
            return 0;
        case 'e':
            calculateEaster();
            return 0;
        case 'a':
            calculateFeast(1);
            search_flag = 1;
            break;
        case 'q':
            quiet=1;
            break;
        case 'n':
            strncpy(temp, optarg, BUFFER);
            if (temp[0] == 'n' || temp[0] == 'p' || temp[0] == 'i' || temp[0] == 'a')
            {
                no_database = temp[0];
            }
            else 
            {
                if (temp[0] != 'h')
                    fprintf(stdout, _("Wrong argument at -n option\n"));
                noDatabaseHelp();
                return 1;
            }
            strncpy(temp, "", BUFFER);
            break;
        case 'm':
            strncpy(temp, optarg, BUFFER);
            if (temp[0] == 'p')
            {
#ifndef NO_GUI
                SettingPersonal();
#else
                createPersonalText();
#endif
            }
            else if (temp[0] == 'i')
            {
#ifndef NO_GUI
                SettingInternat();
#else
                createInternationalDaysText();
#endif
            }
            else if (temp[0] == 'a')
            {
#ifndef NO_GUI
                SettingPersonal();
                SettingInternat();
#else
                createPersonalText();
                createInternationalDaysText();
#endif
            }
            else
            {
                makeDatabaseHelp();
            }
            return 0;
        case 'd':
            strncpy(database, optarg, BUFFER);
            break;
        case 'x':
            strncpy(temp, optarg, BUFFER);
            X = checkNumber(temp, strlen(temp));
            if (X>365)
            {
                while(X>365) X-=365;
                fprintf(stderr, _("\nVery big number at argument -x\nChanging to %d\n"), X);
            }
            if (X<=0)
            {
                fprintf(stderr, _("Can't check %d days later. Changing to 5\n"), X);
                X = 5;
            }
            break;
#ifndef NO_GUI
        case 'c':
            strncpy(temp, optarg, BUFFER);
            auto_close = checkNumber(temp, strlen(temp));
            if (auto_close>120)
            {
                auto_close=120;
                fprintf(stderr, _("\nVery big number at argument -c\nChanging to %d\n"), auto_close);
            }
            if (auto_close<0)
            {
                fprintf(stderr, _("Could not autoexit after %d seconds. Changing to 30\n"), auto_close);
                auto_close = 30;
            }
            if (auto_close==0)
            {
                auto_close_flag = 1;
            }
            break;
#endif
        case 'p':
            strncpy(personal, optarg, BUFFER);
            break;
        case 'i':
            strncpy(internat, optarg, BUFFER);
            break;
        case 's':
            search_flag = 1;
            if (checkFile(database)) return 1;
#ifndef NO_GUI
            SetSearchNameGUI(temp, BUFFER);
#else
            fprintf(stdout, _("Enter the name you are searching: "));
            fgets(temp, BUFFER, stdin);
            temp[BUFFER-1]='\0';
#endif
            search(temp);
            break;
        case 'f':
            if (checkFile(database)) return 1;
            search_flag = 1;
            find(0, 0);
            break;
        case 'w':
            writeOptions();
            return 0;
        default:
            help();
            return 0;
        }
    }

    if (checkFile(database)) return 1;

    if (search_flag == 0){
        if (no_database != 'p' && no_database != 'a') {
            checkPersonal();
        }
        if (no_database != 'i' && no_database != 'a') {
            checkInternationalDays();
        }
        checkAllDays();
    }

#ifndef NO_GUI
    createMainWindowEndGUI();
    if (auto_close_flag == 0){
        g_timeout_add (auto_close*1000, (GSourceFunc) exitProgramGUI, NULL);
    }
#endif
#ifdef GTK_GUI
    gtk_main ();
#endif

    return 0;
}
