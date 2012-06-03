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
 * A wrapper to represent 0MQ PUSH sockets.
*/

#ifndef CLOUDLESS_PUSH_HPP
#define CLOUDLESS_PUSH_HPP

#include <cloudless/detail/export.hpp>
#include <cloudless/context.hpp>
#include <cloudless/socket.hpp>

namespace cloudless
{

    /**
     * A wrapper structure around PUSH socket.
     */

    struct LIBCLOUDLESS_EXPORT push : socket
    {

        /**
         * A constructor that takes a context.
         *
         * @param context a context.
         */
        push(context& context);

        /**
         * An override of the recv() function in the socket interface
         * to disable it as PUSH sockets does not receive any messages.
         */
        virtual bool recv(message& msg, bool block = true);
    };

} // namespace cloudless

#endif // CLOUDLESS_PUSH_HPP
