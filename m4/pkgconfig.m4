dnl ################################################################################
dnl # LIBCLOUDLESS_PKGCONFIG([action-if-found], [action-if-not-found])             #
dnl # Provide an option to set pkgconfig dir                                       #
dnl ################################################################################
AC_DEFUN([LIBCLOUDLESS_PKGCONFIG],[
AC_ARG_WITH(
  [pkgconfigdir],
  [AC_HELP_STRING([--with-pkgconfigdir=DIR],[location of pkgconfig dir (default is libdir/pkgcofnig)])],
  [pkgconfigdir=${withval}],
  [pkgconfigdir='${libdir}/pkgconfig'])
AC_SUBST([pkgconfigdir])
])
