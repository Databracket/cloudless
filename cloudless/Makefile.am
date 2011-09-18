lib_LTLIBRARIES = libcloudless.la

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = libcloudless.pc

include_HEADERS = $(top_srcdir)/include/cloudless.h

cloudlessincludedir = $(includedir)/cloudless
nobase_cloudlessinclude_HEADERS = zsocket.hpp common.hpp
nobase_nodist_cloudlessinclude_HEADERS = platform.hpp

libcloudless_la_SOURCES = zsocket.cpp

if ON_MINGW
libcloudless_la_LDFLAGS = -no-undefined -avoid-version -version-info @LTVER@ @LIBCLOUDLESS_EXTRA_LDFLAGS@
else
libcloudless_la_LDFLAGS = -version-info @LTVER@ @LIBCLOUDLESS_EXTRA_LDFLAGS@
endif

libcloudless_la_CXXFLAGS = -I'$(top_srcdir)' -I'$(top_builddir)' @LIBCLOUDLESS_EXTRA_CXXFLAGS@

dist-hook:
	-rm $(distdir)/platform.hpp

