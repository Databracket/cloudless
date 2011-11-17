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
#include <cloudless/details/zeromq/zsocket.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

namespace details
{

    // zsocket

    zsocket::zsocket(zcontext& context_, int type_)
    {
        _M_ptr = zmq_socket(context_, type_);

        if (_M_ptr == NULL)
            throw zexception();
    }

    zsocket::~zsocket()
    {
        if (_M_ptr == NULL)
            return;

        zmq_close(_M_ptr);

        _M_ptr = NULL;
    }

    void
    zsocket::close()
    {
        if (_M_ptr == NULL)
            return;

        int rc = zmq_close(_M_ptr);

        if (rc == -1)
            throw zexception();

        _M_ptr = NULL;
    }

    void
    zsocket::setsockopt(int option_, const void* optval_,
            size_t optvallen_)
    {
        int rc = zmq_setsockopt(_M_ptr, option_, optval_, optvallen_);

        if (rc == -1)
            throw zexception();
    }

    void
    zsocket::getsockopt(int option_, void* optval_,
            size_t* optvallen_) const
    {
        int rc = zmq_getsockopt(_M_ptr, option_, optval_, optvallen_);

        if (rc == -1)
            throw zexception();
    }

    void
    zsocket::bind(const char* addr_)
    {
        int rc = zmq_bind(_M_ptr, addr_);

        if (rc == -1)
            throw zexception();
    }

    void
    zsocket::connect(const char* addr_)
    {
        int rc = zmq_connect(_M_ptr, addr_);

        if (rc == -1)
            throw zexception();
    }

    bool
    zsocket::sendmsg(zmessage& msg_, int flags_)
    {
        int rc = zmq_sendmsg(_M_ptr, msg_, flags_);

        if (rc == 0)
            return true;

        if (rc == -1 && zmq_errno() == EAGAIN)
            return false;

        throw zexception();
    }

    bool
    zsocket::recvmsg(zmessage& msg_, int flags_)
    {
        int rc = zmq_recvmsg(_M_ptr, msg_, flags_);

        if (rc == 0)
            return true;

        if (rc == -1 && zmq_errno() == EAGAIN)
            return false;

        throw zexception();
    }

    zsocket::operator void*() const throw()
    {
        return _M_ptr;
    }

} // namespace details

} // namespace cloudless
