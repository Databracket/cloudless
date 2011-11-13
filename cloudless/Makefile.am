lib_LTLIBRARIES = libcloudless.la

cloudlessincludedir = $(includedir)/cloudless
nobase_cloudlessinclude_HEADERS = details/noncopyable.hpp details/export.hpp \
								  details/exception.hpp details/singleton.hpp \
								  details/shared_ptr.hpp details/shared_array.hpp \
								  details/zeromq/zcontext.hpp details/zeromq/zeromq.hpp \
								  details/zeromq/zmessage.hpp details/zeromq/zsocket.hpp \
								  socket.hpp address.hpp context.hpp element.hpp \
								  exceptions.hpp messages.hpp poller.hpp pollitem.hpp \
								  version.hpp
nobase_nodist_cloudlessinclude_HEADERS = details/platform.hpp

libcloudless_la_SOURCES = details/zeromq/zcontext.cpp details/zeromq/zmessage.cpp \
						  details/zeromq/zsocket.cpp socket.cpp \
						  address.cpp context.cpp element.cpp exceptions.cpp \
						  messages.cpp pollitem.cpp poller.cpp

if ON_MINGW
libcloudless_la_LDFLAGS = -no-undefined -avoid-version -version-info @LTVER@ @LIBCLOUDLESS_EXTRA_LDFLAGS@
else
libcloudless_la_LDFLAGS = -version-info @LTVER@ @LIBCLOUDLESS_EXTRA_LDFLAGS@
endif

libcloudless_la_LDFLAGS += @ZMQ_LIBS@

libcloudless_la_CXXFLAGS = -I'$(top_srcdir)' -I'$(top_builddir)' @LIBCLOUDLESS_EXTRA_CXXFLAGS@

dist-hook:
	-rm $(distdir)/details/platform.hpp
