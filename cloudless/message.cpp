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

#include <cloudless/details/zeromq/zmessage.hpp>
#include <cloudless/message.hpp>

namespace cloudless
{

    // message

    message::message(const std::string& data_)
    {
        push_tail(data_);
    }

    message::message(const void* p_, size_t size_)
    {
        push_tail(p_, size_);
    }

    message::message(const element& elem_)
    {
        push_tail(elem_);
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
    message::push_tail(const element& elem_)
    {
        _M_elements.push_back(elem_);

        return *this;
    }

    message&
    message::push_tail(const std::string& data_)
    {
        return push_tail(element(data_));
    }

    message&
    message::push_tail(const void* p_, size_t size_)
    {
        return push_tail(element(p_, size_));
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
    message::push_head(const element& elem_)
    {
        _M_elements.push_front(elem_);

        return *this;
    }

    message&
    message::push_head(const std::string& data_)
    {
        return push_head(element(data_));
    }

    message&
    message::push_head(const void* p_, size_t size_)
    {
        return push_head(element(p_, size_));
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
    message::operator [](size_t idx_) const
    {
        return _M_elements.at(idx_);
    }

} // namespace cloudless
