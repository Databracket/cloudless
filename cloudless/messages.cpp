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
#include <cloudless/messages.hpp>

namespace cloudless
{

    // messages

    messages::messages(const std::string& data_)
    {
        push_tail(data_);
    }

    messages::messages(const void* p_, size_t size_)
    {
        push_tail(p_, size_);
    }

    messages::messages(const element& elem_)
    {
        push_tail(elem_);
    }

    element
    messages::tail()
    {
        if (!_M_msgs.empty())
            return _M_msgs.back();

        if (_M_element.get() == NULL)
            _M_element.reset(new details::zmessage);

        return _M_element;
    }

    messages&
    messages::push_tail(const element& elem_)
    {
        _M_msgs.push_back(elem_);

        return *this;
    }

    messages&
    messages::push_tail(const std::string& data_)
    {
        return push_tail(element(data_));
    }

    messages&
    messages::push_tail(const void* p_, size_t size_)
    {
        return push_tail(element(p_, size_));
    }

    element
    messages::pop_tail()
    {
        element ret = _M_msgs.back();

        _M_msgs.pop_back();

        return ret;
    }

    element
    messages::head()
    {
        if (!_M_msgs.empty())
            return _M_msgs.front();

        if (_M_element.get() == NULL)
            _M_element.reset(new details::zmessage);

        return _M_element;
    }

    messages&
    messages::push_head(const element& elem_)
    {
        _M_msgs.push_front(elem_);

        return *this;
    }

    messages&
    messages::push_head(const std::string& data_)
    {
        return push_head(element(data_));
    }

    messages&
    messages::push_head(const void* p_, size_t size_)
    {
        return push_head(element(p_, size_));
    }

    element
    messages::pop_head()
    {
        if (!_M_msgs.empty() && !_M_msgs.front()->size())
            _M_msgs.pop_front();

        element ret = _M_msgs.front();

        _M_msgs.pop_front();

        return ret;
    }

    size_t
    messages::size() const throw()
    {
        return _M_msgs.size();
    }

    void
    messages::clear() throw()
    {
        _M_msgs.clear();
    }

    std::deque<element>*
    messages::operator ->()
    {
        return &_M_msgs;
    }

    element
    messages::operator [](size_t idx_) const
    {
        return _M_msgs.at(idx_);
    }

} // namespace cloudless
