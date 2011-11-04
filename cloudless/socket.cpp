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

#include <cloudless/socket.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    socket::socket(context& context_, int type_) :
        details::zsocket_base(context_, type_)
    {}

    void
    socket::bind(const std::string& addr_)
    {
        bind(addr_.c_str());
    }

    void
    socket::bind(const address& addr_)
    {
        bind((const char*) addr_);
    }

    void
    socket::connect(const std::string& addr_)
    {
        connect(addr_.c_str());
    }

    void
    socket::connect(const address& addr_)
    {
        connect((const char*) addr_);
    }

    bool
    socket::send(messages& msgs_, bool block_)
    {
        if (msgs_->empty())
            throw message_empty();

        while (msgs_.size()) {
            if (!sendmsg(*msgs_->front(),
                        (msgs_->size() > 1 ? ZMQ_SNDMORE : 0)
                        | (block_ == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msgs_->pop_front();
        }

        return true;
    }

    bool
    socket::recv(messages& msgs_, bool block_)
    {
        return false;
        // TODO: Do this NOW!
    }

} // namespace cloudless
