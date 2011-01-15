/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

char database[200];         /* default filename */              /* Flawfinder: ignore */
char personal[200];                                             /* Flawfinder: ignore */
char internat[200];                                             /* Flawfinder: ignore */
char settings[200];         /* path to the settings file */     /* Flawfinder: ignore */

void createPersonalText(void);
void createInternationalDaysText(void);
void readFile(char *, int, int);

#endif // FILES_H_INCLUDED
