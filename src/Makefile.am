AM_CFLAGS = -Wall -O3
AM_LDFLAGS = -s 

DEFS = @DEFS@ \
       -DPIXMAPDIR=\"$(datadir)/pixmaps\" \
       -DDATADIR=\"$(datadir)/$(PACKAGE)\" \
       -D_\(String\)=gettext\(String\) \
       -DLOCALEDIR=\"$(localedir)\" 

bin_PROGRAMS = giortes
giortes_SOURCES = check.c\
check.h\
dates.c\
dates.h\
files.c\
files.h\
help.c\
help.h\
init.c\
init.h\
interface.c\
interface.h\
main.c\
options.c\
options.h\
print.c\
print.h\
search.c\
search.h

noinst_HEADERS = gettext.h
