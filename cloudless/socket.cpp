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

#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/socket.hpp>
#include <cloudless/poller.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    // socket

    socket::socket(context& context_, int type_) :
        details::zsocket(context_, type_)
    {
        _M_ip = details::shared_ptr<pollitem>(new pollitem(*this));
    }

    socket&
    socket::bind(const std::string& addr_)
    {
        details::zsocket::bind(addr_.c_str());

        return *this;
    }

    socket&
    socket::bind(const address& addr_)
    {
        details::zsocket::bind((const char*) addr_);

        return *this;
    }

    socket&
    socket::connect(const std::string& addr_)
    {
        details::zsocket::connect(addr_.c_str());

        return *this;
    }

    socket&
    socket::connect(const address& addr_)
    {
        details::zsocket::connect((const char*) addr_);

        return *this;
    }

    bool
    socket::send(message& msg_, bool block_)
    {
        if (msg_->empty())
            throw message_empty();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        if (block_ && !can_send()) {
            poller p;

            p.add_item(poll_item().register_event(poll_events::OUT),
                    "__send_socket");

            if (!p.poll(send_timeout()) || !p["__send_socket"].out())
                return false;
        }
#endif

        while (msg_.size()) {
            if (!sendmsg(*msg_->front(),
                        (msg_->size() > 1 ? ZMQ_SNDMORE : 0)
                        | (block_ == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msg_->pop_front();
        }

        return true;
    }

    bool
    socket::recv(message& msg_, bool block_)
    {
        if (msg_.size())
            msg_->clear();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        if (block_ && !can_recv()) {
            poller p;

            p.add_item(poll_item().register_event(poll_events::IN),
                    "__recv_socket");

            if (!p.poll(recv_timeout()) || !p["__recv_socket"].in())
                return false;
        }
#endif

        do {
            element e;

            if (!recvmsg(*e,
                        (block_ == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msg_.push_tail(e);
        } while (recv_more());

        return true;
    }

    pollitem&
    socket::poll_item() throw()
    {
        return *_M_ip;
    }

} // namespace cloudless
