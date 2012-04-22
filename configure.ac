#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.67])
LT_PREREQ([2.4.0])
#
# The Cloudless version number is extracted from cloudless/version.hpp using
# the version.sh script. Hence, it should be updated there.
# The version in git should reflect the *next* version planned.
#
AC_INIT([cloudless],[m4_esyscmd([./version.sh])],[dev@cloudless.io])

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR(m4)
AM_CONFIG_HEADER(cloudless/details/platform.hpp)
AM_INIT_AUTOMAKE(tar-ustar dist-zip dist-bzip2 subdir-objects nostdinc foreign)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# This lets us use PACKAGE_VERSION in Makefiles
AC_SUBST(PACKAGE_VERSION)

# Libtool -version-info (ABI version)
#
# Don't change this unless you know exactly what you're doing and have read and
# understand:
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
#
# libcloudless -version-info current:revision:age
LTVER="1:0:0"
AC_SUBST(LTVER)

# Take a copy of original flags
CLOUDLESS_ORIG_CFLAGS="${CFLAGS:-none}"
CLOUDLESS_ORIG_CPPFLAGS="${CPPFLAGS:-none}"
CLOUDLESS_ORIG_CXXFLAGS="${CXXFLAGS:-none}"

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_SED
AC_PROG_AWK

# initialize libtool
LT_INIT([win32-dll])
AC_SUBST([LIBTOOL_DEPS])

# Generate configured libtool
LT_OUTPUT

AC_ARG_VAR([XMLTO], [Path to xmlto command])
AC_PATH_PROG([XMLTO], [xmlto])
AC_ARG_VAR([ASCIIDOC], [Path to asciidoc command])
AC_PATH_PROG([ASCIIDOC], [asciidoc])
LIBCLOUDLESS_CONFIG_LIBTOOL

# Check whether to build with debug symbols
LIBCLOUDLESS_CHECK_ENABLE_DEBUG

# Check whether to enable code coverage
LIBCLOUDLESS_WITH_GCOV

# Set pkgconfig dir
LIBCLOUDLESS_PKGCONFIG

# Define LIBCLOUDLESS_STATIC_LIB if we are building static library on certain platforms
STATIC_LIB([LIBCLOUDLESS_STATIC_LIB], [Static library interface.])

# Set pedantic
libcloudless_pedantic="yes"

# By default compiling with -Werror except OSX.
libcloudless_werror="yes"

# By default use DSO visibility
libcloudless_dso_visibility="yes"

# Whether we are on mingw or not.
libcloudless_on_mingw32="no"

# For host type checks
AC_CANONICAL_HOST

# OS-specific tests
case "${host_os}" in
    *linux*)
        # Define on Linux to enable all library features. Define if using a gnu compiler
        if test "x$GXX" = "xyes"; then
            CPPFLAGS="-D_GNU_SOURCE $CPPFLAGS"
        fi
        AC_DEFINE(CLOUDLESS_HAVE_LINUX, 1, [Have Linux OS])
        ;;
    *solaris*)
        # Define on Solaris to enable all library features
        AC_DEFINE(CLOUDLESS_HAVE_SOLARIS, 1, [Have Solaris OS])
        ;;
    *freebsd*)
        # Define on FreeBSD to enable all library features
        CPPFLAGS="-D__BSD_VISIBLE $CPPFLAGS"
        AC_DEFINE(CLOUDLESS_HAVE_FREEBSD, 1, [Have FreeBSD OS])
        ;;
    *darwin*)
        # Define on Darwin to enable all library features
        CPPFLAGS="-D_DARWIN_C_SOURCE $CPPFLAGS"
        libcloudless_pedantic="no"
        libcloudless_werror="no"
        AC_DEFINE(CLOUDLESS_HAVE_OSX, 1, [Have DarwinOSX OS])
        AC_LANG_PUSH([C++])
        LIBCLOUDLESS_CHECK_LANG_FLAG_PREPEND([-Wno-uninitialized])
        AC_LANG_POP([C++])
        ;;
    *netbsd*)
        # Define on NetBSD to enable all library features
        CPPFLAGS="-D_NETBSD_SOURCE $CPPFLAGS"
        AC_DEFINE(CLOUDLESS_HAVE_NETBSD, 1, [Have NetBSD OS])
        AC_DEFINE(CLOUDLESS_FORCE_MUTEXES, 1, [Force to use mutexes])
        ;;
    *openbsd*)
        # Define on OpenBSD to enable all library features
        CPPFLAGS="-D_BSD_SOURCE $CPPFLAGS"
        AC_DEFINE(CLOUDLESS_HAVE_OPENBSD, 1, [Have OpenBSD OS])
        ;;
    *nto-qnx*)
        libcloudless_pedantic="no"
        AC_DEFINE(CLOUDLESS_HAVE_QNXNTO, 1, [Have QNX Neutrino OS])
        ;;
    *aix*)
        AC_DEFINE(CLOUDLESS_HAVE_AIX, 1, [Have AIX OS])
        ;;
    *hpux*)
        # Define on HP-UX to enable all library features
        CPPFLAGS="-D_POSIX_C_SOURCE=200112L $CPPFLAGS"
        AC_DEFINE(CLOUDLESS_HAVE_HPUX, 1, [Have HPUX OS])
        ;;
    *mingw32*)
        AC_DEFINE(CLOUDLESS_HAVE_WINDOWS, 1, [Have Windows OS])
        AC_DEFINE(CLOUDLESS_HAVE_MINGW32, 1, [Have MinGW32])
        AC_CHECK_HEADERS(windows.h)
        # mingw32 defines __int64_t as long long
        AC_LANG_PUSH([C++])
        LIBCLOUDLESS_CHECK_LANG_FLAG_PREPEND([-Wno-long-long])
        AC_LANG_POP([C++])
        libcloudless_on_mingw32="yes"
        libcloudless_dso_visibility="no"

        if test "x$enable_static" = "xyes"; then
            AC_MSG_ERROR([Building static libraries is not supported under MinGW32])
        fi
        ;;
    *cygwin*)
        # Define on Cygwin to enable all library features
        CPPFLAGS="-D_GNU_SOURCE $CPPFLAGS"
        AC_DEFINE(CLOUDLESS_HAVE_CYGWIN, 1, [Have Cygwin])

        if test "x$enable_static" = "xyes"; then
            AC_MSG_ERROR([Building static libraries is not supported under Cygwin])
        fi
        ;;
    *)
        AC_MSG_ERROR([unsupported system: ${host_os}.])
        ;;
