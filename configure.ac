#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.53])
AC_INIT([libuthread], [0.1], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/uthread.h])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([-Wall])

# Checks for programs.
AC_PROG_CC_C99

AC_PROG_RANLIB

case "$target" in
*-pc-mingw32* )
AM_CONDITIONAL(OS_WIN32,[true])
;;
*-linux-* | *linux*  | *linux )
AM_CONDITIONAL(OS_WIN32,[false])
;;
* )
esac
# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
src/Makefile
test/Makefile])

AC_OUTPUT
