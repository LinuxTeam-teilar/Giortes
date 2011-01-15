/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef GTK_GUI
#include <gtk/gtk.h>
#include "init.h"

int auto_close_flag;
int auto_close;

#define labelBUFFER 2000

char label_str[labelBUFFER];     /* Flawfinder: ignore */
GtkWidget *main_window;
GtkWidget *vbox;
GtkWidget *label;
GdkPixbuf *pixbuf;

struct options {
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *spinbutton1;
    GtkWidget *spinbutton2;
    GtkWidget *checkbutton1;
    GtkWidget *checkbutton2;
    GtkWidget *label;
};

struct search {
    GtkWidget *win;
    GtkWidget *radio1;
    GtkWidget *radio2;
};

void createMainWindowEndGUI(void);
void createMainWindowTopGUI(void);
void closeWindowGUI(GtkWidget *, GtkWidget *);
gboolean exitProgramGUI(void);

void on_about_BT_clicked(GtkWidget *);
void on_options_BT_clicked (GtkWidget *, GtkWidget *);
void on_more_BT_clicked(GtkWidget *);
void on_search_BT_clicked(void);

void SetSearchTypeGUI(GtkWidget *, struct search *);
void SetSearchNameGUI(char *, int );

int getYearGUI(void);

void createPersonalGUI(GtkWidget *);
void createInternationalDaysGUI(GtkWidget *);

void SettingPersonal(void);
void file_choose(GtkWidget *, GtkWidget *);
void SettingInternat(void);
void SetSettings (GtkWidget *, struct options *);
void ReadSettingToDrawOptions(GtkWidget *, struct options *);

void checkFileErrorGUI(char *);
void checkPersonalErrorGUI(void);
void checkInternationalDaysErrorGUI(void);

void printFeastDaysGUI(int);
void printEasterGUI(int, int, char *);

void showMainWindowGUI(void);
void hideMainWindowGUI(void);

void insertResultIntoLabelGUI(void);
void getDateForFindGUI(int *, int *);
void invalidDateMsgGUI(void);

void fillLabelGUI(struct event, char *);

#endif

#endif // INTERFACE_H_INCLUDED
