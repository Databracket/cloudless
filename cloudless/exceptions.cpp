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
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    // null_pointer

    const char*
    null_pointer::what() const throw()
    {
        return "NULL pointer exception";
    }

    // message_empty

    const char*
    message_empty::what() const throw()
    {
        return "message is empty";
    }

    // poll_empty

    const char*
    poll_empty::what() const throw()
    {
        return "poll is empty";
    }

    // poll_not_found

    const char*
    poll_not_found::what() const throw()
    {
        return "item not found";
    }

    // zexception

    zexception::zexception() :
        _M_errnum(zmq_errno())
    {}

    const char*
    zexception::what() const throw()
    {
        return zmq_strerror(_M_errnum);
    }

    int
    zexception::error_num() const throw()
    {
        return _M_errnum;
    }

    // feature_not_supported

    const char*
    feature_not_supported::what() const throw()
    {
        return "this socket type doesn't support this feature";
    }

    // function_not_implemented

    const char*
    function_not_implemented::what() const throw()
    {
        return "this function is not implemented";
    }

    // size_mismatch

    const char*
    size_mismatch::what() const throw()
    {
        return "size mismatch";
    }

    // mac_verification_failed

    const char*
    mac_verification_failed::what() const throw()
    {
        return "MAC verification failed";
    }

} // namespace cloudless
