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

#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/details/shared_array.hpp>
#include <cloudless/exceptions.hpp>
#include <cloudless/poller.hpp>

namespace cloudless
{

    // poller

    void
    poller::add_item(pollitem& item_, const std::string& name_) throw()
    {
        _M_items[name_] = item_;
    }

    bool
    poller::poll(long timeout_) const
    {
        if (_M_items.size() < 1)
            throw poll_empty();

        details::shared_array<pollitem> items(new pollitem[_M_items.size()]);

        std::map<std::string, pollitem>::const_iterator it = _M_items.begin();

        for (size_t i = 0; i < _M_items.size(); ++i)
            items.get()[i] = it++->second;

        int rc = zmq_poll((zmq_pollitem_t*)items.get(), _M_items.size(), timeout_ * ZMQ_POLL_MSEC);

        if (rc == -1)
            throw zexception();

        return (rc > 0);
    }

    const pollitem&
    poller::operator [](const std::string& rhs) const
    {
        poll_items::const_iterator it = _M_items.find(rhs);

        if (it == _M_items.end())
            throw poll_not_found();

        return it->second;
    }

} // namespace cloudless
