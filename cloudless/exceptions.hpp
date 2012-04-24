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
 * Exception wrappers.
*/

#ifndef __CLOUDLESS_EXCEPTIONS_HPP
#define __CLOUDLESS_EXCEPTIONS_HPP

#include <cloudless/details/export.hpp>
#include <cloudless/details/exception.hpp>

namespace cloudless
{

    using details::exception;

    struct LIBCLOUDLESS_EXPORT null_pointer : exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT message_empty : exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT poll_empty : exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT poll_not_found : exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT zexception : exception
    {
        zexception();

        virtual const char* what() const throw();
        int error_num() const throw();

    private:
        int _M_errnum;
    };

    struct LIBCLOUDLESS_EXPORT feature_not_supported : exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT function_not_implemented : exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT crypto_exception : exception
    {
        virtual const char* what() const throw() = 0;
    };

    struct LIBCLOUDLESS_EXPORT size_mismatch : crypto_exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT mac_verification_failed : crypto_exception
    {
        virtual const char* what() const throw();
    };

} // namespace cloudless

#endif // __CLOUDLESS_EXCEPTIONS_HPP
