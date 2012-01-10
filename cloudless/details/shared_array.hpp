/*
    Copyright (c) 2011 Databracket, LLC.
    Copyright (c) 2011 Other contributors as noted in the AUTHORS file

    This file is part of Cloudless.

    Cloudless is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Cloudless is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CLOUDLESS_DETAILS_SHARED_ARRAY_HPP
#define __CLOUDLESS_DETAILS_SHARED_ARRAY_HPP

#include <cloudless/details/shared_ptr.hpp>

namespace cloudless
{

namespace details
{

    template <typename T>
    struct shared_array_deleter
    {
        void operator ()(const T* ptr_)
        { delete[] ptr_; }
    };

    template <typename T>
    struct shared_array : shared_ptr<T>
    {
        explicit shared_array(T* ptr_) :
            shared_ptr<T>(ptr_, shared_array_deleter<T>()) {}
    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_SHARED_ARRAY_HPP
