/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include "gettext.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

void makeDatabaseHelp()
{
    fprintf(stdout, "\n-m argument usage : ");
    fprintf(stdout, "\t-m [a|p|i|h]");
    fprintf(stdout, "\n-m a");
    fprintf(stdout, "\n\ta : create all databases");
    fprintf(stdout, "\n-m p");
    fprintf(stdout, "\n\tp : create the personal database");
    fprintf(stdout, "\n-m i");
    fprintf(stdout, "\n\ti : create the international days database");
    fprintf(stdout, "\n-m h");
    fprintf(stdout, "\n\th : shows this help\n");
    fprintf(stdout, "\nTo change the default name of the databases to be\ncreated use -p and/or -i before -m argument.\n");
}

void noDatabaseHelp()
{
    fprintf(stdout, "\n-n argument usage : ");
    fprintf(stdout, "\t-n [a|p|i|n|h]");
    fprintf(stdout, "\n-n a");
    fprintf(stdout, "\n\ta : block all databases ecxept main (name database)");
    fprintf(stdout, "\n-n p");
    fprintf(stdout, "\n\tp : block the personal database");
    fprintf(stdout, "\n-n i");
    fprintf(stdout, "\n\ti : block the international days database");
    fprintf(stdout, "\n-n n");
    fprintf(stdout, "\n\tn : do not block any database (default)");
    fprintf(stdout, "\n-n h");
    fprintf(stdout, "\n\th : shows this help\n");
}

void help()
{
    fprintf(stdout, "\n\n\tUsage : ");
    fprintf(stdout, "\tGiortes [OPTIONS]\n\n");
    fprintf(stdout, "OPTIONS\n");
    fprintf(stdout, "\t-h : show this help\n");
    fprintf(stdout, "\t-v : show version and exit\n");
    fprintf(stdout, "\t-e : calculate Orthodox Easter Sunday\n");
    fprintf(stdout, "\t-a : display year's holidays\n");
    fprintf(stdout, "\t-q : quiet mode, do not show any messages\n");
    fprintf(stdout, "\t-n [a|p|i|n|h] : exclude databases from view (see -n h for more help)\n");
    fprintf(stdout, "\t-m [a|p|i|h] : create databases (see -m h for more help)\n");
    fprintf(stdout, "\t-x integer : check 'integer' days after current date (default 5)\n");
    fprintf(stdout, "\t-d file : set the database filename\n");
    fprintf(stdout, "\t-p file : set the personal database filename\n");
    fprintf(stdout, "\t-i file : set the international days database filename\n");
#ifndef NO_GUI
    fprintf(stdout, "\t-c integer : autoclose the window after 'integer' seconds (default 30)\n");
#endif
    fprintf(stdout, "\t-w : write current settings to options file (~/.giortes/settings)\n");
    fprintf(stdout, "\t-s : ask for a string to search for (Greek capital letters)\n");
    fprintf(stdout, "\t-f : ask a date to search for\n\n");
    fprintf(stdout, 
                   _("\nCopyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>\n"
                   "This program is free software: you can redistribute it and/or modify it\n"
                   "under the terms of the GNU General Public License version 3 as published\n"
                   "by the Free Software Foundation.\n\n"
                   "You should have received a copy of the GNU General Public License along\n"
                   "with this program.  If not, see <http://www.gnu.org/licenses/>.\n"));
    fprintf(stdout, "http://linuxteam.cs.teilar.gr/~forfolias/giortes\n");
}

void version()
{
    fprintf(stdout, "\nGiortes version %s\n", VERSION);
    fprintf(stdout, 
                   _("\nCopyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>\n"
                   "This program is free software: you can redistribute it and/or modify it\n"
                   "under the terms of the GNU General Public License version 3 as published\n"
                   "by the Free Software Foundation.\n\n"
                   "You should have received a copy of the GNU General Public License along\n"
                   "with this program.  If not, see <http://www.gnu.org/licenses/>.\n"));
    fprintf(stdout, "http://linuxteam.cs.teilar.gr/~forfolias/giortes\n\n");
}
