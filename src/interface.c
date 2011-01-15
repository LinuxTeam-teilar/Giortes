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

#ifdef GTK_GUI

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "dates.h"
#include "init.h"
#include "search.h"
#include "files.h"
#include "options.h"
#include "gettext.h"

void showMainWindowGUI(void){
    gtk_widget_show (main_window);
}

void hideMainWindowGUI(void){
    gtk_widget_hide(main_window);
}

void createMainWindowTopGUI(void){
    char iconPath[BUFFER];
#ifdef _WIN32
    strncpy(iconPath, getenv("PROGRAMFILES"), BUFFER);
    strncat(iconPath, "\\giortes\\giortes64.png", BUFFER-strlen(iconPath));
#else
    strncpy(iconPath, PIXMAPDIR, BUFFER);
    strncat(iconPath, "/giortes64.png", BUFFER-strlen(iconPath));
#endif

    pixbuf = gdk_pixbuf_new_from_file(iconPath, NULL);
    main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (main_window), _("Giortes"));
    gtk_window_set_resizable(GTK_WINDOW (main_window), FALSE);
    gtk_window_set_default_icon(pixbuf);
    gtk_window_set_default_size (GTK_WINDOW (main_window), (gint) 400, (gint) 300);
    gtk_window_set_position (GTK_WINDOW (main_window), GTK_WIN_POS_CENTER);
    g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (main_window), 10);
    vbox = gtk_vbox_new (FALSE, 5);
    gtk_container_add (GTK_CONTAINER (main_window), vbox);
}

void createMainWindowEndGUI(void){
    GtkWidget *button, *button_close;
    GtkWidget *hbox;

    hbox = gtk_hbox_new (FALSE, 5);
    button = gtk_button_new_with_label (_("Preferences"));
    gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_stock(GTK_STOCK_PREFERENCES, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (on_options_BT_clicked), main_window);
    gtk_box_pack_start (GTK_BOX(hbox), button, TRUE, FALSE, 0);
    gtk_widget_show (button);

    button = gtk_button_new_with_label (_("More..."));
    gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_stock(GTK_STOCK_FIND, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (on_more_BT_clicked), NULL);
    gtk_box_pack_start (GTK_BOX(hbox), button, TRUE, FALSE, 0);
    gtk_widget_show (button);

    button = gtk_button_new_with_label (_("About"));
    gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_stock(GTK_STOCK_ABOUT, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (on_about_BT_clicked), NULL);
    gtk_box_pack_start (GTK_BOX(hbox), button, TRUE, FALSE, 0);
    gtk_widget_show (button);

    button_close = gtk_button_new_with_label (_("Quit"));
    gtk_button_set_image(GTK_BUTTON(button_close), gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button_close), "clicked",
		      G_CALLBACK (gtk_main_quit), NULL);
    gtk_box_pack_start (GTK_BOX(hbox), button_close, TRUE, FALSE, 0);
    GTK_WIDGET_SET_FLAGS (button_close, GTK_CAN_FOCUS);
    gtk_window_set_focus(GTK_WINDOW(main_window), button_close);
    gtk_widget_show (button_close);


    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, TRUE, 0);
    gtk_widget_show (vbox);
    gtk_widget_show (hbox);
    gtk_widget_show (main_window);
}

gboolean exitProgramGUI(void){
    if (auto_close_flag == 1) {
        return FALSE;
    }
    else {
        gtk_main_quit();
        return TRUE;
    }
}

