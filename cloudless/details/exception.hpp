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
 * A parent wrapper around Cloudless exceptions.
*/

#ifndef __CLOUDLESS_DETAILS_EXCEPTION_HPP
#define __CLOUDLESS_DETAILS_EXCEPTION_HPP

#include <exception>

#include <cloudless/details/export.hpp>

namespace cloudless
{

namespace details
{

    /**
     * A wrapper exception around all Cloudless exceptions.
     */

    struct LIBCLOUDLESS_EXPORT exception : std::exception
    {
        virtual const char* what() const throw() = 0;
    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_EXCEPTION_HPP
