dnl ##############################################################################
dnl # LIBCLOUDLESS_CONFIG_LIBTOOL                                                #
dnl # Configure libtool. Requires AC_CANONICAL_HOST                              #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CONFIG_LIBTOOL],  [{
    AC_REQUIRE([AC_CANONICAL_HOST])

    # Libtool configuration for different targets
    case "${host_os}" in
        *mingw32*|*cygwin*)
            # Disable static build by default
            AC_DISABLE_STATIC
        ;;
        *)
            # Everything else with static enabled
            AC_ENABLE_STATIC
        ;;
    esac
}])

dnl ################################################################################
dnl # STATIS_LIB([action-if-found], [action-if-not-found])                         #
dnl # Define MACRO if we are on MinGW and are only building static library.        #
dnl ################################################################################
AC_DEFUN([STATIC_LIB],
[
if test x$enable_shared = xno; then
  case $host_os in
    mingw*)
      AC_DEFINE([$1], [1], [$2])
      ;;
  esac
fi
])
