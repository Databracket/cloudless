dnl ##############################################################################
dnl # LIBCLOUDLESS_WITH_GCOV([action-if-found], [action-if-not-found])           #
dnl # Check whether to build with code coverage                                  #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_WITH_GCOV], [{
    # Require compiler specifics
    AC_REQUIRE([LIBCLOUDLESS_CHECK_COMPILERS])

    AC_ARG_WITH(gcov, [AS_HELP_STRING([--with-gcov=yes/no],
                      [With GCC Code Coverage reporting.])],
                      [CLOUDLESS_GCOV="$withval"])

    AC_MSG_CHECKING(whether to enable code coverage)

    if test "x$CLOUDLESS_GCOV" = "xyes"; then

        if test "x$GXX" != "xyes"; then
            AC_MSG_ERROR([--with-gcov=yes works only with GCC])
        fi

        CFLAGS="-g -O0 -fprofile-arcs -ftest-coverage"
        if test "x${CLOUDLESS_ORIG_CPPFLAGS}" != "xnone"; then
            CFLAGS="${CFLAGS} ${CLOUDLESS_ORIG_CFLAGS}"
        fi

        CPPFLAGS="-g -O0 -fprofile-arcs -ftest-coverage"
        if test "x${CLOUDLESS_ORIG_CPPFLAGS}" != "xnone"; then
            CPPFLAGS="${CPPFLAGS} ${CLOUDLESS_ORIG_CPPFLAGS}"
        fi

        CXXFLAGS="-fprofile-arcs"
        if test "x${CLOUDLESS_ORIG_CXXFLAGS}" != "xnone"; then
            CXXFLAGS="${CXXFLAGS} ${CLOUDLESS_ORIG_CXXFLAGS}"
        fi

        LIBS="-lgcov ${LIBS}"
    fi

    AS_IF([test "x$CLOUDLESS_GCOV" = "xyes"],
          [AC_MSG_RESULT(yes) ; $1], [AC_MSG_RESULT(no) ; $2])
}])