esac

#
# Check if the compiler supports -fvisibility=hidden flag. MinGW32 uses __declspec
#
if test "x$libcloudless_dso_visibility" = "xyes"; then
    AC_LANG_PUSH([C++])
    LIBCLOUDLESS_CHECK_LANG_VISIBILITY([LIBCLOUDLESS_EXTRA_CXXFLAGS="$libcloudless_cv_[]_AC_LANG_ABBREV[]_visibility_flag ${LIBCLOUDLESS_EXTRA_CXXFLAGS}"])
    AC_LANG_POP([C++])
fi

# CPU-specific optimizations
case "${host_cpu}" in
    *sparc*)
        AC_LANG_PUSH([C++])
        LIBCLOUDLESS_CHECK_LANG_FLAG_PREPEND([-mcpu=v9])
        AC_LANG_POP([C++])
    ;;
    *)
    ;;
esac

# Check whether to build docs / install man pages
LIBCLOUDLESS_CHECK_DOC_BUILD

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(errno.h stddef.h stdlib.h string.h sys/time.h unistd.h limits.h)

# Use c++ in subsequent tests
AC_LANG_PUSH(C++)

AC_HEADER_STDBOOL
AC_HEADER_MAJOR
AC_C_INLINE
# Checks for typedefs, structures, and compiler characteristics.
if test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes"; then
    dnl 279: controlling expression is constant
    dnl Fixes build with ICC 12.x
    LIBCLOUDLESS_CHECK_WITH_FLAG([-wd279], [AC_TYPE_SIZE_T])
    LIBCLOUDLESS_CHECK_WITH_FLAG([-wd279], [AC_TYPE_SSIZE_T])
else
    AC_TYPE_SIZE_T
    AC_TYPE_SSIZE_T
fi
AC_TYPE_INT64_T
AC_TYPE_UINT64_T

# Set -Wall, -Werror and -pedantic
AC_LANG_PUSH([C++])

# Check how to enable -Wall
LIBCLOUDLESS_LANG_WALL([CPPFLAGS="$libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag $CPPFLAGS"])

if test "x$libcloudless_werror" = "xyes" -a "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" != "xyes"; then
    LIBCLOUDLESS_LANG_WERROR([CPPFLAGS="$libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag $CPPFLAGS"])
fi

if test "x$libcloudless_pedantic" = "xyes"; then
    LIBCLOUDLESS_LANG_STRICT([CPPFLAGS="$libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag $CPPFLAGS"])
fi
AC_LANG_POP([C++])

AM_CONDITIONAL(ON_MINGW, test "x$libcloudless_on_mingw32" = "xyes")

# Checks for library functions.
AC_CHECK_FUNCS(memset memcpy)

# Checks for libraries.
BOOST_REQUIRE([1.46.1])
BOOST_SMART_PTR
BOOST_BIND
BOOST_THREADS([mt-])
LIBZMQ([], [AC_MSG_ERROR([libzmq is not found; consider using --with-libzmq=DIR])])
ENABLE_CRYPTO([crypto_enable=yes])

if test "x$crypto_enable" = "xyes"; then
  LIBCRYPTOPP([], [AC_MSG_ERROR([libcrypto++ is not found; consider using --with-libcryptopp=DIR])])
fi

AM_CONDITIONAL([CRYPTO], [test x"$crypto_enable" = xyes])

# Set boost CPPFLAGS/LDFLAGS
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
LDFLAGS="$LDFLAGS $BOOST_THREAD_LDFLAGS"
LIBS="$LIBS $BOOST_THREAD_LIBS"

# Subset LIBCLOUDLESS_EXTRA_CFLAGS & CXXFLAGS & LDFLAGS
AC_SUBST(LIBCLOUDLESS_EXTRA_CFLAGS)
AC_SUBST(LIBCLOUDLESS_EXTRA_CXXFLAGS)
AC_SUBST(LIBCLOUDLESS_EXTRA_LDFLAGS)

AC_CONFIG_FILES([
		libcloudless.pc \
		Makefile \
		cloudless/Makefile \
		tests/Makefile])
AC_OUTPUT
