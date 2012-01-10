dnl ################################################################################
dnl # LIBCRYPTOPP([action-if-found], [action-if-not-found])                        #
dnl # Try to find and detect libcryptopp                                           #
dnl ################################################################################
AC_DEFUN([LIBCRYPTOPP],[

AC_ARG_WITH(
  [libcryptopp],
  [AC_HELP_STRING([--with-libcryptopp=DIR],[location of libcrypto++ build directory])],
  [libcryptopp_dir=${withval}],
  [libcryptopp_dir=])

AC_MSG_CHECKING([for libcrypto++])

# if libcryptopp_dir was given, add the necessary preprocessor and linker flags
#
if test x"$libcryptopp_dir" != x; then
  save_CPPFLAGS="$CPPFLAGS"
  save_LDFLAGS="$LDFLAGS"

  AS_SET_CATFILE([abs_libcryptopp_dir], [$ac_pwd], [$libcryptopp_dir])

  CPPFLAGS="$CPPFLAGS -I$abs_libcryptopp_dir -Wno-error"
  LDFLAGS="$LDFLAGS -L$abs_libcryptopp_dir"
fi

save_LIBS="$LIBS"
LIBS="-lcryptopp $LIBS"

# check if libcryptopp is available
libcryptopp_found=no

if test x"$libcryptopp_dir" != x; then

CXX_LIBTOOL_LINK_IFELSE([
AC_LANG_SOURCE([[
#include <sha.h>

using namespace CryptoPP;

int
main()
{
  SHA256 hd;
  return 0;
}
]])],
[libcryptopp_found=yes])

else

CXX_LIBTOOL_LINK_IFELSE([
AC_LANG_SOURCE([[
#include <cryptopp/sha.h>

using namespace CryptoPP;

int
main()
{
  SHA256 hd;
  return 0;
}
]])],
[libcryptopp_found=yes])

fi

if test x"$libcryptopp_dir" != x; then
  # Prevent -Wno-error from being global
  CPPFLAGS="$save_CPPFLAGS"
  CPPFLAGS="$CPPFLAGS -I$abs_libcryptopp_dir"
fi

if test x"$libcryptopp_found" = xno; then
  LIBS="$save_LIBS"

  if test x"$libcryptopp_dir" != x; then
    CPPFLAGS="$save_CPPFLAGS"
    LDFLAGS="$save_LDFLAGS"
  fi
fi

if test x"$libcryptopp_found" = xyes; then
  AC_MSG_RESULT([yes])
  AC_DEFINE(HAVE_CRYPTOPP, 1, [Have libcrypto++])
  $1
else
  AC_MSG_RESULT([no])
  $2
fi
])
