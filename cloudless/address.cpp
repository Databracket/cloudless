/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket LLC.
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
 * An abstraction of 0MQ socket addresses.
*/

#include <sstream>

#include <cloudless/address.hpp>

namespace cloudless
{

    address::address(const std::string& protocol, const std::string& path,
            short port) :
        _M_path(path), _M_protocol(protocol), _M_port(port)
    {
        std::ostringstream oss;

        oss << _M_protocol << "://" << _M_path;

        if (port)
            oss << ":" << _M_port;

        _M_addr = oss.str();
    }

    address::operator const std::string&() const
    {
        return _M_addr;
    }

    address::operator const char*() const
    {
        return _M_addr.c_str();
    }

    bool
    address::operator <(const address& rhs) const
    {
        return _M_addr < rhs._M_addr;
    }

} // namespace cloudless
