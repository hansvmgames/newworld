#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([newworld], [0.0.1], [hansvm.games@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/common/type.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AX_CFLAGS_WARN_ALL

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AX_PTHREAD([AC_DEFINE(HAVE_PTHREAD,1,[POSIX compatible threading library found])],[AC_MSG_ERROR([no POSIX compatible threading library found])])

LIBS="$PTHREAD_LIBS $LIBS"
CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
CC="$PTHREAD_CC"

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/common/Makefile])
AC_OUTPUT
