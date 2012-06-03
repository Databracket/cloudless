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

#include <cloudless/detail/thread.hpp>
#include <cloudless/context.hpp>

namespace cloudless
{

    // context

    context::context(int io_threads) :
        detail::zcontext(io_threads == 0 ? detail::thread::hardware_concurrency() : io_threads)
    {}

    detail::shared_ptr<context>
    context::shared_this() throw()
    {
        return shared_from_this();
    }

} // namespace cloudless
