#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([vcdct], [0.1], [pawel.szostek@cern.ch])
AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

# automake initialisation and check for minimal automake API version 1.9
AM_INIT_AUTOMAKE([1.9])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h limits.h malloc.h stddef.h stdlib.h string.h unistd.h])
AC_CHECK_HEADER([string iostream])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPES([ptrdiff_t])
# check for libraries
AC_CHECK_LIB(boost_program_options, main)
AC_CHECK_LIB(boost_regex, main)

# distribute additional compiler and linker flags
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# Checks for library functions.
AC_FUNC_FSEEKO
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([ftruncate memchr memset strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/libfst/Makefile
                 src/libz/Makefile])
AC_OUTPUT
