/*
    Copyright (c) 2011 Databracket, LLC.
    Copyright (c) 2011 Other contributors as noted in the AUTHORS file

    This file is part of Cloudless.

    Cloudless is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Cloudless is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_HPP
#define __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_HPP

#include <string>

#include <cloudless/details/export.hpp>
#include <cloudless/details/noncopyable.hpp>
#include <cloudless/details/zeromq/zcontext.hpp>
#include <cloudless/details/zeromq/zmessage.hpp>

namespace cloudless
{

namespace socket_type
{

    static const int PAIR = ZMQ_PAIR;
    static const int PUB = ZMQ_PUB;
    static const int SUB = ZMQ_SUB;
    static const int REQ = ZMQ_REQ;
    static const int REP = ZMQ_REP;
    static const int DEALER = ZMQ_DEALER;
    static const int ROUTER = ZMQ_ROUTER;
    static const int PULL = ZMQ_PULL;
    static const int PUSH = ZMQ_PUSH;
    static const int XPUB = ZMQ_XPUB;
    static const int XSUB = ZMQ_XSUB;

    // Backwards compatibility
    static const int XREQ = DEALER;
    static const int XREP = ROUTER;

} // namespace socket_type

namespace details
{

    struct LIBCLOUDLESS_EXPORT zsocket : noncopyable
    {
        zsocket(zcontext& context_, int type_);
        virtual ~zsocket();

        void close();

        void setsockopt(int option_, const void* optval_, size_t optvallen_);
        void getsockopt(int option_, void* optval_, size_t* optvallen_) const;

        void bind(const char* addr_);
        void connect(const char* addr_);

        bool sendmsg(zmessage& msg_, int flags_ = 0);
        bool recvmsg(zmessage& msg_, int flags_ = 0);

        uint64_t affinity() const;
        std::string identity() const;
        int rate() const;
        int recovery_ivl() const;
        int send_buffer() const;
        int recv_buffer() const;
        bool recv_more() const;
        socket_t fd() const;
        bool can_send() const;
        bool can_recv() const;
        int type() const;
        int linger() const;
        int reconnect_ivl() const;
        int reconnect_ivl_max() const;
        int backlog() const;
        int64_t max_msg_size() const;
        int send_hwm() const;
        int recv_hwm() const;
        int multicast_hops() const;
        int send_timeout() const;
        int recv_timeout() const;
        bool ipv4_only() const;

        zsocket& affinity(uint64_t affinity_);
        zsocket& identity(const std::string& identity_);
        zsocket& rate(int rate_);
        zsocket& recovery_ivl(int ivl_);
        zsocket& send_buffer(int size_);
        zsocket& recv_buffer(int size_);
        zsocket& linger(int linger_);
        zsocket& reconnect_ivl(int ivl_, int max_ = 0);
        zsocket& backlog(int backlog_);
        zsocket& max_msg_size(int64_t max_size_);
        zsocket& hwm(int hwm_);
        zsocket& send_hwm(int hwm_);
        zsocket& recv_hwm(int hwm_);
        zsocket& multicast_hops(int hops_);
        zsocket& send_timeout(int timeout_);
        zsocket& recv_timeout(int timeout_);
        zsocket& ipv4_only(bool ipv4_only_);
        zsocket& subscribe(const std::string& topic_);
        zsocket& unsubscribe(const std::string& topic_);

        operator void*() const throw();

    private:
        int _M_get_events() const;

    private:
        void* _M_ptr;
        int _M_recvtimeo;
        int _M_sendtimeo;
    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_HPP
