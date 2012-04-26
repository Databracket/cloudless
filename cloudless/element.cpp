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

#include <cstring>

#include <cloudless/element.hpp>

namespace cloudless
{

    // element

    element::element(details::zmessage* p_) :
        details::shared_ptr<details::zmessage>(p_)
    {}

    element::element(const std::string& data_) :
        details::shared_ptr<details::zmessage>(new element_type(data_.size()))
    {
        memcpy(get()->data(), data_.data(), data_.size());
    }

    element::element(const void* p_, size_t size_) :
        details::shared_ptr<details::zmessage>(new element_type(size_))
    {
        memcpy(get()->data(), p_, size_);
    }

} // namespace cloudless
