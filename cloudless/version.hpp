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

#ifndef __CLOUDLESS_VERSION_HPP
#define __CLOUDLESS_VERSION_HPP

#define CLOUDLESS_VERSION_MAJOR 0
#define CLOUDLESS_VERSION_MINOR 1
#define CLOUDLESS_VERSION_PATCH 0

#define CLOUDLESS_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define CLOUDLESS_VERSION \
    CLOUDLESS_MAKE_VERSION(CLOUDLESS_VERSION_MAJOR, CLOUDLESS_VERSION_MINOR, \
            CLOUDLESS_VERSION_PATCH)

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zeromq.hpp>

namespace cloudless
{

    // version

    struct LIBCLOUDLESS_EXPORT version
    {
        static int major() throw() { return CLOUDLESS_VERSION_MAJOR; }
        static int minor() throw() { return CLOUDLESS_VERSION_MINOR; }
        static int patch() throw() { return CLOUDLESS_VERSION_PATCH; }
        int operator ()() const throw() { return CLOUDLESS_VERSION; }
    };

    // zversion

    struct LIBCLOUDLESS_EXPORT zversion
    {
        static int major() throw() { return ZMQ_VERSION_MAJOR; }
        static int minor() throw() { return ZMQ_VERSION_MINOR; }
        static int patch() throw() { return ZMQ_VERSION_PATCH; }
        int operator ()() const throw() { return ZMQ_VERSION; }
    };

} // namespace cloudless

#endif // __CLOUDLESS_VERSION_HPP
