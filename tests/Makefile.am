INCLUDES = -I$(top_builddir)
LDADD = $(top_builddir)/cloudless/libcloudless.la

noinst_PROGRAMS = test_messages test_utils test_context test_comm test_pair \
				  test_req_rep test_push_pull test_pub_sub test_dealer_router \
				  test_thread test_edges

if CRYPTO
noinst_PROGRAMS += test_crypto_block test_crypto_stream test_crypto_hash test_crypto_exchanger
endif

if ZMQ_3_X
noinst_PROGRAMS += test_xpub_xsub
endif

test_messages_SOURCES = test_messages.cpp
test_utils_SOURCES = test_utils.cpp
test_context_SOURCES = test_context.cpp
test_comm_SOURCES = test_comm.cpp
test_pair_SOURCES = test_pair.cpp
test_req_rep_SOURCES = test_req_rep.cpp
test_push_pull_SOURCES = test_push_pull.cpp
test_pub_sub_SOURCES = test_pub_sub.cpp
test_dealer_router_SOURCES = test_dealer_router.cpp
test_thread_SOURCES = test_thread.cpp
test_edges_SOURCES = test_edges.cpp

if CRYPTO
test_crypto_block_SOURCES = test_crypto_block.cpp
test_crypto_stream_SOURCES = test_crypto_stream.cpp
test_crypto_hash_SOURCES = test_crypto_hash.cpp
test_crypto_exchanger_SOURCES = test_crypto_exchanger.cpp
endif

if ZMQ_3_X
test_xpub_xsub_SOURCES = test_xpub_xsub.cpp
endif

TESTS = $(noinst_PROGRAMS)

test: check
