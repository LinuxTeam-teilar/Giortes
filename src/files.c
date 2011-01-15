/**
 Copyright (C) 2010 George Vasilakos <forfolias@linuxteam.cs.teilar.gr>

 This program is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 3 as published
 by the Free Software Foundation.

 You should have received a copy of the GNU General Public License along
 with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <string.h>
#include "files.h"
#include "init.h"
#include "print.h"

void createPersonalText()
{
    FILE *file;
    file = fopen(personal, "w");    /* Flawfinder: ignore */
    fprintf(file, "#Σε αυτό το αρχείο μπορείτε να βάλετε τα προσωπικά σας γεγονότα\n");
    fprintf(file, "#Χρησιμοποιήστε τη δομή όπως φαινεται στο παρακάτω παράδειγμα :\n");
    fprintf(file, "#05 01 Γεγονός προς υπενθύμιση\n");
    fprintf(file, "#Το παραπάνω θα παρουσιάσει \"Γεγονός προς υπενθύμιση\" στις 5 Ιανουαρίου.\n");
    fprintf(file, "#Οι γραμμές που ξεκινάν με \"#\" παραλείπονται\n");
    fclose(file);
}


void createInternationalDaysText()
{
    FILE *file;
    file = fopen(internat, "w");    /* Flawfinder: ignore */
    fprintf(file, "#Σε αυτό το αρχείο υπάρχουν οι παγκόσμιες εορτές\n");
    fprintf(file, "#Έχει την ίδια δομή με το αρχείο personal.dat για να μπορείτε\n");
    fprintf(file, "#να προσθέσετε εύκολα μόνοι σας νέες παγκόσμιες εορτές.\n");
    fprintf(file, "#Οι γραμμές που ξεκινάν με \"#\" παραλλείπονται\n");
    fprintf(file, "\n");
    fprintf(file, "28 01 ΗΜΕΡΑ ΤΩΝ ΛΕΠΡΩΝ\n");
    fprintf(file, "02 02 ΗΜΕΡΑ ΤΩΝ ΥΓΡΟΤΟΠΩΝ\n");
    fprintf(file, "14 02 ΗΜΕΡΑ ΤΩΝ ΕΡΩΤΕΥΜΕΝΩΝ ΚΑΘΟΛΙΚΩΝ ΧΡΙΣΤΙΑΝΩΝ\n");
    fprintf(file, "21 02 ΗΜΕΡΑ ΤΗΣ ΜΗΤΡΙΚΗΣ ΓΛΩΣΣΑΣ\n");
    fprintf(file, "21 02 ΗΜΕΡΑ ΤΟΥ ΞΕΝΑΓΟΥ\n");
    fprintf(file, "08 03 ΗΜΕΡΑ ΤΗΣ ΓΥΝΑΙΚΑΣ\n");
    fprintf(file, "15 03 ΗΜΕΡΑ ΤΟΥ ΚΑΤΑΝΑΛΩΤΗ\n");
    fprintf(file, "21 03 ΗΜΕΡΑ ΤΗΣ ΠΟΙΗΣΗΣ\n");
    fprintf(file, "21 03 ΗΜΕΡΑ ΔΑΣΟΠΟΝΙΑΣ\n");
    fprintf(file, "21 03 ΗΜΕΡΑ ΚΑΤΑ ΤΟΥ ΡΑΤΣΙΣΜΟΥ\n");
    fprintf(file, "22 03 ΗΜΕΡΑ ΥΠΝΟΥ\n");
    fprintf(file, "23 03 ΗΜΕΡΑ ΤΗΣ ΜΕΤΕΩΡΟΛΟΓΙΑΣ\n");
    fprintf(file, "24 03 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΦΥΜΑΤΙΩΣΗΣ\n");
    fprintf(file, "27 03 ΗΜΕΡΑ ΤΟΥ ΘΕΑΤΡΟΥ\n");
    fprintf(file, "30 03 ΗΜΕΡΑ ΑΝΤΙΣΥΛΛΗΨΗΣ\n");
    fprintf(file, "02 04 ΗΜΕΡΑ ΠΑΙΔΙΚΟΥ ΒΙΒΛΙΟΥ\n");
    fprintf(file, "07 04 ΗΜΕΡΑ ΤΗΣ ΥΓΕΙΑΣ\n");
    fprintf(file, "22 04 ΗΜΕΡΑ ΤΗΣ ΓΗΣ\n");
    fprintf(file, "23 04 ΗΜΕΡΑ ΤΟΥ ΒΙΒΛΙΟΥ ΚΑΙ ΤΩΝ ΠΝΕΥΜΑΤΙΚΩΝ ΔΙΚΑΙΩΜΑΤΩΝ\n");
    fprintf(file, "24 04 ΗΜΕΡΑ ΜΝΗΜΗΣ ΤΗΣ ΓΕΝΟΚΤΟΝΙΑΣ ΤΩΝ ΑΡΜΕΝΙΩΝ ΑΠΟ ΤΟΥΣ ΤΟΥΡΚΟΥΣ\n");
    fprintf(file, "24 04 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΦΥΜΑΤΙΩΣΗΣ\n");
    fprintf(file, "27 04 ΗΜΕΡΑ ΣΧΕΔΙΟΥ (DESIGN)\n");
    fprintf(file, "28 04 ΗΜΕΡΑ ΓΙΑ ΤΗΝ ΥΓΕΙΑ ΚΑΙ ΤΗΝ ΑΣΦΑΛΕΙΑ ΣΤΗΝ ΕΡΓΑΣΙΑ\n");
    fprintf(file, "29 04 ΗΜΕΡΑ ΤΟΥ ΧΟΡΟΥ\n");
    fprintf(file, "01 05 ΗΜΕΡΑ ΓΕΛΙΟΥ\n");
    fprintf(file, "03 05 ΗΜΕΡΑ ΤΗΣ ΕΛΕΥΘΕΡΙΑΣ ΤΟΥ ΤΥΠΟΥ\n");
    fprintf(file, "03 05 ΗΜΕΡΑ ΚΑΤΑ ΤΟΥ ΑΣΘΜΑΤΟΣ\n");
    fprintf(file, "06 05 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΔΙΑΙΤΑΣ\n");
    fprintf(file, "09 05 ΗΜΕΡΑ ΤΗΣ ΕΥΡΩΠΗΣ\n");
    fprintf(file, "13 05 ΗΜΕΡΑ ΤΗΣ ΜΗΤΕΡΑΣ (* 2η Κυριακή Μαίου) \n");
    fprintf(file, "15 05 ΗΜΕΡΑ ΤΗΣ ΟΙΚΟΓΕΝΕΙΑΣ\n");
    fprintf(file, "17 05 ΗΜΕΡΑ ΤΩΝ ΤΗΛΕΠΙΚΟΙΝΩΝΙΩΝ\n");
    fprintf(file, "18 05 ΗΜΕΡΑ ΤΩΝ ΜΟΥΣΕΙΩΝ\n");
    fprintf(file, "19 05 ΗΜΕΡΑ ΜΝΗΜΗΣ ΤΗΣ ΓΕΝΟΚΤΟΝΙΑΣ ΤΟΥ ΠΟΝΤΙΑΚΟΥ ΕΛΛΗΝΙΣΜΟΥ ΑΠΟ ΤΟΥΣ ΤΟΥΡΚΟΥΣ\n");
    fprintf(file, "21 05 ΗΜΕΡΑ ΤΗΣ ΠΟΛΙΤΙΣΤΙΚΗΣ ΑΝΑΠΤΥΞΗΣ\n");
    fprintf(file, "31 05 ΗΜΕΡΑ ΚΑΤΑ ΤΟΥ ΚΑΠΝΙΣΜΑΤΟΣ\n");
    fprintf(file, "04 06 ΗΜΕΡΑ ΤΩΝ ΔΙΚΑΙΩΜΑΤΩΝ ΤΟΥ ΠΑΙΔΙΟΥ\n");
    fprintf(file, "05 06 ΗΜΕΡΑ ΠΡΟΣΤΑΣΙΑΣ ΤΟΥ ΠΕΡΙΒΑΛΛΟΝΤΟΣ\n");
    fprintf(file, "08 06 ΗΜΕΡΑ ΤΩΝ ΩΚΕΑΝΩΝ\n");
    fprintf(file, "12 06 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΕΡΓΑΣΙΑΣ ΠΑΙΔΙΩΝ\n");
    fprintf(file, "14 06 ΗΜΕΡΑ TOY ΕΘΕΛOΝΤΗ ΑΙΜOΔΟΤΗ\n");
    fprintf(file, "17 06 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΕΡΗΜΟΠΟΙΗΣΗΣ ΚΑΙ ΤΗΣ ΞΗΡΑΣΙΑΣ\n");
    fprintf(file, "17 06 ΗΜΕΡΑ ΤΟΥ ΠΑΤΕΡΑ (* 3η Κυριακή Ιουνίου)\n");
    fprintf(file, "20 06 ΗΜΕΡΑ ΤΩΝ ΠΡΟΣΦΥΓΩΝ\n");
    fprintf(file, "21 06 ΗΜΕΡΑ ΤΗΣ ΜΟΥΣΙΚΗΣ\n");
    fprintf(file, "26 06 ΗΜΕΡΑ ΚΑΤΑ ΤΩΝ ΝΑΡΚΩΤΙΚΩΝ\n");
    fprintf(file, "26 06 ΗΜΕΡΑ ΥΠΕΡ ΤΩΝ ΘΥΜΑΤΩΝ ΒΑΣΑΝΙΣΜΟΥ\n");
    fprintf(file, "02 07 ΗΜΕΡΑ ΤΩΝ ΣΥΝΕΤΑΙΡΙΣΜΩΝ\n");
    fprintf(file, "03 07 ΗΜΕΡΑ ΤΩΝ ΕΡΩΤΕΥΜΕΝΩΝ ΟΡΘΟΔΟΞΩΝ ΧΡΙΣΤΙΑΝΩΝ\n");
    fprintf(file, "08 07 ΗΜΕΡΑ ΑΛΛΕΡΓΙΑΣ\n");
    fprintf(file, "11 07 ΗΜΕΡΑ ΤΩΝ ΠΛΗΘΥΣΜΩΝ\n");
    fprintf(file, "09 08 ΗΜΕΡΑ ΤΩΝ ΑΥΤΟΧΘΟΝΩΝ ΛΑΩΝ ΤΟΥ ΚΟΣΜΟΥ\n");
    fprintf(file, "12 08 ΗΜΕΡΑ ΤΗΣ ΝΕΟΤΗΤΑΣ\n");
    fprintf(file, "13 08 ΗΜΕΡΑ ΑΡΙΣΤΕΡΟΧΕΙΡΩΝ\n");
    fprintf(file, "23 08 ΗΜEΡΑ ΘYΜΗΣΗΣ ΤΟΥ ΕΜΠΟΡIΟΥ ΣΚΛAΒΩΝ ΚΑI ΤΗΣ ΑΠΑΓOΡΕΥΣHΣ ΤΟΥ\n");
    fprintf(file, "08 09 ΗΜΕΡΑ ΕΞΑΛΕΙΨΗΣ ΤΟΥ ΑΝΑΛΦΑΒΗΤΙΣΜΟΥ\n");
    fprintf(file, "16 09 ΗΜΕΡΑ ΠΡΟΣΤΑΣΙΑΣ ΤΗΣ ΖΩΝΗΣ ΤΟΥ ΟΖΟΝΤΟΣ\n");
    fprintf(file, "20 09 ΗΜΕΡΑ ΧΩΡΙΣ ΑΥΤΟΚΙΝΗΤΟ\n");
    fprintf(file, "21 09 ΗΜΕΡΑ ΤΗΣ ΕΙΡΗΝΗΣ\n");
    fprintf(file, "26 09 ΗΜΕΡΑ ΤΗΣ ΝΑΥΤΙΛΙΑΣ\n");
    fprintf(file, "27 09 ΗΜΕΡΑ ΤΟΥ ΤΟΥΡΙΣΜΟΥ\n");
    fprintf(file, "01 10 ΗΜΕΡΑ ΤΗΣ ΜΟΥΣΙΚΗΣ\n");
    fprintf(file, "01 10 ΗΜΕΡΑ ΤΩΝ ΓΗΡΑΤΕΙΩΝ\n");
    fprintf(file, "03 10 ΗΜΕΡΑ ΚΑΤΟΙΚΙΑΣ\n");
    fprintf(file, "01 10 ΗΜΕΡΑ ΤΩΝ ΓΗΡΑΤΕΙΩΝ\n");
    fprintf(file, "04 10 ΗΜΕΡΑ ΤΩΝ ΖΩΩΝ\n");
    fprintf(file, "05 10 ΗΜΕΡΑ ΤΩΝ ΔΑΣΚΑΛΩΝ\n");
    fprintf(file, "09 10 ΗΜΕΡΑ ΤΩΝ ΤΑΧΥΔΡΟΜΕΙΩΝ\n");
    fprintf(file, "10 10 ΗΜΕΡΑ ΨΥΧΙΚΗΣ ΥΓΕΙΑΣ\n");
    fprintf(file, "11 10 ΗΜΕΡΑ ΤΗΣ ΜΕΙΩΣΗΣ ΖΗΜΙΩΝ ΑΠΟ ΤΙΣ ΦΥΣΙΚΕΣ ΚΑΤΑΣΤΡΟΦΕΣ\n");
    fprintf(file, "13 10 ΗΜΕΡΑ ΟΡΑΣΗΣ (ΚΑΤΑ ΤΗΣ ΤΥΦΛΟΤΗΤΑΣ)\n");
    fprintf(file, "16 10 ΗΜΕΡΑ ΤΗΣ ΔΙΑΤΡΟΦΗΣ\n");
    fprintf(file, "17 10 ΗΜΕΡΑ ΥΠΕΡ ΤΗΣ ΕΞΑΛΕΙΨΗΣ ΤΗΣ ΦΤΩΧΙΑΣ\n");
    fprintf(file, "20 10 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΟΣΤΕΟΠΟΡΩΣΗΣ\n");
    fprintf(file, "24 10 ΗΜΕΡΑ ΤΟΥ Ο.Η.Ε.\n");
    fprintf(file, "31 10 ΗΜΕΡΑ ΤΗΣ ΑΠΟΤΑΜΙΕΥΣΗΣ\n");
    fprintf(file, "01 11 ΗΜΕΡΑ ΧΟΡΤΟΦΑΓΙΑΣ\n");
    fprintf(file, "14 11 ΗΜΕΡΑ ΤΟΥ ΔΙΑΒΗΤΗ\n");
    fprintf(file, "16 11 ΗΜΕΡΑ ΥΠΕΡ ΤΗΣ ΑΝΟΧΗΣ\n");
    fprintf(file, "21 11 ΗΜΕΡΑ ΤΗΣ ΤΗΛΕΟΡΑΣΗΣ\n");
    fprintf(file, "21 11 ΗΜΕΡΑ ΧΑΙΡΕΤΙΣΜΟΥ\n");
    fprintf(file, "21 11 ΗΜΕΡΑ ΦΙΛΟΣΟΦΙΑΣ\n");
    fprintf(file, "25 11 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΒΙΑΣ ΕΝΑΝΤΙΟΝ ΤΩΝ ΓΥΝΑΙΚΩΝ\n");
    fprintf(file, "29 11 ΗΜΕΡΑ ΥΠΕΡ ΤΩΝ ΠΑΛΑΙΣΤΙΝΙΩΝ\n");
    fprintf(file, "01 12 ΗΜΕΡΑ ΚΑΤΑ ΤΟΥ AIDS\n");
    fprintf(file, "02 12 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΣΚΛΑΒΙΑΣ\n");
    fprintf(file, "03 12 ΗΜΕΡΑ ΤΩΝ ΑΤΟΜΩΝ ΜΕ ΑΝΑΠΗΡΙΑ\n");
    fprintf(file, "04 12 ΗΜΕΡΑ ΚΑΤΑ ΤΩΝ ΝΑΡΚΩΝ\n");
    fprintf(file, "07 12 ΗΜΕΡΑ ΤΗΣ ΠΟΛΙΤΙΚΗΣ ΑΕΡΟΠΟΡΙΑΣ\n");
    fprintf(file, "09 12 ΗΜΕΡΑ ΚΑΤΑ ΤΗΣ ΔΙΑΦΘΟΡΑΣ\n");
    fprintf(file, "10 12 ΗΜΕΡΑ ΤΩΝ ΑΝΘΡΩΠΙΝΩΝ ΔΙΚΑΙΩΜΑΤΩΝ ΚΑΙ ΤΗΣ ΔΙΕΘΝΟΥΣ ΑΜΝΗΣΤΙΑΣ\n");
    fprintf(file, "11 12 ΗΜΕΡΑ ΤΟΥ ΠΑΙΔΙΟΥ\n");
    fprintf(file, "11 12 ΗΜΕΡΑ ΤΩΝ ΒΟΥΝΩΝ\n");
    fprintf(file, "18 12 ΗΜΕΡΑ ΤΩΝ ΜΕΤΑΝΑΣΤΩΝ\n");
    fclose(file);
}

void readFile(char *filename, int day, int month)
{
    struct event giorti;
    FILE *file;
    char onoma[BUFFER];    /* Flawfinder: ignore */
    int mera;
    int minas;
    int size;
    int i;

    file = fopen(filename, "r");    /* Flawfinder: ignore */

    if (!file)
    {
        return;
    }

    while (!feof(file))
    {
        fgets(onoma, BUFFER, file);
        onoma[BUFFER-1] = '\0';
        if (!feof(file) && onoma[0]!='#' && onoma[0]!='\n')
        {
            sscanf(onoma, "%d %d", &mera, &minas);
            if ((mera == day) && (minas == month))
            {
                size = strlen(onoma)-1;
                for (i=0;i<size-6;i++)
                {
                    onoma[i]=onoma[i+6];
                }
                onoma[i]='\0';
                giorti.mera = mera;
                giorti.minas = minas;
                strncpy(giorti.paragoga, "", 400);
                giorti.paragoga[399]='\0';
                strncpy(giorti.kiniti, "", 4);
                giorti.kiniti[3]='\0';
                strncpy(giorti.onoma, onoma, 200);
                giorti.onoma[199]='\0';
                print(giorti);
            }
        }
    }

    fclose(file);
}
