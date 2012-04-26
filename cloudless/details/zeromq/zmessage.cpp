/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket, LLC.
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
 * A wrapper around 0MQ low level messages.
*/

#include <cassert>

#include <cloudless/details/zeromq/zmessage.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

namespace details
{

    // zmessage

    zmessage::zmessage()
    {
        int rc = zmq_msg_init(this);

        if (rc == -1)
            throw zexception();
    }

    zmessage::zmessage(size_t size_)
    {
        int rc = zmq_msg_init_size(this, size_);

        if (rc == -1)
            throw zexception();
    }

    zmessage::zmessage(const zmessage& msg_)
    {
        int rc = zmq_msg_copy(this, (zmq_msg_t*) &msg_);

        if (rc == -1)
            throw zexception();
    }

    zmessage::~zmessage()
    {
        int rc = zmq_msg_close(this);

        assert(rc == 0);
    }

    void*
    zmessage::data() const throw()
    {
        return zmq_msg_data((zmq_msg_t*)this);
    }

    size_t
    zmessage::size() const throw()
    {
        return zmq_msg_size((zmq_msg_t*)this);
    }

    zmessage::operator std::string() throw()
    {
        return std::string((const char*) data(), size());
    }

    zmessage::operator zmq_msg_t*() throw()
    {
        return this;
    }

} // namespace details

} // namespace cloudless
