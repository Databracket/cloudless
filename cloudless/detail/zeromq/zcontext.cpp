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

#include <cassert>

#include <cloudless/detail/zeromq/zeromq.hpp>
#include <cloudless/detail/zeromq/zcontext.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

namespace detail
{

    // zcontext

    zcontext::zcontext(int io_threads)
    {
        int num_threads = io_threads == 0 ? 2 : io_threads;
        _M_ptr = zmq_init(num_threads);

        if (_M_ptr == NULL)
            raise(null_pointer);
    }

    zcontext::~zcontext()
    {
        int rc = zmq_term(_M_ptr);
        assert(rc == 0);
    }

    zcontext::operator void*() const throw()
    {
        return _M_ptr;
    }

} // namespace detail

} // namespace cloudless
