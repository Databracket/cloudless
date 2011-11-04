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

#ifndef __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_BASE_HPP
#define __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_BASE_HPP

#include <cloudless/details/export.hpp>
#include <cloudless/details/noncopyable.hpp>
#include <cloudless/details/zeromq/zcontext.hpp>
#include <cloudless/details/zeromq/zmessage.hpp>

namespace cloudless
{

namespace details
{

    struct LIBCLOUDLESS_EXPORT zsocket_base : noncopyable
    {
        zsocket_base(zcontext& context_, int type_);
        virtual ~zsocket_base();

        void close();

        void setsockopt(int option_, const void* optval_, size_t optvallen_);
        void getsockopt(int option_, void* optval_, size_t* optvallen_);

        void bind(const char* addr_);
        void connect(const char* addr_);

        bool sendmsg(zmessage& msg_, int flags_ = 0);
        bool recvmsg(zmessage& msg_, int flags_ = 0);

        operator void*() const throw();

    private:
        void* _M_ptr;
    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_BASE_HPP
