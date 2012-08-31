dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_ICC([action-if-found], [action-if-not-found])      #
dnl # Check if the current language is compiled using ICC                        #
dnl # Adapted from http://software.intel.com/en-us/forums/showthread.php?t=67984 #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_ICC],
          [AC_CACHE_CHECK([whether we are using Intel _AC_LANG compiler],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler],
          [_AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],
[[#ifndef __INTEL_COMPILER
       error if not ICC
#endif
]])],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler="yes" ; $1],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler="no" ; $2])
])])

dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_SUN_STUDIO([action-if-found], [action-if-not-found])#
dnl # Check if the current language is compiled using Sun Studio                 #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_SUN_STUDIO],
          [AC_CACHE_CHECK([whether we are using Sun Studio _AC_LANG compiler],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler],
          [_AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],
[[#if !defined(__SUNPRO_CC) && !defined(__SUNPRO_C)
       error if not sun studio
#endif
]])],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler="yes" ; $1],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler="no" ; $2])
])])

dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_CLANG([action-if-found], [action-if-not-found])    #
dnl # Check if the current language is compiled using clang                      #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_CLANG],
          [AC_CACHE_CHECK([whether we are using clang _AC_LANG compiler],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler],
          [_AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],
[[#ifndef __clang__
       error if not clang
#endif
]])],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler="yes" ; $1],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler="no" ; $2])
])])

dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_GCC4([action-if-found], [action-if-not-found])     #
dnl # Check if the current language is compiled using GCC >= v4.0                #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_GCC4],
          [AC_CACHE_CHECK([whether we are using gcc >= 4 _AC_LANG compiler],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_gcc4_compiler],
          [_AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],
[[#if (!defined __GNUC__ || __GNUC__ < 4)
       error if not gcc4 or higher
#endif
]])],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_gcc4_compiler="yes" ; $1],
          [libcloudless_cv_[]_AC_LANG_ABBREV[]_gcc4_compiler="no" ; $2])
])])

dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_COMPILER([action-if-found], [action-if-not-found]) #
dnl # Check that compiler for the current language actually works                #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_COMPILER], [{
    # Test that compiler for the current language actually works
    AC_CACHE_CHECK([whether the _AC_LANG compiler works],
                   [libcloudless_cv_[]_AC_LANG_ABBREV[]_compiler_works],
                   [AC_LINK_IFELSE([AC_LANG_PROGRAM([], [])],
                   [libcloudless_cv_[]_AC_LANG_ABBREV[]_compiler_works="yes" ; $1],
                   [libcloudless_cv_[]_AC_LANG_ABBREV[]_compiler_works="no" ; $2])
                   ])

    if test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_compiler_works" != "xyes"; then
        AC_MSG_ERROR([Unable to find a working _AC_LANG compiler])
    fi
}])

dnl ##############################################################################
dnl # LIBCLOUDLESS_CHECK_COMPILERS                                               #
dnl # Check compiler characteristics. This is so that we can AC_REQUIRE checks   #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_COMPILERS], [{
    # For that the compiler works and try to come up with the type
    AC_LANG_PUSH([C])
    LIBCLOUDLESS_CHECK_LANG_COMPILER

    LIBCLOUDLESS_CHECK_LANG_ICC
    LIBCLOUDLESS_CHECK_LANG_SUN_STUDIO
    LIBCLOUDLESS_CHECK_LANG_CLANG
    LIBCLOUDLESS_CHECK_LANG_GCC4
    AC_LANG_POP([C])

    AC_LANG_PUSH(C++)
    LIBCLOUDLESS_CHECK_LANG_COMPILER

    LIBCLOUDLESS_CHECK_LANG_ICC
    LIBCLOUDLESS_CHECK_LANG_SUN_STUDIO
    LIBCLOUDLESS_CHECK_LANG_CLANG
    LIBCLOUDLESS_CHECK_LANG_GCC4
    AC_LANG_POP([C++])

    # Set GCC and GXX variables correctly
    if test "x$GCC" = "xyes"; then
        if test "xyes" = "x$libcloudless_cv_c_intel_compiler"; then
            GCC="no"
        fi
    fi

    if test "x$GXX" = "xyes"; then
        if test "xyes" = "x$libcloudless_cv_cxx_intel_compiler"; then
            GXX="no"
        fi
    fi
}])

