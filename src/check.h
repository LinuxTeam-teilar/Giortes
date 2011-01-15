/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

int  checkNumber(char *, int);
void checkKiniti(char *, int *, int *, char *);
int  checkDate(int, int, int);
void checkPersonal(void);
void checkInternationalDays(void);
int  checkFile(char *);
void checkAllDays(void);

#endif // CHECK_H_INCLUDED
