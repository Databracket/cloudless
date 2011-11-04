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

#ifndef __CLOUDLESS_DETAILS_ZEROMQ_ZMESSAGE_HPP
#define __CLOUDLESS_DETAILS_ZEROMQ_ZMESSAGE_HPP

#include <string>

#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/details/export.hpp>

namespace cloudless
{

namespace details
{

    struct LIBCLOUDLESS_EXPORT zmessage : private zmq_msg_t
    {
        zmessage();
        zmessage(size_t size_);
        zmessage(const zmessage& msg_);
        ~zmessage();

        void* data() const throw();
        size_t size() const throw();
        std::string toString();

        operator zmq_msg_t*() throw();

        const zmessage& operator=(const zmessage& rhs);
    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_ZEROMQ_ZMESSAGE_HPP
