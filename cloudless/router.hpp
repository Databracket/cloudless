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
 * A wrapper to represent 0MQ ROUTER sockets.
*/

#ifndef CLOUDLESS_ROUTER_HPP
#define CLOUDLESS_ROUTER_HPP

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/shared_ptr.hpp>
#include <cloudless/context.hpp>
#include <cloudless/socket.hpp>

namespace cloudless
{

    /**
     * A wrapper structure around ROUTER socket.
     */

    struct LIBCLOUDLESS_EXPORT router : socket
    {

        /**
         * Default constructor. Uses the global context.
         */
        router();

        /**
         * A constructor that takes a context.
         *
         * @param context a context.
         */
        router(context& context);

        /**
         * A constructor that takes a context.
         *
         * @param context a shared pointer of a context.
         */
        router(detail::shared_ptr<context> context);
    };

} // namespace cloudless

#endif // CLOUDLESS_ROUTER_HPP