void on_about_BT_clicked(GtkWidget *widget)
{
    auto_close_flag = 1;
    static const gchar *author[] = { "George Vasilakos <forfolias@linuxteam.cs.teilar.gr>", NULL, };

    gtk_show_about_dialog (GTK_WINDOW(main_window),
                         "artists", author,
                         "authors", author,
                         "copyright", "Copyright (c) 2010 George Vasilakos\n",
                         "destroy-with-parent", TRUE,
                         "documenters", author,
                         "comments", 
   _("This program displays the name day celebration\n"
     "based on the Orthodox Calendar. It also displays\n"
     "events from a personal and international days\n"
     "file list and can calculate the Orthodox Easter\n"
     "Sunday and the holidays of a year."),
 
                         "license", 
    _("\nCopyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>\n"
    "This program is free software: you can redistribute it and/or modify it\n"
    "under the terms of the GNU General Public License version 3 as published\n"
    "by the Free Software Foundation.\n\n"
    "You should have received a copy of the GNU General Public License along\n"
    "with this program.  If not, see <http://www.gnu.org/licenses/>.\n"),

                         "logo", pixbuf,
                         "program-name", _("Giortes"),
                         "translator-credits", _("Enter translator name here"),
                         "version", VERSION,
                         "website", "http://linuxteam.cs.teilar.gr/~forfolias/giortes",
                         NULL);
}

void closeWindowGUI(GtkWidget *widget, GtkWidget *wind){
    gtk_widget_destroy(wind);
    gtk_widget_show(main_window);
}

void on_more_BT_clicked(GtkWidget *wid){
    auto_close_flag = 1;
    gtk_widget_hide(main_window);

    GtkWidget *radio1, *radio2, *radio3, *hbox1;
    GtkWidget *window2 = gtk_dialog_new_with_buttons (_("More..."), NULL, GTK_DIALOG_NO_SEPARATOR, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_resizable(GTK_WINDOW (window2), FALSE);

    GtkWidget *widg = gtk_label_new (_("Choose an action from the list"));
    hbox1 = gtk_hbox_new (TRUE, 5);
    gtk_box_pack_start (GTK_BOX (hbox1), widg, TRUE, TRUE , 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox1, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox1);

    hbox1 = gtk_hbox_new (TRUE, 5);
    radio1 = gtk_radio_button_new_with_label (NULL, _("Calculate Easter Sunday..."));
    gtk_box_pack_start (GTK_BOX (hbox1), radio1, TRUE, TRUE , 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox1, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox1); 

    hbox1 = gtk_hbox_new (TRUE, 5);
    radio2 = gtk_radio_button_new_with_label (gtk_radio_button_group (GTK_RADIO_BUTTON (radio1)), _("Calculate year's holidays..."));
    gtk_box_pack_start (GTK_BOX (hbox1), radio2, TRUE, TRUE , 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox1, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox1); 

    hbox1 = gtk_hbox_new (TRUE, 5);
    radio3 = gtk_radio_button_new_with_label (gtk_radio_button_group (GTK_RADIO_BUTTON (radio1)), _("Search"));
    gtk_box_pack_start (GTK_BOX (hbox1), radio3, TRUE, TRUE , 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox1, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox1); 

    gtk_dialog_set_default_response (GTK_DIALOG (window2), GTK_RESPONSE_OK);

    gint result = gtk_dialog_run (GTK_DIALOG (window2));
    if (result == GTK_RESPONSE_CANCEL) {
        closeWindowGUI(NULL, window2); 
        return;
    }
    else {
        if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio1)) == TRUE){
            gtk_widget_destroy (window2);
            calculateEaster();
        }
        else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio2)) == TRUE) {
            gtk_widget_destroy (window2);
            calculateFeast(0);
        }
        else {
            gtk_widget_destroy (window2);
            on_search_BT_clicked();
        }
    }
    return;
}

