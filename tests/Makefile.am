INCLUDES = -I$(top_builddir)
LDADD = $(top_builddir)/cloudless/libcloudless.la

noinst_PROGRAMS = test_messages test_utils test_context test_comm test_pair test_req_rep test_push_pull test_pub_sub

test_messages_SOURCES = test_messages.cpp
test_utils_SOURCES = test_utils.cpp
test_context_SOURCES = test_context.cpp
test_comm_SOURCES = test_comm.cpp
test_pair_SOURCES = test_pair.cpp
test_req_rep_SOURCES = test_req_rep.cpp
test_push_pull_SOURCES = test_push_pull.cpp
test_pub_sub_SOURCES = test_pub_sub.cpp

TESTS = $(noinst_PROGRAMS)

test: check
