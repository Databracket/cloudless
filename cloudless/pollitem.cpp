/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket, LLC.
 * Copyright (c) 2012 Other contributors as noted in the AUTHORS file
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
 * A wrapper around 0MQ sockets or system sockets to represent a polling item.
*/

#include <cloudless/pollitem.hpp>

namespace cloudless
{

    // pollitem

    pollitem::pollitem() throw()
    {
        ((zmq_pollitem_t*)this)->socket = 0;
        ((zmq_pollitem_t*)this)->fd = 0;
        ((zmq_pollitem_t*)this)->events = 0;
        ((zmq_pollitem_t*)this)->revents = 0;
    }

    pollitem::pollitem(socket_t fd_, short events_, short revents_) throw()
    {
        ((zmq_pollitem_t*)this)->socket = 0;
        ((zmq_pollitem_t*)this)->fd = fd_;
        ((zmq_pollitem_t*)this)->events = events_;
        ((zmq_pollitem_t*)this)->revents = revents_;
    }

    pollitem::pollitem(details::zsocket& socket_, short events_,
            short revents_) throw()
    {
        ((zmq_pollitem_t*)this)->socket = socket_;
        ((zmq_pollitem_t*)this)->fd = 0;
        ((zmq_pollitem_t*)this)->events = events_;
        ((zmq_pollitem_t*)this)->revents = revents_;
    }

    pollitem&
    pollitem::register_event(short event_) throw()
    {
        events |= event_;

        return *this;
    }

    pollitem&
    pollitem::unregister_event(short event_) throw()
    {
        events ^= event_;

        return *this;
    }

    bool
    pollitem::in() const throw()
    {
        return (revents & poll_events::IN);
    }

    bool
    pollitem::out() const throw()
    {
        return (revents & poll_events::OUT);
    }

    bool
    pollitem::error() const throw()
    {
        return (revents & poll_events::ERROR);
    }

    bool
    pollitem::operator ==(const pollitem& rhs) const
    {
        return ((zmq_pollitem_t*)this)->socket == ((zmq_pollitem_t*)&rhs)->socket
            || ((zmq_pollitem_t*)this)->fd == ((zmq_pollitem_t*)&rhs)->fd;
    }

} // namespace cloudless