void on_search_BT_clicked(){
    GtkWidget *widg, *vbox1, *hbox1, *button1;
    struct search *ser;

    gtk_widget_hide(main_window);

    ser = g_new0 (struct search, 1);
    ser->win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (ser->win), "Αναζήτηση");
    gtk_window_set_default_size(GTK_WINDOW (ser->win), 300, -1);
    gtk_window_set_position (GTK_WINDOW (ser->win), GTK_WIN_POS_CENTER);

    g_signal_connect (G_OBJECT (ser->win), "destroy", G_CALLBACK (closeWindowGUI), ser->win);

    vbox1 = gtk_vbox_new (FALSE, 10);
    gtk_container_add (GTK_CONTAINER (ser->win), vbox1);

    widg = gtk_label_new ( _("Select search type:"));
    gtk_box_pack_start (GTK_BOX (vbox1), widg, TRUE, TRUE , 5);
    gtk_widget_show(widg);

    ser->radio1 = gtk_radio_button_new_with_label (NULL, _("Search by name..."));
    gtk_widget_show(ser->radio1); 
    ser->radio2 = gtk_radio_button_new_with_label (gtk_radio_button_group (GTK_RADIO_BUTTON (ser->radio1)), _("Search by date..."));
    gtk_widget_show(ser->radio2); 
    gtk_box_pack_start (GTK_BOX (vbox1), ser->radio1, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (vbox1), ser->radio2, TRUE, TRUE, 5);

    /* BUTTONS */
    hbox1 = gtk_hbox_new (TRUE, 5);
    button1 = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (SetSearchTypeGUI), ser);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 0);

    button1 = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (closeWindowGUI), ser->win);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    gtk_widget_show_all(ser->win);
    return;
}

int getYearGUI(){
    GtkWidget *window2, *hbox2, *widg, *spinbutton1;
    window2 = gtk_dialog_new_with_buttons (_("Select year"), NULL, GTK_DIALOG_NO_SEPARATOR,
                                         GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_resizable(GTK_WINDOW (window2), FALSE);
    hbox2 = gtk_hbox_new (FALSE, 5);
    widg = gtk_label_new (_("Please, insert year: "));
    gtk_box_pack_start (GTK_BOX(hbox2), widg, TRUE, TRUE, 5);
    spinbutton1 = gtk_spin_button_new_with_range(1583, 2099, 1);
    gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinbutton1), current_year);
    gtk_box_pack_start (GTK_BOX(hbox2), spinbutton1, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE , 5);
    gtk_dialog_set_default_response (GTK_DIALOG (window2), GTK_RESPONSE_OK);
    gtk_widget_show_all(hbox2);

    gint result = gtk_dialog_run (GTK_DIALOG (window2));
    if (result == GTK_RESPONSE_OK) {
        int temp = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinbutton1));
        gtk_widget_destroy (window2);
        return temp;
    }
    else {
        gtk_widget_destroy (window2);
        return 0;
    }
}

void SetSearchTypeGUI(GtkWidget *but, struct search *srch){
        char temp[BUFFER]="";    /* Flawfinder: ignore */
        createMainWindowTopGUI();
        if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(srch->radio1)) == TRUE){
            gtk_widget_destroy (srch->win);
            SetSearchNameGUI(temp, BUFFER);
            search(temp);
        } else {
            gtk_widget_destroy (srch->win);
            find(0, 0);
        }
        createMainWindowEndGUI();
    return;
}

void SetSearchNameGUI(char *temp, int size){

    auto_close_flag = 1;
    hideMainWindowGUI();

    strncpy(label_str, "", labelBUFFER);
    gtk_label_set_text(GTK_LABEL(label), label_str);

    GtkWidget *window2 = gtk_dialog_new_with_buttons (_("Search"), NULL, GTK_DIALOG_NO_SEPARATOR, GTK_STOCK_FIND, 1, NULL);
    gtk_window_set_resizable(GTK_WINDOW (window2), FALSE);
    gtk_dialog_set_default_response(GTK_DIALOG(window2), 1);
    GtkWidget *hbox = gtk_hbox_new (FALSE, 5);
    GtkWidget *widg = gtk_label_new (_("Insert the name you want to search: "));
    gtk_box_pack_start (GTK_BOX(hbox), widg, FALSE, FALSE, 5);
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_activates_default(GTK_ENTRY(entry), 1);
    gtk_entry_set_max_length(GTK_ENTRY(entry), BUFFER-1);
    gtk_box_pack_start (GTK_BOX(hbox), entry, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox);

    hbox = gtk_hbox_new (FALSE, 5);
    widg = gtk_label_new (_("The name must be written in Greek CAPITAL characters, it can contain the\nwildcard character '*' only at the end and must be at least 3 characters long."));
    gtk_box_pack_start (GTK_BOX(hbox), widg, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox);

    gtk_dialog_run (GTK_DIALOG (window2));
    strncpy(temp, gtk_entry_get_text(GTK_ENTRY(entry)), size);
    temp[size-1] = '\0';
    if (strlen(temp) == 0){
        temp[0]=' ';
        temp[1]='\0';
    }
    closeWindowGUI(NULL, window2);
}

