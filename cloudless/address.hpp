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
 * An abstraction of 0MQ socket addresses.
*/

#ifndef CLOUDLESS_ADDRESS_HPP
#define CLOUDLESS_ADDRESS_HPP

#include <string>
#include <utility>

#include <cloudless/detail/export.hpp>

namespace cloudless
{

namespace protocol
{

    using std::string;

    /*
     * The protocols that can be used in an address.
     */
    static const string TCP = "tcp"; // takes a host and a port.
    static const string UDP = "udp"; // takes a host and a port.
    static const string IPC = "ipc"; // takes path to a file and no port.
    static const string INPROC = "inproc"; // takes unique string as a path and no port.
    static const string PGM = "pgm"; // takes a host and a port.
    static const string EPGM = "epgm"; // same as PGM.

} // namespace protocol

namespace path
{

    using std::string;

    static const string ANY = "*";

} // namespace path

    using namespace std::rel_ops;

    /**
     * A structure abstracting 0MQ socket's addresses.
     * The structure can be casted to std::string to get the full address,
     * or a char array. It can also be compared to another address structure
     * in a similar fashion of comparing two objects of std::string.
     */
    struct LIBCLOUDLESS_EXPORT address {

        /**
         * A constructor that accepts a protocol, a path or a host,
         * and a port if applicable.
         *
         * @param protocol a protocol which will be used for two sockets to communicate on.
         * @param path a host or a unique string, depending on the protocol.
         * @param port a port number to be used along with the protocol.
         */
        address(const std::string& protocol, const std::string& path,
                short port = 0);

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

#endif // CLOUDLESS_ADDRESS_HPP
