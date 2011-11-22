dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_DOC_BUILD                                               #
dnl # Check whether to build documentation and install man-pages                 #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_DOC_BUILD], [{
    # Allow user to disable doc build
    AC_ARG_WITH([documentation], [AS_HELP_STRING([--without-documentation],
        [disable documentation build even if asciidoc and xmlto are present [default=no]])])

    if test "x$with_documentation" = "xno"; then
        libcloudless_build_doc="no"
        libcloudless_install_man="no"
    else
        # Determine whether or not documentation should be built and installed.
        libcloudless_build_doc="yes"
        libcloudless_install_man="yes"
        # Check for asciidoc and xmlto and don't build the docs if these are not installed.
        AC_CHECK_PROG(libcloudless_have_asciidoc, asciidoc, yes, no)
        AC_CHECK_PROG(libcloudless_have_xmlto, xmlto, yes, no)
        if test "x$libcloudless_have_asciidoc" = "xno" -o "x$libcloudless_have_xmlto" = "xno"; then
            libcloudless_build_doc="no"
            # Tarballs built with 'make dist' ship with prebuilt documentation.
            if ! test -f doc/zmq.7; then
                libcloudless_install_man="no"
                AC_MSG_WARN([You are building an unreleased version of Cloudless and asciidoc or xmlto are not installed.])
                AC_MSG_WARN([Documentation will not be built and manual pages will not be installed.])
            fi
        fi

        # Do not install man pages if on mingw
        if test "x$libcloudless_on_mingw32" = "xyes"; then
            libcloudless_install_man="no"
        fi
    fi

    AC_MSG_CHECKING([whether to build documentation])
    AC_MSG_RESULT([$libcloudless_build_doc])

    AC_MSG_CHECKING([whether to install manpages])
    AC_MSG_RESULT([$libcloudless_install_man])

    AM_CONDITIONAL(BUILD_DOC, test "x$libcloudless_build_doc" = "xyes")
    AM_CONDITIONAL(INSTALL_MAN, test "x$libcloudless_install_man" = "xyes")
}])
