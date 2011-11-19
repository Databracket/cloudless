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

#ifndef __CLOUDLESS_SOCKET_HPP
#define __CLOUDLESS_SOCKET_HPP

#include <string>

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zsocket.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/address.hpp>
#include <cloudless/pollitem.hpp>

namespace cloudless
{

namespace socket_type
{

    static const int PAIR = ZMQ_PAIR;
    static const int PUB = ZMQ_PUB;
    static const int SUB = ZMQ_SUB;
    static const int REQ = ZMQ_REQ;
    static const int REP = ZMQ_REP;
    static const int XREQ = ZMQ_XREQ;
    static const int XREP = ZMQ_XREP;
    static const int PULL = ZMQ_PULL;
    static const int PUSH = ZMQ_PUSH;
    static const int XPUB = ZMQ_XPUB;
    static const int XSUB = ZMQ_XSUB;

    // Backwards compatibility
    static const int DEALER = ZMQ_XREQ;
    static const int ROUTER = ZMQ_XREP;

} // namespace socket_type

    struct LIBCLOUDLESS_EXPORT socket : details::zsocket
    {
        socket(context& context_, int type_);

        socket& bind(const std::string& addr_);
        socket& bind(const address& addr_);

        socket& connect(const std::string& addr_);
        socket& connect(const address& addr_);

        virtual bool send(message& msg_, bool block_ = true);
        virtual bool recv(message& msg_, bool block_ = true);

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

        socket& affinity(uint64_t affinity_);
        socket& identity(const std::string& identity_);
        socket& rate(int rate_);
        socket& recovery_ivl(int ivl_);
        socket& send_buffer(int size_);
        socket& recv_buffer(int size_);
        socket& linger(int linger_);
        socket& reconnect_ivl(int ivl_, int max_ = 0);
        socket& backlog(int backlog_);
        socket& max_msg_size(int64_t max_size_);
        socket& hwm(int hwm_);
        socket& send_hwm(int hwm_);
        socket& recv_hwm(int hwm_);
        socket& multicast_hops(int hops_);
        socket& send_timeout(int timeout_);
        socket& recv_timeout(int timeout_);
        socket& ipv4_only(bool ipv4_only_);

        pollitem& poll_item() throw();

    private:
        int _M_get_events() const;

    private:
        int _M_recvtimeo;
        int _M_sendtimeo;
        details::shared_ptr<pollitem> _M_ip;
    };

} // namespace cloudless

#endif // __CLOUDLESS_SOCKET_HPP