void create_personal(GtkWidget *entry) {
    GtkWidget *dialog;

    strncpy(personal, gtk_entry_get_text(GTK_ENTRY(entry)), BUFFER);

    if (strcmp(personal, "") == 0) {
        strncpy(personal, "personal.txt", BUFFER);
    }
    createPersonalText();
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, _("The file with your personal events <%s> was successfully created.\nYou can edit the file with your preferred text editor to add events."), personal);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void create_i_days(GtkWidget *temp) {
    GtkWidget *dialog;

    if (strcmp(internat, "") == 0) {
        strncpy(internat, "int_days.txt", BUFFER);
    }
    createInternationalDaysText();
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "The file with international days <%s> created successful.", internat);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void checkPersonalErrorGUI(){
    auto_close_flag=1;
    GtkWidget *window1;
    window1 = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, _("Could not locate the personal events database file <%s>. Would you like to create the file now?"), personal);
    gint result = gtk_dialog_run (GTK_DIALOG (window1));
    gtk_widget_destroy (window1);
    if (result == GTK_RESPONSE_YES) {
        SettingPersonal();
    }
}

void checkInternationalDaysErrorGUI(){
    auto_close_flag=1;
    GtkWidget *window1;
    window1 = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, _("Could not locate the international days database <%s>. Would you like to create the file now?"), internat);
    gint result = gtk_dialog_run (GTK_DIALOG (window1));
    gtk_widget_destroy (window1);
        if (result == GTK_RESPONSE_YES) {
        SettingInternat();
    }
}

void checkFileErrorGUI(char *filename){
    auto_close_flag=1;
    GtkWidget *window1;
    window1 = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, _("Could not locate file <%s>.\n"), filename);
    gtk_dialog_run (GTK_DIALOG (window1));
    gtk_widget_destroy (window1);
}

void SettingPersonal(){
    GtkWidget *window2, *widg, *entry, *button1, *hbox2;

    gtk_widget_hide(main_window);

    window2 = gtk_dialog_new_with_buttons (_("Create file"), NULL, GTK_DIALOG_NO_SEPARATOR,
                                         _("Create"), 2, GTK_STOCK_CANCEL, 3, NULL);

    widg = gtk_label_new (_("Insert file path or leave the field blank to\ncreate the file at the default path.\nWARNING: If the file already exists it will be overwritten!"));
    hbox2 = gtk_hbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (hbox2), widg, TRUE, TRUE , 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox2);

    hbox2 = gtk_hbox_new (FALSE, 5);
    entry = gtk_entry_new_with_max_length(199);
    gtk_entry_set_text(GTK_ENTRY(entry), personal);
    gtk_box_pack_start (GTK_BOX(hbox2), entry, TRUE, TRUE, 5);
    button1 = gtk_button_new_with_label("...");
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (file_choose), entry);
    gtk_box_pack_start (GTK_BOX(hbox2), button1, FALSE, FALSE, 5);
    gtk_widget_show_all(hbox2);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE, 5);
    
    gint result = gtk_dialog_run (GTK_DIALOG (window2));
    if (result == 2) create_personal(entry);
    gtk_widget_destroy (window2);
}

