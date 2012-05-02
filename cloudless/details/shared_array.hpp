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
 * A shared_array implementation for heap-allocating exception-safe arrays.
*/

#ifndef CLOUDLESS_DETAILS_SHARED_ARRAY_HPP
#define CLOUDLESS_DETAILS_SHARED_ARRAY_HPP

#include <cloudless/details/shared_ptr.hpp>

namespace cloudless
{

namespace details
{

    template <typename T>
    struct shared_array_deleter
    {
        void operator ()(const T* ptr)
        { delete[] ptr; }
    };

    /**
     * An implementation for heap-allocating exception-safe arrays.
     *
     * @tparam T type of array.
     */

    template <typename T>
    struct shared_array : shared_ptr<T>
    {

        /**
         * A constructor that takes a pointer of T.
         *
         * @param ptr a pointer from the expression (new T[size]).
         */
        explicit shared_array(T* ptr) :
            shared_ptr<T>(ptr, shared_array_deleter<T>()) {}
    };

} // namespace details

} // namespace cloudless

#endif // CLOUDLESS_DETAILS_SHARED_ARRAY_HPP
