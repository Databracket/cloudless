lib_LTLIBRARIES = libcloudless.la

cloudlessincludedir = $(includedir)/cloudless
nobase_cloudlessinclude_HEADERS = details/noncopyable.hpp details/nonconstructive.hpp \
								  details/export.hpp details/exception.hpp \
								  details/singleton.hpp details/shared_ptr.hpp \
								  details/shared_array.hpp details/zeromq/zcontext.hpp \
								  details/zeromq/zeromq.hpp details/zeromq/zmessage.hpp details/zeromq/zsocket.hpp \
								  socket.hpp address.hpp context.hpp element.hpp \
								  exceptions.hpp message.hpp poller.hpp pollitem.hpp \
								  version.hpp req.hpp rep.hpp dealer.hpp router.hpp \
								  push.hpp pull.hpp pub.hpp sub.hpp pair.hpp

if ZMQ_3_X
nobase_cloudlessinclude_HEADERS += xsub.hpp xpub.hpp
endif

if CRYPTO
nobase_cloudlessinclude_HEADERS += crypto/block.hpp crypto/stream.hpp crypto/hash.hpp \
								   crypto/random.hpp crypto/dh_modp.hpp crypto/exchanger.hpp
endif

nobase_nodist_cloudlessinclude_HEADERS = details/platform.hpp

libcloudless_la_SOURCES = details/zeromq/zcontext.cpp details/zeromq/zmessage.cpp \
						  details/zeromq/zsocket.cpp socket.cpp \
						  address.cpp context.cpp element.cpp exceptions.cpp \
						  message.cpp pollitem.cpp poller.cpp \
						  req.cpp rep.cpp dealer.cpp router.cpp push.cpp pull.cpp \
						  pub.cpp sub.cpp pair.cpp

if CRYPTO
libcloudless_la_SOURCES += crypto/dh_modp.cpp
endif

if ZMQ_3_X
libcloudless_la_SOURCES += xsub.cpp xpub.cpp
endif

if ON_MINGW
libcloudless_la_LDFLAGS = -no-undefined -avoid-version -version-info @LTVER@ @LIBCLOUDLESS_EXTRA_LDFLAGS@
else
libcloudless_la_LDFLAGS = -version-info @LTVER@ @LIBCLOUDLESS_EXTRA_LDFLAGS@
endif

libcloudless_la_CXXFLAGS = -I'$(top_srcdir)' -I'$(top_builddir)' @LIBCLOUDLESS_EXTRA_CXXFLAGS@

dist-hook:
	-rm $(distdir)/details/platform.hpp
