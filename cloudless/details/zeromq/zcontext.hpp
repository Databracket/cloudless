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
 * A wrapper around 0MQ low level context.
*/

#ifndef CLOUDLESS_DETAILS_ZEROMQ_ZCONTEXT_HPP
#define CLOUDLESS_DETAILS_ZEROMQ_ZCONTEXT_HPP

#include <cloudless/details/export.hpp>
#include <cloudless/details/noncopyable.hpp>

namespace cloudless
{

namespace details
{

    /**
     * A wrapper around 0MQ low level context.
     */

    struct LIBCLOUDLESS_EXPORT zcontext : noncopyable
    {

        /**
         * A constrcutor that takes the number of I/O threads
         * to handle sending and receiving messages.
         *
         * @param io_threads the number of threads to handle I/O.
         */
        zcontext(int io_threads);

        /**
         * A destructor to free the allocated context by 0MQ.
         */
        virtual ~zcontext();

        /**
         * Expose internal 0MQ context by casting this structure to a void pointer.
         */
        operator void*() const throw();

    private:
        void* _M_ptr;
    };

} // namespace details

} // namespace cloudless

#endif // CLOUDLESS_DETAILS_ZEROMQ_ZCONTEXT_HPP
