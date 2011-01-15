/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void Initialize(void);

#define BUFFER 200

int  search_flag;
int  quiet;                  /* verbose mode */
char no_database;       /* which database NOT to show, n:none, a:all, p:personal, i:international*/
int  X;                      /* variable to check X days after today */
int  gtk;

struct event {
    int mera;
    int minas;
    char kiniti[4];     /* If the event does NOT depend on easter Sunday, this variable */
                        /* contains '*', otherwise it contains the number on which it depends. */
                        /* eg -2 for Friday's easter */     /* Flawfinder: ignore */
    char onoma[200];        /* Flawfinder: ignore */
    char paragoga[400];     /* Flawfinder: ignore */
};


#endif // INIT_H_INCLUDED
