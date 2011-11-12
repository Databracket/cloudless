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
#include <cloudless/messages.hpp>
#include <cloudless/address.hpp>
#include <cloudless/pollitem.hpp>

namespace cloudless
{

    struct LIBCLOUDLESS_EXPORT socket : details::zsocket
    {
        socket(context& context_, int type_);

        void bind(const std::string& addr_);
        void bind(const address& addr_);

        void connect(const std::string& addr_);
        void connect(const address& addr_);

        bool send(messages& msgs_, bool block_ = true);
        bool recv(messages& msgs_, bool block_ = true);

        void set_send_timeout(int timeout_);
        void set_recv_timeout(int timeout_);

        pollitem& poll_item() throw();

    private:
        int _M_recvtimeo;
        int _M_sendtimeo;
        details::shared_ptr<pollitem> _M_ip;
    };

} // namespace cloudless

#endif // __CLOUDLESS_SOCKET_HPP
