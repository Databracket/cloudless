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
 * A high level abstraction for 0MQ sockets interface.
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

    /**
     * A high level socket abstraction that wraps 0MQ's
     * low level interface.
     */

    struct LIBCLOUDLESS_EXPORT socket : details::zsocket
    {

        /**
         * A constructor that takes a context and a socket type.
         *
         * @param context_ a context.
         * @param type_ a socket type.
         */
        socket(context& context_, int type_);

        /**
         * Bind this socket to a specific address given via
         * a std::string.
         *
         * @param addr_ a socket address string.
         */
        socket& bind(const std::string& addr_);

        /**
         * Bind this socket to a specific address given via
         * the address structure.
         *
         * @param addr_ a socket address structure.
         */
        socket& bind(const address& addr_);

        /**
         * Connect this socket to a specific address given via
         * a std::string.
         *
         * @param addr_ a socket address string.
         */
        socket& connect(const std::string& addr_);

        /**
         * Connect this socket to a specific address given via
         * the address structure.
         *
         * @param addr_ a socket address structure.
         */
        socket& connect(const address& addr_);

        /**
         * Send a message through this socket.
         *
         * @param msg_ a reference to an instance of a message.
         * @param block_ whether to send this message synchronously or asynchronously.
         * @return whether the message was sent successfully.
         */
        virtual bool send(message& msg_, bool block_ = true);

        /**
         * Receive a message through this socket.
         * Note that if a reference to a message with elements were to be passed,
         * the message container will be cleared of all elements prior to filling
         * it with the message to be received.
         *
         * @param msg_ a reference to an instance of a message.
         * @param block_ whether to receive this message synchronously or asynchronously.
         * @return whether the message was received successfully.
         */
        virtual bool recv(message& msg_, bool block_ = true);

        /**
         * Get a pollitem that represents this socket.
         *
         * @return a pollitem of this socket.
         */
        pollitem& poll_item() throw();

    private:
        details::shared_ptr<pollitem> _M_ip;
    };

} // namespace cloudless

#endif // __CLOUDLESS_SOCKET_HPP
