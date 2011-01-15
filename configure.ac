#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT(giortes, 1.3, forfolias@linuxteam.cs.teilar.gr)
AM_INIT_AUTOMAKE(giortes, 1.3)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_PROG_CC_STDC

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.17)

AC_CHECK_HEADERS(stdlib.h)
AC_CHECK_HEADERS(unistd.h)

AC_MSG_CHECKING([for Win32 platform])
case "$host" in
  *-*-mingw*)
    platform_win32=yes
    ;;
    *linux* )
    platform_win32=no
    ;;
esac

if test "$platform_win32" = "yes"; then
	AC_MSG_RESULT([yes])
	LIBS="$LIBS -lintl -liconv"
	AC_CHECK_HEADERS(direct.h, , AC_MSG_ERROR([You need the win32 api]))
else
	AC_MSG_RESULT([no])
fi

AC_DEFUN([AM_PATH_GTK], true)
AC_ARG_ENABLE(gtk-gui, [AC_HELP_STRING([--enable-gtk-gui],[enable the gtk-gui])], ok=$enableval, ok="yes")

if test "$ok" = "yes"; then
	AM_PATH_GTK_2_0(2.16.0,
		CFLAGS="$CFLAGS $GTK_CFLAGS"
		LIBS="$LIBS $GTK_LIBS"
		if test "$platform_win32" = "yes"; then
			LDFLAGS="$LDFLAGS -mwindows"
		fi
		AC_DEFINE(GTK_GUI, 1, [Define to enable gtk-gui.]),
		    AC_MSG_WARN([Building without GTK GUI. To enable GTK+ GUI install the package libgtk2.0-dev (on Debian and derivatives) and run this configure again.])
		AC_DEFINE(NO_GUI, 1, [Define to disable gui.]) )
else
        AC_DEFINE(NO_GUI, 1, [Define to disable gui.])
fi

AC_CONFIG_FILES(Makefile src/Makefile pixmap/Makefile data/Makefile po/Makefile.in)
AC_OUTPUT