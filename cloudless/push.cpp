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
 * A wrapper to represent 0MQ PUSH sockets.
*/

#include <cloudless/push.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    // push

    push::push() :
        socket(socket_type::PUSH)
    {}

    push::push(context& context) :
        socket(context, socket_type::PUSH)
    {}

    push::push(detail::shared_ptr<context> context) :
        socket(context, socket_type::PUSH)
    {}

    bool
    push::recv(message& msg, bool block)
    {
        raise(feature_not_supported);
    }

} // namespace cloudless
