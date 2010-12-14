#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([vcdct], [0.1], [pawel.szostek@cern.ch])
AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB
AC_CHECK_PROGS(XGPERF, gperf, none)
if test "$XGPERF" = "none"
then
	echo ""
        echo "*** Warning: No suitable gperf found. ***"
	echo "    The gperf package is essential for building vcdct from"
	echo "							sources							"
	echo ""
fi

# automake initialisation and check for minimal automake API version 1.9
AM_INIT_AUTOMAKE([1.9])
AC_LANG(C++)
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER([getopt.h])
AC_CHECK_HEADER([time.h])
AC_CHECK_HEADERS(inttypes.h limits.h malloc.h stddef.h)
AC_CHECK_HEADERS(stdlib.h string.h unistd.h stdio.h)
AC_CHECK_HEADERS(string iostream utility fstream stdexcept list vector map iterator algorithm stack)
AC_CHECK_HEADERS(boost/function.hpp boost/lexical_cast.hpp boost/shared_ptr.hpp boost/foreach.hpp)
AC_CHECK_HEADERS(boost/lambda/lambda.hpp boost/bind.hpp)

if 
# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPES([ptrdiff_t])
# check for libraries

# distribute additional compiler and linker flags
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

if test "$GCC" = yes; then
    CFLAGS="$CFLAGS -Wshadow -Wunused -Wall -Werror"
fi

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
