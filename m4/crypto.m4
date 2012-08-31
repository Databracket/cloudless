dnl ################################################################################
dnl # ENABLE_CRYPTO([action-if-found], [action-if-not-found])                      #
dnl # Check to whether enable cryptographic facilities                             #
dnl ################################################################################
AC_DEFUN([ENABLE_CRYPTO],[

AC_ARG_ENABLE(
  [crypto],
  [AC_HELP_STRING([--disable-crypto],[Disable cryptographic facilities [default=no]])],
  [crypto_disable=yes],[crypto_disable=no])

AC_MSG_CHECKING([whether to enable cryptographic facilities])

if test x"$crypto_disable" = xno; then
AC_MSG_RESULT([yes])
[$1]
:
else
AC_MSG_RESULT([no])
[$2]
:
fi

])
