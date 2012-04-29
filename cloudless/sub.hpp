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
 * A wrapper to represent 0MQ SUB sockets.
*/

#ifndef __CLOUDLESS_SUB_HPP
#define __CLOUDLESS_SUB_HPP

#include <string>

#include <cloudless/details/export.hpp>
#include <cloudless/context.hpp>
#include <cloudless/socket.hpp>

namespace cloudless
{

    /**
     * A wrapper structure around SUB socket.
     */

    struct LIBCLOUDLESS_EXPORT sub : socket
    {

        /**
         * A constructor that takes a context.
         *
         * @param context a context.
         */
        sub(context& context);

        /**
         * An override of the send() function in the socket interface
         * to disable it as SUB sockets does not send any messages.
         */
        virtual bool send(message& msg, bool block = true);
    };

} // namespace cloudless

#endif // __CLOUDLESS_SUB_HPP
