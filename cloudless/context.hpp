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

#ifndef __CLOUDLESS_CONTEXT_HPP
#define __CLOUDLESS_CONTEXT_HPP

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zcontext.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT context : details::zcontext
    {
        context(int io_threads_ = 4);
    };

} // namespace cloudless

#endif // __CLOUDLESS_CONTEXT_HPP
