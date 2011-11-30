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

#ifndef __CLOUDLESS_SOCKET_HPP
#define __CLOUDLESS_SOCKET_HPP

#include <string>

#include <cloudless/details/export.hpp>
#include <cloudless/details/zeromq/zsocket.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/address.hpp>
#include <cloudless/pollitem.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT socket : details::zsocket
    {
        socket(context& context_, int type_);

        socket& bind(const std::string& addr_);
        socket& bind(const address& addr_);

        socket& connect(const std::string& addr_);
        socket& connect(const address& addr_);

        virtual bool send(message& msg_, bool block_ = true);
        virtual bool recv(message& msg_, bool block_ = true);

        pollitem& poll_item() throw();

    private:
        details::shared_ptr<pollitem> _M_ip;
    };

} // namespace cloudless

#endif // __CLOUDLESS_SOCKET_HPP