dnl ############################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_FLAG([flag], [action-if-found], [action-if-not-found]) #
dnl # Check if the compiler supports given flag. Works for C and C++           #
dnl # Sets libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_[FLAG]=yes/no     #
dnl ############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_FLAG], [{

    AC_REQUIRE([AC_PROG_GREP])

    AC_MSG_CHECKING([whether _AC_LANG compiler supports $1])

    libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag_save=$ac_[]_AC_LANG_ABBREV[]_werror_flag
    ac_[]_AC_LANG_ABBREV[]_werror_flag="yes"

    case "x[]_AC_LANG_ABBREV" in
        xc)
            libcloudless_cv_check_lang_flag_save_CFLAGS="$CFLAGS"
            CFLAGS="$CFLAGS $1"
        ;;
        xcxx)
            libcloudless_cv_check_lang_flag_save_CPPFLAGS="$CPPFLAGS"
            CPPFLAGS="$CPPFLAGS $1"
        ;;
        *)
            AC_MSG_WARN([testing compiler characteristic on an unknown language])
        ;;
    esac

    AC_COMPILE_IFELSE([AC_LANG_PROGRAM()],
                      # This hack exist for ICC, which outputs unknown options as remarks
                      # Remarks are not turned into errors even with -Werror on
                      [if ($GREP 'ignoring unknown' conftest.err ||
                           $GREP 'not supported' conftest.err) >/dev/null 2>&1; then
                           eval AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_$1)="no"
                       else
                           eval AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_$1)="yes"
                       fi],
                      [eval AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_$1)="no"])

    case "x[]_AC_LANG_ABBREV" in
        xc)
            CFLAGS="$libcloudless_cv_check_lang_flag_save_CFLAGS"
        ;;
        xcxx)
            CPPFLAGS="$libcloudless_cv_check_lang_flag_save_CPPFLAGS"
        ;;
        *)
            # nothing to restore
        ;;
    esac

    # Restore the werror flag
    ac_[]_AC_LANG_ABBREV[]_werror_flag=$libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag_save

    # Call the action as the flags are restored
    AS_IF([eval test x$]AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_$1)[ = "xyes"],
          [AC_MSG_RESULT(yes) ; $2], [AC_MSG_RESULT(no) ; $3])

}])

dnl ####################################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_FLAG_PREPEND([flag], [action-if-found], [action-if-not-found]) #
dnl # Check if the compiler supports given flag. Works for C and C++                   #
dnl # This macro prepends the flag to CFLAGS or CPPFLAGS accordingly                   #
dnl # Sets libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_[FLAG]=yes/no             #
dnl ####################################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_FLAG_PREPEND], [{
    LIBCLOUDLESS_CHECK_LANG_FLAG([$1])
    case "x[]_AC_LANG_ABBREV" in
       xc)
            AS_IF([eval test x$]AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_$1)[ = "xyes"],
                  [CFLAGS="$1 $CFLAGS"; $2], $3)
       ;;
       xcxx)
            AS_IF([eval test x$]AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_flag_$1)[ = "xyes"],
                  [CPPFLAGS="$1 $CPPFLAGS"; $2], $3)
       ;;
    esac
}])

dnl ##############################################################################
dnl # AC_CLOUDLESS_CHECK_WITH_FLAG([flags], [macro])                             #
dnl # Runs a normal autoconf check with compiler flags                           #
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_WITH_FLAG], [{
    libcloudless_check_with_flag_save_CFLAGS="$CFLAGS"
    libcloudless_check_with_flag_save_CPPFLAGS="$CPPFLAGS"

    CFLAGS="$CFLAGS $1"
    CPPFLAGS="$CPPFLAGS $1"

    # Execute the macro
    $2

    CFLAGS="$libcloudless_check_with_flag_save_CFLAGS"
    CPPFLAGS="$libcloudless_check_with_flag_save_CPPFLAGS"
}])

dnl ##############################################################################
dnl # LIBCLOUDLESS_LANG_WALL([action-if-found], [action-if-not-found])           #
dnl # How to define -Wall for the current compiler                               #
dnl # Sets libcloudless_cv_[]_AC_LANG_ABBREV[]__wall_flag variable to found style#
dnl ##############################################################################
AC_DEFUN([LIBCLOUDLESS_LANG_WALL], [{

    AC_MSG_CHECKING([how to enable additional warnings for _AC_LANG compiler])

    libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag=""

    # C compilers
    case "x[]_AC_LANG_ABBREV" in
       xc)
            # GCC, clang and ICC
            if test "x$GCC" = "xyes" -o \
                    "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes" -o \
                    "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag="-Wall"
            # Sun studio
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag="-v"
            fi
       ;;
       xcxx)
            # GCC, clang and ICC
            if test "x$GXX" = "xyes" -o \
                    "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes" -o \
                    "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag="-Wall"
            # Sun studio
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag="+w"
            fi
       ;;
       *)
       ;;
    esac

    # Call the action
    if test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag" != "x"; then
        AC_MSG_RESULT([$libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag])
        $1
    else
        AC_MSG_RESULT([not found])
        $2
    fi
}])

dnl ####################################################################
dnl # LIBCLOUDLESS_LANG_STRICT([action-if-found], [action-if-not-found])#
dnl # Check how to turn on strict standards compliance                 #
dnl ####################################################################
AC_DEFUN([LIBCLOUDLESS_LANG_STRICT], [{
    AC_MSG_CHECKING([how to enable strict standards compliance in _AC_LANG compiler])

    libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag=""

    # C compilers
    case "x[]_AC_LANG_ABBREV" in
       xc)
            # GCC, clang and ICC
            if test "x$GCC" = "xyes" -o "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag="-pedantic"
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag="-strict-ansi"
            # Sun studio
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag="-Xc"
            fi
       ;;
       xcxx)
            # GCC, clang and ICC
            if test "x$GXX" = "xyes" -o "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag="-pedantic"
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag="-strict-ansi"
            # Sun studio
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag="-compat=5"
            fi
       ;;
       *)
       ;;
    esac

    # Call the action
    if test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag" != "x"; then
        AC_MSG_RESULT([$libcloudless_cv_[]_AC_LANG_ABBREV[]_strict_flag])
        $1
    else
        AC_MSG_RESULT([not found])
        $2
    fi
}])

