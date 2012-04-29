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
 * Exception wrappers.
*/

#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    // null_pointer

    null_pointer::null_pointer(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "NULL pointer exception";
    }

    // message_empty

    message_empty::message_empty(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "message is empty";
    }

    // poll_empty

    poll_empty::poll_empty(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "poll is empty";
    }

    // poll_not_found

    poll_not_found::poll_not_found(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "item not found";
    }

    // zexception

    zexception::zexception(const char* file_, int line_) :
        exception(file_, line_),
        _M_errnum(zmq_errno())
    {
        error += zmq_strerror(_M_errnum);
    }

    int
    zexception::error_num() const throw()
    {
        return _M_errnum;
    }

    // feature_not_supported

    feature_not_supported::feature_not_supported(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "this socket type doesn't support this feature";
    }

    // function_not_implemented

    function_not_implemented::function_not_implemented(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "this function is not implemented";
    }

    // invalid_format

    invalid_format::invalid_format(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "invalid string format";
    }

    // not_fully_parsed

    not_fully_parsed::not_fully_parsed(const char* file_, int line_) :
        exception(file_, line_)
    {
        error += "string not fully parsed";
    }

    // crypto_exception

    crypto_exception::crypto_exception(const char* file_, int line_) :
        exception(file_, line_)
    {}

    // size_mismatch

    size_mismatch::size_mismatch(const char* file_, int line_) :
        crypto_exception(file_, line_)
    {
        error += "size mismatch";
    }

    // mac_verification_failed

    mac_verification_failed::mac_verification_failed(const char* file_, int line_) :
        crypto_exception(file_, line_)
    {
        error += "MAC verification failed";
    }

} // namespace cloudless
