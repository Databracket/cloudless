dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_ENABLE_DEBUG([action-if-found], [action-if-not-found])  #
dnl # Check whether to enable debug build and set compiler flags accordingly     #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_ENABLE_DEBUG], [{

    # Require compiler specifics
    AC_REQUIRE([LIBCLOUDLESS_CHECK_COMPILERS])

    # This flag is checked also in
    AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug],
        [Enable debugging information [default=no]])])

    AC_MSG_CHECKING(whether to enable debugging information)

    if test "x$enable_debug" = "xyes"; then

        # GCC, clang and ICC
        if test "x$GCC" = "xyes" -o \
                "x$libcloudless_cv_c_intel_compiler" = "xyes" -o \
                "x$libcloudless_cv_c_clang_compiler" = "xyes"; then
            CFLAGS="-g -O0 "
        elif test "x$libcloudless_cv_c_sun_studio_compiler" = "xyes"; then
            CFLAGS="-g0 "
        fi

        # GCC, clang and ICC
        if test "x$GXX" = "xyes" -o \
                "x$libcloudless_cv_cxx_intel_compiler" = "xyes" -o \
                "x$libcloudless_cv_cxx_clang_compiler" = "xyes"; then
            CPPFLAGS="-g -O0 "
            CXXFLAGS="-g -O0 "
        # Sun studio
        elif test "x$libcloudless_cv_cxx_sun_studio_compiler" = "xyes"; then
            CPPFLAGS="-g0 "
            CXXFLAGS="-g0 "
        fi

        if test "x$CLOUDLESS_ORIG_CFLAGS" != "xnone"; then
            CFLAGS="${CFLAGS} ${CLOUDLESS_ORIG_CFLAGS}"
        fi
        if test "x$CLOUDLESS_ORIG_CPPFLAGS" != "xnone"; then
            CPPFLAGS="${CPPFLAGS} ${CLOUDLESS_ORIG_CPPFLAGS}"
        fi
        if test "x$CLOUDLESS_ORIG_CXXFLAGS" != "xnone"; then
            CXXFLAGS="${CXXFLAGS} ${CLOUDLESS_ORIG_CXXFLAGS}"
        fi
        AC_MSG_RESULT(yes)
    else
        AC_MSG_RESULT(no)
    fi
}])
