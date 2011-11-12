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
        details::zsocket(context_, type_), _M_recvtimeo(-1), _M_sendtimeo(-1)
    {
        _M_ip = details::shared_ptr<pollitem>(new pollitem(*this));
    }

    void
    socket::bind(const std::string& addr_)
    {
        bind(addr_.c_str());
    }

    void
    socket::bind(const address& addr_)
    {
        bind((const char*) addr_);
    }

    void
    socket::connect(const std::string& addr_)
    {
        connect(addr_.c_str());
    }

    void
    socket::connect(const address& addr_)
    {
        connect((const char*) addr_);
    }

    bool
    socket::send(messages& msgs_, bool block_)
    {
        if (msgs_->empty())
            throw message_empty();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        poller p;
        pollitem& pi = poll_item();

        pi.register_event(poll_events::OUT);

        p.add_item(pi, "__send_socket");

        if (!p.poll(block_ == true ? _M_sendtimeo : 0) || !pi.out())
            return false;
#endif

        while (msgs_.size()) {
            if (!sendmsg(*msgs_->front(),
                        (msgs_->size() > 1 ? ZMQ_SNDMORE : 0)
                        | (block_ == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msgs_->pop_front();
        }

        return true;
    }

    bool
    socket::recv(messages& msgs_, bool block_)
    {
#if ZMQ_VERSION_MAJOR == 2
        int64_t more;
#elif ZMQ_VERSION_MAJOR == 3
        int more;
#endif
        size_t more_size = sizeof(more);

        if (msgs_.size())
            msgs_->clear();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        poller p;
        pollitem& pi = poll_item();

        pi.register_event(poll_events::IN);

        p.add_item(pi, "__recv_socket");

        if (!p.poll(block_ == true ? _M_recvtimeo : 0) || !pi.in())
            return false;
#endif

        do {
            element e;

            if (!recvmsg(*e,
                        (block_ == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msgs_.push_tail(e);

            getsockopt(ZMQ_RCVMORE, &more, &more_size);
        } while (more);

        return true;
    }

    void
    socket::set_send_timeout(int timeout_)
    {
        _M_sendtimeo = timeout_;

#if ZMQ_VERSION_MAJOR == 3
        setsockopt(ZMQ_SNDTIMEO, &_M_sendtimeo, sizeof(_M_sendtimeo));
#endif
    }

    void
    socket::set_recv_timeout(int timeout_)
    {
        _M_recvtimeo = timeout_;

#if ZMQ_VERSION_MAJOR == 3
        setsockopt(ZMQ_RCVTIMEO, &_M_recvtimeo, sizeof(_M_recvtimeo));
#endif
    }

    pollitem&
    socket::poll_item() throw()
    {
        return *_M_ip;
    }

} // namespace cloudless