void SettingInternat(){
    GtkWidget *window2, *widg, *entry, *button1, *hbox2;

    gtk_widget_hide(main_window);

    window2 = gtk_dialog_new_with_buttons (_("Create file"), NULL, GTK_DIALOG_NO_SEPARATOR,
                                         _("Create"), 2, GTK_STOCK_CANCEL, 3, NULL);
    widg = gtk_label_new (_("Insert file path or leave the field blank to\ncreate the file at the default path.\nWARNING: If the file already exists it will be overwritten!"));
    hbox2 = gtk_hbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (hbox2), widg, TRUE, TRUE , 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox2);

    hbox2 = gtk_hbox_new (FALSE, 5);
    entry = gtk_entry_new_with_max_length(199);
    gtk_entry_set_text(GTK_ENTRY(entry), internat);
    gtk_box_pack_start (GTK_BOX(hbox2), entry, TRUE, TRUE, 5);
    button1 = gtk_button_new_with_label("...");
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (file_choose), entry);
    gtk_box_pack_start (GTK_BOX(hbox2), button1, FALSE, FALSE, 5);
    gtk_widget_show_all(hbox2);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE, 5);
    
    gint result = gtk_dialog_run (GTK_DIALOG (window2));
    if (result == 2) create_i_days(entry);
    gtk_widget_destroy (window2);
}

void file_choose(GtkWidget *widget, GtkWidget *entry){
    GtkWidget *dialog;
    char *temp;
    dialog = gtk_file_chooser_dialog_new(_("Select file"), NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                         GTK_STOCK_CANCEL, 0, GTK_STOCK_OK, 1, NULL);
    gint result = gtk_dialog_run(GTK_DIALOG (dialog));
    if (result == 1){
        temp = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        gtk_entry_set_text(GTK_ENTRY (entry), temp);
    }
    gtk_widget_destroy (dialog);
}

