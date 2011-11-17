INCLUDES = -I$(top_builddir)
LDADD = $(top_builddir)/cloudless/libcloudless.la

noinst_PROGRAMS = test_messages test_utils test_context test_comm

test_messages_SOURCES = test_messages.cpp
test_utils_SOURCES = test_utils.cpp
test_context_SOURCES = test_context.cpp
test_comm_SOURCES = test_comm.cpp

TESTS = $(noinst_PROGRAMS)

test: check
