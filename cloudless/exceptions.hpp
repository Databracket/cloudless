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

#ifndef CLOUDLESS_EXCEPTIONS_HPP
#define CLOUDLESS_EXCEPTIONS_HPP

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/exception.hpp>

namespace cloudless
{

    using detail::exception;

    struct LIBCLOUDLESS_EXPORT null_pointer : exception
    {
        null_pointer(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT message_empty : exception
    {
        message_empty(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT poll_empty : exception
    {
        poll_empty(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT poll_not_found : exception
    {
        poll_not_found(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT zexception : exception
    {
        zexception(const char* file, int line);
        int error_num() const throw();

    private:
        int _M_errnum;
    };

    struct LIBCLOUDLESS_EXPORT feature_not_supported : exception
    {
        feature_not_supported(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT function_not_implemented : exception
    {
        function_not_implemented(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT invalid_format : exception
    {
        invalid_format(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT not_fully_parsed : exception
    {
        not_fully_parsed(const char* file, int line);
    };

    // crypto

    struct LIBCLOUDLESS_EXPORT crypto_exception : exception
    {
        crypto_exception(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT size_mismatch : crypto_exception
    {
        size_mismatch(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT mac_verification_failed : crypto_exception
    {
        mac_verification_failed(const char* file, int line);
    };

    // edges

    struct LIBCLOUDLESS_EXPORT edgepoint_not_found : exception
    {
        edgepoint_not_found(const char* file, int line);
    };

    struct LIBCLOUDLESS_EXPORT point_not_found : exception
    {
        point_not_found(const char* file, int line);
    };

} // namespace cloudless

#endif // CLOUDLESS_EXCEPTIONS_HPP
