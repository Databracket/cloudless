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

#ifndef __CLOUDLESS_MESSAGE_HPP
#define __CLOUDLESS_MESSAGE_HPP

#include <string>
#include <deque>

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/element.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT message
    {
        message() {}
        message(const std::string& data_);
        message(const void* p_, size_t size_);
        message(const element& elem_);

        element tail();
        message& push_tail(const element& elem_);
        message& push_tail(const std::string& data_);
        message& push_tail(const void* p_, size_t size_);
        element pop_tail();

        element head();
        message& push_head(const element& elem_);
        message& push_head(const std::string& data_);
        message& push_head(const void* p_, size_t size_);
        element pop_head();

        size_t size() const throw();
        void clear() throw();

        element operator [](size_t idx_) const;
        std::deque<element>* operator ->();

    private:
        element _M_element;
        std::deque<element> _M_elements;
    };

} // namespace cloudless

#endif // __CLOUDLESS_MESSAGE_HPP
