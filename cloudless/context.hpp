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
 * An abstraction around 0MQ context.
*/

#ifndef CLOUDLESS_CONTEXT_HPP
#define CLOUDLESS_CONTEXT_HPP

#include <cloudless/details/export.hpp>
#include <cloudless/details/singleton.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/details/enable_shared_from_this.hpp>
#include <cloudless/details/zeromq/zcontext.hpp>

namespace cloudless
{

    /**
     * A structure to abstract 0MQ context.
     *
     * There must be only one context per process. If two threads belong to
     * two different contexts; which connect to each other through an INPROC
     * address, they will NOT be able to communicate.
     */

    struct LIBCLOUDLESS_EXPORT context : details::zcontext, details::singleton<context>, details::enable_shared_from_this<context>
    {

        /**
         * A constructor that takes the number of threads that should
         * handle recieving and sending messages.
         *
         * @param io_threads the number of threads to handle I/O. Defaults to the number
         * of hardware threads available on the system.
         */
        context(int io_threads = 0);

        details::shared_ptr<context> shared_this() throw();
    };

} // namespace cloudless

#endif // CLOUDLESS_CONTEXT_HPP