void on_options_BT_clicked (GtkWidget *widget, GtkWidget *main_win)
{
    FILE *opt_file;
    struct options *opt;

    GtkWidget *window1;
    GtkWidget *vbox1;
    GtkWidget *label1;
    GtkWidget *button1;
    GtkWidget *hbox1;
    GtkWidget *hbox2;

    gtk_widget_hide(main_window);

    auto_close_flag = 1;
    opt = g_new0 (struct options, 1);
    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window1), _("Options"));
    gtk_window_set_default_size(GTK_WINDOW (window1), 550, 450);
    gtk_window_set_resizable(GTK_WINDOW (window1), FALSE);
    gtk_window_set_position (GTK_WINDOW (window1), GTK_WIN_POS_CENTER);

    g_signal_connect (G_OBJECT (window1), "destroy", G_CALLBACK (closeWindowGUI), window1);

    vbox1 = gtk_vbox_new (FALSE, 10);
    gtk_container_add (GTK_CONTAINER (window1), vbox1);

    label1 = gtk_label_new(_("To activate the modifications you need to restart the program."));
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX(vbox1), label1, FALSE, TRUE, 15);

    /* NAMEDAY DATABASE */
    hbox1 = gtk_hbox_new (FALSE, 5);
    label1 = gtk_label_new(_("Nameday database file:"));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, FALSE, 5);
    hbox2 = gtk_hbox_new (FALSE, 5);
    opt->entry1 = gtk_entry_new_with_max_length(199);
    gtk_entry_set_text(GTK_ENTRY(opt->entry1), database);
    gtk_box_pack_start (GTK_BOX(hbox2), opt->entry1, TRUE, TRUE, 0);
    button1 = gtk_button_new_with_label("...");
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (file_choose), opt->entry1);
    gtk_box_pack_start (GTK_BOX(hbox2), button1, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    /* PERSONAL DATABASE */
    hbox1 = gtk_hbox_new (FALSE, 5);
    button1 = gtk_button_new_with_label(_("Create"));
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (SettingPersonal), NULL);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 5);
    label1 = gtk_label_new(_("Personal events file:"));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, FALSE, 0);
    hbox2 = gtk_hbox_new (FALSE, 5);
    opt->entry2 = gtk_entry_new_with_max_length(199);
    gtk_entry_set_text(GTK_ENTRY(opt->entry2), personal);
    gtk_box_pack_start (GTK_BOX(hbox2), opt->entry2, TRUE, TRUE, 0);
    button1 = gtk_button_new_with_label("...");
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (file_choose), opt->entry2);
    gtk_box_pack_start (GTK_BOX(hbox2), button1, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    /* INTERNATIONAL DAYS DATABASE */
    hbox1 = gtk_hbox_new (FALSE, 5);
    button1 = gtk_button_new_with_label(_("Create"));
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (SettingInternat), NULL);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 5);
    label1 = gtk_label_new( _("International days file:"));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, FALSE, 0);
    hbox2 = gtk_hbox_new (FALSE, 5);
    opt->entry3 = gtk_entry_new_with_max_length(199);
    gtk_entry_set_text(GTK_ENTRY(opt->entry3), internat);
    gtk_box_pack_start (GTK_BOX(hbox2), opt->entry3, TRUE, TRUE, 0);
    button1 = gtk_button_new_with_label("...");
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (file_choose), opt->entry3);
    gtk_box_pack_start (GTK_BOX(hbox2), button1, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);
 
    /* CHECKBUTTONS DATABASE */
    opt->checkbutton1 = gtk_check_button_new_with_label (_("Display personal events"));
    if (no_database == 'a' || no_database == 'p') {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton1), FALSE);
    }
    else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton1), TRUE);
    }
    hbox1 = gtk_hbox_new (TRUE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), opt->checkbutton1, TRUE, TRUE, 5); 
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);
    opt->checkbutton2 = gtk_check_button_new_with_label (_("Display international days"));
    if (no_database == 'a' || no_database == 'i') {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton2), FALSE);
    }
    else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton2), TRUE);
    }
    hbox1 = gtk_hbox_new (TRUE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), opt->checkbutton2, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    /* SHOW X NEXT DAYS */
    hbox1 = gtk_hbox_new (FALSE, 5);
    label1 = gtk_label_new(_("Display events for the next"));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, TRUE, 5);
    opt->spinbutton1 = gtk_spin_button_new_with_range(1, 30, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(opt->spinbutton1), X);
    gtk_box_pack_start (GTK_BOX(hbox1), opt->spinbutton1, FALSE, TRUE, 0);
    label1 = gtk_label_new(_("days. Use sparingly."));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    /* AUTOCLOSE SECONDS */
    hbox1 = gtk_hbox_new (FALSE, 5);
    label1 = gtk_label_new(_("Autoexit after"));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, TRUE, 5);
    opt->spinbutton2 = gtk_spin_button_new_with_range(0, 120, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(opt->spinbutton2), auto_close);
    gtk_box_pack_start (GTK_BOX(hbox1), opt->spinbutton2, FALSE, TRUE, 0);
    label1 = gtk_label_new(_("seconds. 0 means no autoexit."));
    gtk_box_pack_start (GTK_BOX(hbox1), label1, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    /* LABEL OPTIONS */
    opt_file = fopen(settings, "r");    /* Flawfinder: ignore */

    if (!opt_file) {
        opt->label = gtk_label_new(_("Could not locate settings file. Click save to create the file."));
    }
    else {
        fclose(opt_file); 
        opt->label = gtk_label_new(_("Displaying current settings. Press open to view the\nsettings on the settings file."));
    }
    gtk_label_set_justify(GTK_LABEL(opt->label), GTK_JUSTIFY_CENTER);
    hbox1 = gtk_hbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), opt->label, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 5);

    /* BUTTONS */
    hbox1 = gtk_hbox_new (TRUE, 5);
    button1 = gtk_button_new_with_label (_("Save"));
    gtk_button_set_image(GTK_BUTTON(button1), gtk_image_new_from_stock(GTK_STOCK_SAVE, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (SetSettings), opt);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 0);
    button1 = gtk_button_new_with_label (_("Open"));
    gtk_button_set_image(GTK_BUTTON(button1), gtk_image_new_from_stock(GTK_STOCK_OPEN, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (ReadSettingToDrawOptions), opt);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 0);
    button1 = gtk_button_new_with_label (_("Close"));
    gtk_button_set_image(GTK_BUTTON(button1), gtk_image_new_from_stock(GTK_STOCK_CLOSE, GTK_ICON_SIZE_BUTTON));
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (closeWindowGUI), window1);
    gtk_box_pack_start (GTK_BOX(hbox1), button1, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, FALSE, FALSE, 15);

    gtk_widget_show_all(window1);
}

