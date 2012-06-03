lib_LTLIBRARIES = libcloudless.la

cloudlessincludedir = $(includedir)/cloudless
nobase_cloudlessinclude_HEADERS = detail/noncopyable.hpp detail/nonconstructive.hpp \
								  detail/export.hpp detail/exception.hpp \
								  detail/singleton.hpp detail/shared_ptr.hpp \
								  detail/shared_array.hpp detail/zeromq/zcontext.hpp \
								  detail/zeromq/zeromq.hpp detail/zeromq/zmessage.hpp \
								  detail/zeromq/zsocket.hpp detail/thread.hpp \
								  detail/enable_shared_from_this.hpp \
								  socket.hpp address.hpp context.hpp element.hpp \
								  exceptions.hpp message.hpp poller.hpp pollitem.hpp \
								  version.hpp req.hpp rep.hpp dealer.hpp router.hpp \
								  push.hpp pull.hpp pub.hpp sub.hpp pair.hpp misc.hpp \
								  edges.hpp device.hpp

if ZMQ_3_X
nobase_cloudlessinclude_HEADERS += xsub.hpp xpub.hpp
endif

if CRYPTO
nobase_cloudlessinclude_HEADERS += crypto/block.hpp crypto/stream.hpp crypto/hash.hpp \
								   crypto/random.hpp crypto/dh_modp.hpp crypto/exchanger.hpp \
								   crypto/cryptopp/eccrypto.h crypto/cryptopp/fhmqv.h
endif

nobase_nodist_cloudlessinclude_HEADERS = detail/platform.hpp

libcloudless_la_SOURCES = detail/zeromq/zcontext.cpp detail/zeromq/zmessage.cpp \
						  detail/zeromq/zsocket.cpp detail/thread.cpp socket.cpp \
						  address.cpp context.cpp element.cpp exceptions.cpp \
						  message.cpp pollitem.cpp poller.cpp \
						  req.cpp rep.cpp dealer.cpp router.cpp push.cpp pull.cpp \
						  pub.cpp sub.cpp pair.cpp misc.cpp edges.cpp device.cpp

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
	-rm $(distdir)/detail/platform.hpp
