/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket LLC.
 *
 * This file is part of Cloudless.
 *
 * Cloudless is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cloudless is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * A high level abstraction for 0MQ sockets interface.
*/

#include <cloudless/detail/zeromq/zeromq.hpp>
#include <cloudless/socket.hpp>
#include <cloudless/poller.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    // socket

    socket::socket(context& context, int type) :
        detail::zsocket(context, type)
    {
        _M_ip = detail::shared_ptr<pollitem>(new pollitem(*this));
    }

    socket::socket(detail::shared_ptr<context>& context, int type) :
        detail::zsocket(*context, type)
    {
        _M_ip = detail::shared_ptr<pollitem>(new pollitem(*this));
    }

    socket&
    socket::bind(const std::string& addr)
    {
        detail::zsocket::bind(addr.c_str());

        return *this;
    }

    socket&
    socket::bind(const address& addr)
    {
        detail::zsocket::bind((const char*) addr);

        return *this;
    }

    socket&
    socket::connect(const std::string& addr)
    {
        detail::zsocket::connect(addr.c_str());

        return *this;
    }

    socket&
    socket::connect(const address& addr)
    {
        detail::zsocket::connect((const char*) addr);

        return *this;
    }

    bool
    socket::send(message& msg, bool block)
    {
        if (msg->empty())
            raise(message_empty);

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        if (block && !can_send()) {
            poller p;

            p.add("__send_socket",
                    poll_item().register_event(poll_events::OUT_EVENT));

            if (!p.poll(send_timeout()) || !p["__send_socket"].out())
                return false;
        }
#endif

        while (msg.size()) {
            if (!sendmsg(*msg->front(),
                        (msg->size() > 1 ? ZMQ_SNDMORE : 0)
                        | (block == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msg->pop_front();
        }

        return true;
    }

    bool
    socket::recv(message& msg, bool block)
    {
        if (msg.size())
            msg->clear();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        if (block && !can_recv()) {
            poller p;

            p.add("__recv_socket",
                    poll_item().register_event(poll_events::IN_EVENT));

            if (!p.poll(recv_timeout()) || !p["__recv_socket"].in())
                return false;
        }
#endif

        do {
            element e;

            if (!recvmsg(*e,
                        (block == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msg.push_tail(e);
        } while (recv_more());

        return true;
    }

    pollitem&
    socket::poll_item() throw()
    {
        return *_M_ip;
    }

} // namespace cloudless