void SetSettings (GtkWidget *widget, struct options *opt) {
    
    strncpy(database, gtk_entry_get_text(GTK_ENTRY(opt->entry1)), BUFFER);
    strncpy(personal, gtk_entry_get_text(GTK_ENTRY(opt->entry2)), BUFFER);
    strncpy(internat, gtk_entry_get_text(GTK_ENTRY(opt->entry3)), BUFFER);
    X =  gtk_spin_button_get_value(GTK_SPIN_BUTTON (opt->spinbutton1));
    auto_close =  gtk_spin_button_get_value(GTK_SPIN_BUTTON (opt->spinbutton2));
    if ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton1)) == FALSE) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton2))== FALSE)){
        no_database = 'a';
    }
    else if ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton1)) == TRUE) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton2)) == FALSE)){
        no_database = 'i';
    }
    else if ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton1)) == FALSE) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton2)) == TRUE)){
        no_database = 'p';
    }
    else if ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton1)) == TRUE) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (opt->checkbutton2)) == TRUE)){
        no_database = 'n';
    }

    writeOptions();
    char text[BUFFER];    /* Flawfinder: ignore */
    strncpy(text, _("Settings were successfully saved at file: "), BUFFER);
    strncat(text, settings, BUFFER-strlen(text));
    gtk_label_set_text(GTK_LABEL(opt->label), text);
}

void ReadSettingToDrawOptions(GtkWidget *widget, struct options *opt) {
    char text[BUFFER];    /* Flawfinder: ignore */
    FILE *set;
    set = fopen (settings, "r");    /* Flawfinder: ignore */
    if (!set){
        strncpy(text, _("Could not locate settings file. Click save to create the file."), BUFFER);
        gtk_label_set_text(GTK_LABEL(opt->label), text);
        return;
    }
    else {
        fclose(set);
        readOptions("");
        strncpy(text, _("Settings were successfully read from file: "), BUFFER);
        strncat(text, settings, BUFFER-strlen(text));
    }
    gtk_entry_set_text(GTK_ENTRY (opt->entry1), database);
    gtk_entry_set_text(GTK_ENTRY (opt->entry2), personal);
    gtk_entry_set_text(GTK_ENTRY (opt->entry3), internat);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON (opt->spinbutton1), X);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON (opt->spinbutton2), auto_close);
    if (no_database == 'a' || no_database == 'p') {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton1), FALSE);
    }
    else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton1), TRUE);
    }
    if (no_database == 'a' || no_database == 'i') {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton2), FALSE);
    }
    else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opt->checkbutton2), TRUE);
    }
    gtk_label_set_text(GTK_LABEL(opt->label), text);
}

void printEasterGUI(int i, int pasxa_day, char *temp){
    GtkWidget *window1 = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
                   GTK_BUTTONS_OK, _("Orthodox Easter Sunday of year %d is on %d of %s"), i, pasxa_day, temp);
    gtk_window_set_title(GTK_WINDOW(window1), _("Calculate Easter"));
    gtk_dialog_run (GTK_DIALOG (window1));
    gtk_widget_destroy (window1);
    gtk_widget_show (main_window);
}

