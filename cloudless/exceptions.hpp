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

#ifndef __CLOUDLESS_EXCEPTIONS_HPP
#define __CLOUDLESS_EXCEPTIONS_HPP

#include <cloudless/details/export.hpp>
#include <cloudless/details/exception.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT null_pointer : public details::exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT message_empty : public details::exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT poll_empty : public details::exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT poll_not_found : public details::exception
    {
        virtual const char* what() const throw();
    };

    struct LIBCLOUDLESS_EXPORT zexception : public details::exception
    {
        zexception();

        virtual const char* what() const throw();
        int error_num() const throw();

    private:
        int _M_errnum;
    };

} // namespace cloudless

#endif // __CLOUDLESS_EXCEPTIONS_HPP