dnl ########################################################################
dnl # LIBCLOUDLESS_LANG_WERROR([action-if-found], [action-if-not-found])   #
dnl # Check how to turn warnings to errors                                 #
dnl ########################################################################
AC_DEFUN([LIBCLOUDLESS_LANG_WERROR], [{
    AC_MSG_CHECKING([how to turn warnings to errors in _AC_LANG compiler])

    libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag=""

    # C compilers
    case "x[]_AC_LANG_ABBREV" in
       xc)
            # GCC, clang and ICC
            if test "x$GCC" = "xyes" -o "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag="-Werror"
            # Sun studio
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag="-errwarn=%all"
            fi
       ;;
       xcxx)
            # GCC, clang and ICC
            if test "x$GXX" = "xyes" -o "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag="-Werror"
            # Sun studio
            elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
                libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag="-errwarn=%all"
            fi
       ;;
       *)
       ;;
    esac

    # Call the action
    if test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag" != "x"; then
        AC_MSG_RESULT([$libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag])
        $1
    else
        AC_MSG_RESULT([not found])
        $2
    fi
}])

dnl ################################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_PRAGMA([pragma], [action-if-found], [action-if-not-found]) #
dnl # Check if the compiler supports given pragma                                  #
dnl ################################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_PRAGMA], [{
    # Need to know how to enable all warnings
    LIBCLOUDLESS_LANG_WALL

    AC_MSG_CHECKING([whether _AC_LANG compiler supports pragma $1])

    # Save flags
    libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag_save=$ac_[]_AC_LANG_ABBREV[]_werror_flag
    ac_[]_AC_LANG_ABBREV[]_werror_flag="yes"

    if test "x[]_AC_LANG_ABBREV" = "xc"; then
        libcloudless_cv_check_lang_pragma_save_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS $libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag"
    elif test "x[]_AC_LANG_ABBREV" = "xcxx"; then
        libcloudless_cv_check_lang_pragma_save_CPPFLAGS="$CPPFLAGS"
        CPPFLAGS="$CPPFLAGS $libcloudless_cv_[]_AC_LANG_ABBREV[]_wall_flag"
    else
        AC_MSG_WARN([testing compiler characteristic on an unknown language])
    fi

    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [[#pragma $1]])],
                      [eval AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_pragma_$1)="yes" ; AC_MSG_RESULT(yes)],
                      [eval AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_pragma_$1)="no" ; AC_MSG_RESULT(no)])

    if test "x[]_AC_LANG_ABBREV" = "xc"; then
        CFLAGS="$libcloudless_cv_check_lang_pragma_save_CFLAGS"
    elif test "x[]_AC_LANG_ABBREV" = "xcxx"; then
        CPPFLAGS="$libcloudless_cv_check_lang_pragma_save_CPPFLAGS"
    fi

    ac_[]_AC_LANG_ABBREV[]_werror_flag=$libcloudless_cv_[]_AC_LANG_ABBREV[]_werror_flag_save

    # Call the action as the flags are restored
    AS_IF([eval test x$]AS_TR_SH(libcloudless_cv_[]_AC_LANG_ABBREV[]_supports_pragma_$1)[ = "xyes"],
          [$2], [$3])
}])

dnl ################################################################################
dnl # LIBCLOUDLESS_CHECK_LANG_VISIBILITY([action-if-found], [action-if-not-found]) #
dnl # Check if the compiler supports dso visibility                                #
dnl ################################################################################
AC_DEFUN([LIBCLOUDLESS_CHECK_LANG_VISIBILITY], [{

    libcloudless_cv_[]_AC_LANG_ABBREV[]_visibility_flag=""

    if test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_intel_compiler" = "xyes" -o \
            "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_clang_compiler" = "xyes" -o \
            "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_gcc4_compiler" = "xyes"; then
        LIBCLOUDLESS_CHECK_LANG_FLAG([-fvisibility=hidden],
                               [libcloudless_cv_[]_AC_LANG_ABBREV[]_visibility_flag="-fvisibility=hidden"])
    elif test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_sun_studio_compiler" = "xyes"; then
        LIBCLOUDLESS_CHECK_LANG_FLAG([-xldscope=hidden],
                               [libcloudless_cv_[]_AC_LANG_ABBREV[]_visibility_flag="-xldscope=hidden"])
    fi

    AC_MSG_CHECKING(whether _AC_LANG compiler supports dso visibility)

    AS_IF([test "x$libcloudless_cv_[]_AC_LANG_ABBREV[]_visibility_flag" != "x"],
          [AC_MSG_RESULT(yes) ; $1], [AC_MSG_RESULT(no) ; $2])
}])