void printFeastDaysGUI(int i){
    GtkWidget *hbox;
    char temp[50]="";    /* Flawfinder: ignore */
    snprintf(temp, sizeof(temp), _("Holidays of year %d:"), i);
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new(temp);
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("\nΣτις 1/1:\n\tΠΡΩΤΟΧΡΟΝΙΑ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 6/1:\n\tΘΕΟΦΑΝΕΙΑ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    search("ΚΑΘΑΡΑ ΔΕΥΤΕΡΑ");
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 25/3:\n\tΕΛΛΗΝΙΚΗ ΕΠΑΝΑΣΤΑΣΗ ΤΟΥ 1821\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    search("ΜΕΓΑΛΗ ΔΕΥΤΕΡΑ");
    search("ΜΕΓΑΛΗ ΠΑΡΑΣΚΕΥΗ");
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 1/5:\n\tΠΡΩΤΟΜΑΓΙΑ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    search("ΤΟΥ ΑΓΙΟΥ ΠΝ*");
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 15/8:\n\tΚΟΙΜΗΣΕΩΣ ΤΗΣ ΘΕΤΟΚΟΥ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 28/10:\n\tΕΠΕΤΕΙΟΣ ΤΟΥ ΟΧΙ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 25/12:\n\tΓΕΝΝΗΣΗΣ ΤΟΥ ΧΡΙΣΤΟΥ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
    hbox = gtk_hbox_new (FALSE, 5);
    label = gtk_label_new("Στις 26/12:\n\tΔΕΥΤΕΡΗ ΜΕΡΑ ΤΩΝ ΧΡΙΣΤΟΥΓΕΝΝΩΝ\n");
    gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (label);
    gtk_widget_show (hbox);
}

void insertResultIntoLabelGUI(void){
    GtkWidget *hbox;
    if (strcmp(label_str, "") != 0)
    {
        hbox = gtk_hbox_new (FALSE, 5);
        label = gtk_label_new(label_str);
        gtk_box_pack_start (GTK_BOX(hbox), label, FALSE, TRUE, 5);
        gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
        gtk_widget_show (label);
        gtk_widget_show (hbox);
    }
}

void getDateForFindGUI(int *mera, int *minas){

    GtkWidget *window2, *widg, *hbox2, *spinbutton1, *spinbutton2;

    strncpy(label_str, "", labelBUFFER);

    window2 = gtk_dialog_new_with_buttons (_("Search"), NULL, GTK_DIALOG_NO_SEPARATOR,
                                                   GTK_STOCK_FIND, 1, NULL);
    gtk_window_set_resizable(GTK_WINDOW (window2), FALSE);
    hbox2 = gtk_hbox_new (FALSE, 5);

    widg = gtk_label_new (_("Select the month and day you want to search: "));
    gtk_box_pack_start (GTK_BOX(hbox2), widg, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox2);

    hbox2 = gtk_hbox_new (FALSE, 5);
    widg = gtk_label_new (_("Month:"));
    gtk_box_pack_start (GTK_BOX(hbox2), widg, FALSE, FALSE, 5);
    spinbutton1 = gtk_spin_button_new_with_range(1, 12, 1);
    gtk_box_pack_start (GTK_BOX(hbox2), spinbutton1, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox2);

    hbox2 = gtk_hbox_new (FALSE, 5);
    widg = gtk_label_new (_("Day:"));
    gtk_box_pack_start (GTK_BOX(hbox2), widg, FALSE, FALSE, 5);
    spinbutton2 = gtk_spin_button_new_with_range(1, 31, 1);
    gtk_box_pack_start (GTK_BOX(hbox2), spinbutton2, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window2)->vbox), hbox2, TRUE, TRUE , 5);
    gtk_widget_show_all(hbox2);

    gtk_dialog_run (GTK_DIALOG (window2));
    *mera = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinbutton2));
    *minas = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinbutton1));

    closeWindowGUI(NULL, window2);
}

void invalidDateMsgGUI(void){
    GtkWidget *window2 = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
                      GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, _("Invalid date, please try again.") );
    gtk_dialog_run (GTK_DIALOG (window2));
    gtk_widget_destroy (window2);
}

void fillLabelGUI(struct event giorti, char *current){
    if (strcmp(current, past)!=0)
    {
        strncat(label_str, current, labelBUFFER-strlen(label_str));
        strncat(label_str, "\n", labelBUFFER-strlen(label_str));
    }
    strncat(label_str, "\t", labelBUFFER-strlen(label_str));
    strncat(label_str, giorti.onoma, labelBUFFER-strlen(label_str));
    strncat(label_str, "  ", labelBUFFER-strlen(label_str));
    strncat(label_str, giorti.paragoga, labelBUFFER-strlen(label_str));
    strncat(label_str, "\n", labelBUFFER-strlen(label_str));
}

#endif
