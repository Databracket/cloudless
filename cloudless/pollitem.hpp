/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket LLC.
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

    static const short IN = ZMQ_POLLIN; // recieved a message.
    static const short OUT = ZMQ_POLLOUT; // a message is ready to be sent.
    static const short ERROR = ZMQ_POLLERR; // an error occurred (only applicable to system sockets).

} // namespace poll_events

    using namespace std::rel_ops;

    /**
     * Pollitem is a wrapper around 0MQ pollitem. It provides facilities
     * to make polling over a number of pollitems efficient and easier.
     */

    struct LIBCLOUDLESS_EXPORT pollitem : private zmq_pollitem_t
    {
        /**
         * A default constructor.
         */
        pollitem() throw();

        /**
         * A constructor that takes a 0MQ socket.
         *
         * @param socket a 0MQ socket.
         * @param events the events that poller should be monitoring. (e.g., IN | OUT)
         */
        pollitem(details::zsocket& socket, short events = 0) throw();

        /**
         * A constructor that takes a system socket.
         *
         * @param fd a system's socket file descriptor.
         * @param events the events that polller should be monitoring. (e.g., IN | ERROR)
         */
        pollitem(socket_t fd, short events = 0) throw();

        /**
         * Register an event to be monitored by poller.
         *
         * @param event an event. (e.g., poll_events::IN)
         */
        pollitem& register_event(short event) throw();

        /**
         * Unregister an event.
         *
         * @param event an event. (e.g., poll_events::OUT)
         */
        pollitem& unregister_event(short event) throw();

        /**
         * Check whether poll_events::IN was triggered.
         *
         * @return true or false.
         */
        bool in() const throw();

        /**
         * Check whether poll_events::OUT was triggered.
         *
         * @return true or false.
         */
        bool out() const throw();

        /**
         * Check whether poll_events::ERROR was triggered.
         *
         * @return true or false.
         */
        bool error() const throw();

        bool operator ==(const pollitem& rhs) const;
    };

} // namespace cloudless

#endif // __CLOUDLESS_POLLITEM_HPP
