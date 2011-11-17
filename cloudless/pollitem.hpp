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

#ifndef __CLOUDLESS_POLLITEM_HPP
#define __CLOUDLESS_POLLITEM_HPP

#include <utility>

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/details/zeromq/zsocket.hpp>

namespace cloudless
{

namespace poll_events
{

    static const short IN = ZMQ_POLLIN;
    static const short OUT = ZMQ_POLLOUT;
    static const short ERROR = ZMQ_POLLERR;

} // namespace poll_events

    using namespace std::rel_ops;

    struct LIBCLOUDLESS_EXPORT pollitem : private zmq_pollitem_t
    {
        pollitem() throw();
        pollitem(details::zsocket& socket_, short events_ = 0,
                short revents_ = 0) throw();
        pollitem(socket_t fd_, short events_ = 0, short revents_ = 0) throw();

        pollitem& register_event(short event_) throw();
        pollitem& unregister_event(short event_) throw();

        bool in() const throw();
        bool out() const throw();
        bool error() const throw();

        bool operator ==(const pollitem& rhs) const;
    };

} // namespace cloudless

#endif // __CLOUDLESS_POLLITEM_HPP
