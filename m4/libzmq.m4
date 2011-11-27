dnl ################################################################################
dnl # LIBZMQ([action-if-found], [action-if-not-found])                             #
dnl # Try to find and detect libzmq version                                        #
dnl ################################################################################
AC_DEFUN([LIBZMQ],[

AC_ARG_WITH(
  [libzmq],
  [AC_HELP_STRING([--with-libzmq=DIR],[location of libzmq build directory])],
  [libzmq_dir=${withval}],
  [libzmq_dir=])

AC_MSG_CHECKING([for libzmq])

# if libzmq_dir was given, add the necessary preprocessor and linker flags.
#
if test x"$libzmq_dir" != x; then
  save_CPPFLAGS="$CPPFLAGS"
  save_LDFLAGS="$LDFLAGS"

  AS_SET_CATFILE([abs_libzmq_dir], [$ac_pwd], [$libzmq_dir])

  CPPFLAGS="$CPPFLAGS -I$abs_libzmq_dir/include"
  LDFLAGS="$LDFLAGS -L$abs_libzmq_dir/src"
fi

save_LIBS="$LIBS"
LIBS="-lzmq $LIBS"

# check if libzmq is available
libzmq_found=no

CXX_LIBTOOL_RUN_IFELSE([
AC_LANG_SOURCE([[
#include <zmq.h>

int
main()
{
  int major, minor, patch;

  zmq_version(&major, &minor, &patch);
  return 0;
}
]])],
[libzmq_found=yes])

if test x"$libzmq_found" = xyes; then

# check if libzmq is of version 2.1.x
libzmq_v2_1_x=no

CXX_LIBTOOL_RUN_IFELSE([
AC_LANG_SOURCE([[
#include <zmq.h>

int
main()
{
  int major, minor, patch;

  zmq_version(&major, &minor, &patch);
  return (major == 2 && minor == 1 && patch > 0) ? 0 : 1;
}
]])],
[libzmq_v2_1_x=yes])

# check if libzmq is of version 3.1.x
libzmq_v3_1_x=no

CXX_LIBTOOL_RUN_IFELSE([
AC_LANG_SOURCE([[
#include <zmq.h>

int
main()
{
  int major, minor, patch;

  zmq_version(&major, &minor, &patch);
  return (major == 3 && minor == 1 && patch >= 0) ? 0 : 1;
}
]])],
[libzmq_v3_1_x=yes])

if test x"$libzmq_v2_1_x" = xno -a x"$libzmq_v3_1_x" = xno; then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([version of libzmq is not supported])
fi

fi

if test x"$libzmq_found" = xno; then
  LIBS="$save_LIBS"

  if test x"$libzmq_dir" != x; then
    CPPFLAGS="$save_CPPFLAGS"
    LDFLAGS="$save_LDFLAGS"
  fi
fi

if test x"$libzmq_found" = xyes; then
  if test x"$libzmq_v2_1_x" = xyes; then
    AC_DEFINE([HAVE_ZMQ_MAJOR], [2], [0MQ major version.])
    AC_DEFINE([HAVE_ZMQ_MINOR], [1], [0MQ minor version.])
    AC_MSG_RESULT([v2.1.x])
  elif test x"$libzmq_v3_1_x" = xyes; then
    AC_DEFINE([HAVE_ZMQ_MAJOR], [3], [0MQ major version.])
    AC_DEFINE([HAVE_ZMQ_MINOR], [1], [0MQ minor version.])
    AC_MSG_RESULT([v3.1.x])
  fi

  $1
else
  AC_MSG_RESULT([no])
  $2
fi
])
