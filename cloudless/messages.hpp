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

#ifndef __CLOUDLESS_MESSAGES_HPP
#define __CLOUDLESS_MESSAGES_HPP

#include <string>
#include <deque>

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/element.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT messages
    {
        messages() {}
        messages(const std::string& data_);
        messages(const void* p_, size_t size_);
        messages(const element& elem_);

        template <typename Iter>
        messages(Iter begin, Iter end)
        {
            push_tail(begin, end);
        }

        element tail();
        messages& push_tail(const element& elem_);
        messages& push_tail(const std::string& data_);
        messages& push_tail(const void* p_, size_t size_);
        element pop_tail();

        template <typename Iter>
        messages& push_tail(Iter begin, Iter end)
        {
            return push_tail(element(begin, end));
        }

        element head();
        messages& push_head(const element& elem_);
        messages& push_head(const std::string& data_);
        messages& push_head(const void* p_, size_t size_);
        element pop_head();

        template <typename Iter>
        messages& push_head(Iter begin, Iter end)
        {
            return push_head(element(begin, end));
        }

        size_t size() const;

        element operator [](size_t idx_) const;
        std::deque<element>* operator ->();

    private:
        element _M_element;
        std::deque<element> _M_msgs;
    };

} // namespace cloudless

#endif // __CLOUDLESS_MESSAGES_HPP
