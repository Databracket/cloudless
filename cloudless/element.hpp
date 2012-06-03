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
 * A helper around the elements 0MQ messages can have.
*/

#ifndef CLOUDLESS_ELEMENT_HPP
#define CLOUDLESS_ELEMENT_HPP

#include <string>
#include <utility>

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/shared_ptr.hpp>
#include <cloudless/detail/zeromq/zmessage.hpp>

namespace cloudless
{

    using namespace std::rel_ops;

    /**
     * A structure that wraps an element inside a the message container.
     */

    struct LIBCLOUDLESS_EXPORT element : detail::shared_ptr<detail::zmessage>
    {

        /**
         * A default constructor that optionally takes a pointer
         * to a 0MQ message.
         *
         * @param p a pointer to a 0MQ message.
         */
        element(detail::zmessage* p = new detail::zmessage);

        /**
         * A constructor that takes a constant reference to a std::string.
         *
         * @param data the data in std::string to be wrapped.
         */
        element(const std::string& data);

        /**
         * A constructor that takes a char array pointer and its size.
         *
         * @param p a pointer to data in a char array.
         * @param size the size of the char array.
         */
        element(const void* p, size_t size);

        /**
         * Equality comparison against a generic type and the underlying
         * zmessage.
         *
         * @tparam T any type that is defined to be compatible with zmessages.
         * @param rhs a constant reference to the other type to be compared with
         * the underlying zmessage.
         * @return true or false.
         */
        template <typename T>
        inline bool operator ==(const T& rhs) const
        {
            return *get() == rhs;
        }

        /**
         * Less-than comparison against a generic type and the underlying
         * zmessage.
         *
         * @tparam T any type that is defined to be compatible with zmessages.
         * @param rhs a constant reference to the other type to be compared with
         * the underlying zmessage.
         * @return true or false.
         */
        template <typename T>
        inline bool operator <(const T& rhs) const
        {
            return *get() < rhs;
        }
    };

} // namespace cloudless

#endif // CLOUDLESS_ELEMENT_HPP
