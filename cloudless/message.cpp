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
 * An abstraction of 0MQ messages.
*/

#include <cloudless/details/zeromq/zmessage.hpp>
#include <cloudless/message.hpp>

namespace cloudless
{

    // message

    message::message(const std::string& data)
    {
        push_tail(data);
    }

    message::message(const void* p, size_t size)
    {
        push_tail(p, size);
    }

    message::message(const element& elem)
    {
        push_tail(elem);
    }

    element
    message::tail()
    {
        if (!_M_elements.empty())
            return _M_elements.back();

        if (_M_element.get() == NULL)
            _M_element.reset(new details::zmessage);

        return _M_element;
    }

    message&
    message::push_tail(const element& elem)
    {
        _M_elements.push_back(elem);

        return *this;
    }

    message&
    message::push_tail(const std::string& data)
    {
        return push_tail(element(data));
    }

    message&
    message::push_tail(const void* p, size_t size)
    {
        return push_tail(element(p, size));
    }

    element
    message::pop_tail()
    {
        element ret = _M_elements.back();

        _M_elements.pop_back();

        return ret;
    }

    element
    message::head()
    {
        if (!_M_elements.empty())
            return _M_elements.front();

        if (_M_element.get() == NULL)
            _M_element.reset(new details::zmessage);

        return _M_element;
    }

    message&
    message::push_head(const element& elem)
    {
        _M_elements.push_front(elem);

        return *this;
    }

    message&
    message::push_head(const std::string& data)
    {
        return push_head(element(data));
    }

    message&
    message::push_head(const void* p, size_t size)
    {
        return push_head(element(p, size));
    }

    element
    message::pop_head()
    {
        if (!_M_elements.empty() && !_M_elements.front()->size())
            _M_elements.pop_front();

        element ret = _M_elements.front();

        _M_elements.pop_front();

        return ret;
    }

    size_t
    message::size() const throw()
    {
        return _M_elements.size();
    }

    void
    message::clear() throw()
    {
        _M_elements.clear();
    }

    std::deque<element>*
    message::operator ->()
    {
        return &_M_elements;
    }

    element
    message::operator [](size_t idx) const
    {
        return _M_elements.at(idx);
    }

} // namespace cloudless
