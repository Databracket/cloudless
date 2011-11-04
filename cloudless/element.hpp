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

#ifndef __CLOUDLESS_ELEMENT_HPP
#define __CLOUDLESS_ELEMENT_HPP

#include <algorithm>
#include <string>

#include <cloudless/details/export.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/details/zeromq/zmessage.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT element : details::shared_ptr<details::zmessage>
    {
        element(details::zmessage* p_ = new details::zmessage);
        element(const std::string& data_);
        element(const void* p_, size_t size_);

        template <typename Iter>
        element(Iter begin, Iter end) :
            details::shared_ptr<details::zmessage>(
                    new details::zmessage(std::count(begin, end)))
        {
            std::copy(begin, end, get()->data);
        }
    };

} // namespace cloudless

#endif // __CLOUDLESS_ELEMENT_HPP
