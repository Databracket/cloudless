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

#ifndef __CLOUDLESS_ADDRESS_HPP
#define __CLOUDLESS_ADDRESS_HPP

#include <string>

#include <cloudless/details/export.hpp>

namespace cloudless
{

namespace protocol
{

    using std::string;

    static const string TCP = "tcp";
    static const string UDP = "udp";
    static const string IPC = "ipc";
    static const string INPROC = "inproc";
    static const string PGM = "pgm";
    static const string EPGM = "epgm";

} // namespace protocol

namespace path
{

    using std::string;

    static const string ANY = "*";

} // namespace path

    struct LIBCLOUDLESS_EXPORT address {
        address(const std::string& protocol_, const std::string& path_,
                short port_ = 0);

        operator const std::string&() const;
        operator const char*() const;
        bool operator <(const address& rhs) const;

    private:
        std::string _M_addr;
        std::string _M_path;
        std::string _M_protocol;
        short _M_port;
    };

} // namespace cloudless

#endif // __CLOUDLESS_ADDRESS_HPP
