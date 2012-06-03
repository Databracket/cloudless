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
 * A polling mechanism based on 0MQ polling abstraction.
*/

#include <cloudless/detail/zeromq/zeromq.hpp>
#include <cloudless/detail/singleton.hpp>
#include <cloudless/exceptions.hpp>
#include <cloudless/poller.hpp>

namespace cloudless
{

    // poller

    poller&
    poller::add(const std::string& name, const pollitem& item)
    {
        _M_items.push_back(item);
        _M_indexes[name] = _M_ctr++;

        return *this;
    }

    bool
    poller::poll(long timeout) const
    {
        if (_M_items.empty())
            raise(poll_empty);

        // Accessing a std::vector like that is safe, as its memory is guaranteed
        // to be contiguous.
        int rc = zmq_poll((zmq_pollitem_t*)&_M_items[0], _M_items.size(),
                timeout < 0 ? timeout : timeout * ZMQ_POLL_MSEC);

        // 0MQ error occurred
        if (rc == -1)
            raise(zexception);

        // rc is the number of pollitems that had an event triggered.
        // In the current form of poller that piece of information is irrelevant.
        // So we instead just return whether there was any events fired on any pollitem.
        return (rc > 0);
    }

    const std::string&
    poller::get_triggered() const
    {
        items_indexes::const_iterator it;

        for (it = _M_indexes.begin(); it != _M_indexes.end(); ++it)
        {
            if (_M_items[it->second].in()
                    || _M_items[it->second].out()
                    || _M_items[it->second].error())
                return it->first;
        }

        // Return empty string
        return *detail::singleton<std::string>::instance();
    }

    const pollitem&
    poller::operator [](const std::string& rhs) const
    {
        items_indexes::const_iterator it = _M_indexes.find(rhs);

        if (it == _M_indexes.end())
            raise(poll_not_found);

        return _M_items[it->second];
    }

} // namespace cloudless
