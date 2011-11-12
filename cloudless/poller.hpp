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

#ifndef __CLOUDLESS_POLLER_HPP
#define __CLOUDLESS_POLLER_HPP

#include <string>
#include <map>

#include <cloudless/details/noncopyable.hpp>
#include <cloudless/details/export.hpp>
#include <cloudless/pollitem.hpp>

namespace cloudless
{

    class LIBCLOUDLESS_EXPORT poller : details::noncopyable
    {
    public:
        void add_item(pollitem& item_, const std::string& name_) throw();
        bool poll(long timeout_ = 300) const;

        const pollitem& operator [](const std::string& rhs) const;

    private:
        typedef std::map<std::string, pollitem> poll_items;
        poll_items _M_items;
    };

} // namespace cloudless

#endif // __CLOUDLESS_POLLER_HPP
