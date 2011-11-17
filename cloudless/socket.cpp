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

#include <cloudless/details/zeromq/zeromq.hpp>
#include <cloudless/socket.hpp>
#include <cloudless/poller.hpp>
#include <cloudless/exceptions.hpp>

#define _M_getsockopt(opt_, optval_) \
    size_t optvallen = sizeof(optval_); \
    getsockopt(opt_, (void*)&optval_, &optvallen);

#define _M_setsockopt(opt_, optval_) \
    setsockopt(opt_, (void*)&optval_, sizeof(optval_));

namespace cloudless
{

    // socket

    socket::socket(context& context_, int type_) :
        details::zsocket(context_, type_), _M_recvtimeo(-1), _M_sendtimeo(-1)
    {
        _M_ip = details::shared_ptr<pollitem>(new pollitem(*this));
    }

    socket&
    socket::bind(const std::string& addr_)
    {
        bind(addr_.c_str());

        return *this;
    }

    socket&
    socket::bind(const address& addr_)
    {
        bind((const char*) addr_);

        return *this;
    }

    socket&
    socket::connect(const std::string& addr_)
    {
        connect(addr_.c_str());

        return *this;
    }

    socket&
    socket::connect(const address& addr_)
    {
        connect((const char*) addr_);

        return *this;
    }

    bool
    socket::send(messages& msgs_, bool block_)
    {
        if (msgs_->empty())
            throw message_empty();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        poller p;
        pollitem& pi = poll_item().register_event(poll_events::OUT);

        p.add_item(pi, "__send_socket");

        if (!p.poll(block_ == true ? _M_sendtimeo : 0) || !pi.out())
            return false;
#endif

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
        if (msgs_.size())
            msgs_->clear();

#if ZMQ_VERSION_MAJOR == 2
        // An implementation for timed blocking.
        poller p;
        pollitem& pi = poll_item().register_event(poll_events::IN);

        p.add_item(pi, "__recv_socket");

        if (!p.poll(block_ == true ? _M_recvtimeo : 0) || !pi.in())
            return false;
#endif

        do {
            element e;

            if (!recvmsg(*e,
                        (block_ == true ? 0 : ZMQ_DONTWAIT)))
                return false;

            msgs_.push_tail(e);
        } while (recv_more());

        return true;
    }

    uint64_t
    socket::affinity() const
    {
        uint64_t affinity;

        _M_getsockopt(ZMQ_AFFINITY, affinity);
        return affinity;
    }

    std::string
    socket::identity() const
    {
        char id[256];

        _M_getsockopt(ZMQ_IDENTITY, id);
        return std::string(id, optvallen);
    }

    int
    socket::rate() const
    {
        int64v rate;

        _M_getsockopt(ZMQ_RATE, rate);
        return rate;
    }

    int
    socket::recovery_ivl() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int opt = ZMQ_RECOVERY_IVL;
#elif ZMQ_VERSION_MAJOR == 2
        int opt = ZMQ_RECOVERY_IVL_MSEC;
#endif
        int64v recovery_ivl;

        _M_getsockopt(opt, recovery_ivl);
        return recovery_ivl;
    }

    int
    socket::send_buffer() const
    {
        uint64v buffer;

        _M_getsockopt(ZMQ_SNDBUF, buffer);
        return buffer;
    }

    int
    socket::recv_buffer() const
    {
        uint64v buffer;

        _M_getsockopt(ZMQ_RCVBUF, buffer);
        return buffer;
    }

    bool
    socket::recv_more() const
    {
        int64v more;

        _M_getsockopt(ZMQ_RCVMORE, more);
        return more;
    }

    socket_t
    socket::fd() const
    {
        socket_t fd;

        _M_getsockopt(ZMQ_FD, fd);
        return fd;
    }

    bool
    socket::can_send() const
    {
        return _M_get_events() & ZMQ_POLLOUT;
    }

    bool
    socket::can_recv() const
    {
        return _M_get_events() & ZMQ_POLLIN;
    }

    int
    socket::type() const
    {
        int type;

        _M_getsockopt(ZMQ_TYPE, type);
        return type;
    }

    int
    socket::linger() const
    {
        int linger;

        _M_getsockopt(ZMQ_LINGER, linger);
        return linger;
    }

    int
    socket::reconnect_ivl() const
    {
        int ivl;

        _M_getsockopt(ZMQ_RECONNECT_IVL, ivl);
        return ivl;
    }

    int
    socket::reconnect_ivl_max() const
    {
        int ivl_max;

        _M_getsockopt(ZMQ_RECONNECT_IVL_MAX, ivl_max);
        return ivl_max;
    }

    int
    socket::backlog() const
    {
        int backlog;

        _M_getsockopt(ZMQ_BACKLOG, backlog);
        return backlog;
    }

    int64_t
    socket::max_msg_size() const
    {
        int64_t mms = -1;

#if ZMQ_VERSION_MAJOR == 3
        _M_getsockopt(ZMQ_MAXMSGSIZE, mms);
#endif
        return mms;
    }

    int
    socket::send_hwm() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int hwm_type = ZMQ_SNDHWM;
#elif ZMQ_VERSION_MAJOR == 2
        int hwm_type = ZMQ_HWM;
#endif
        uint64v hwm;

        _M_getsockopt(hwm_type, hwm);
        return hwm;
    }

    int
    socket::recv_hwm() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int hwm_type = ZMQ_RCVHWM;
#elif ZMQ_VERSION_MAJOR == 2
        int hwm_type = ZMQ_HWM;
#endif
        uint64v hwm;

        _M_getsockopt(hwm_type, hwm);
        return hwm;
    }

    int
    socket::multicast_hops() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int hops;

        _M_getsockopt(ZMQ_MULTICAST_HOPS, hops);
        return hops;
#elif ZMQ_VERSION_MAJOR == 2
        return -1;
#endif
    }

    int
    socket::send_timeout() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int timeo;

        _M_getsockopt(ZMQ_SNDTIMEO, timeo);
        return timeo;
#elif ZMQ_VERSION_MAJOR == 2
        return _M_sendtimeo;
#endif
    }

    int
    socket::recv_timeout() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int timeo;

        _M_getsockopt(ZMQ_RCVTIMEO, timeo);
        return timeo;
#elif ZMQ_VERSION_MAJOR == 2
        return _M_recvtimeo;
#endif
    }

    bool
    socket::ipv4_only() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int ipv4;

        _M_getsockopt(ZMQ_IPV4ONLY, ipv4);
        return ipv4;
#elif ZMQ_VERSION_MAJOR == 2
        return true;
#endif
    }

    socket&
    socket::affinity(uint64_t affinity_)
    {
        _M_setsockopt(ZMQ_AFFINITY, affinity_);
        return *this;
    }

    socket&
    socket::identity(const std::string& identity_)
    {
        setsockopt(ZMQ_IDENTITY, identity_.c_str(), identity_.size());
        return *this;
    }

    socket&
    socket::rate(int rate_)
    {
        int64v rate = rate_;

        _M_setsockopt(ZMQ_RATE, rate);
        return *this;
    }

    socket&
    socket::recovery_ivl(int ivl_)
    {
#if ZMQ_VERSION_MAJOR == 3
        int opt = ZMQ_RECOVERY_IVL;
#elif ZMQ_VERSION_MAJOR == 2
        int opt = ZMQ_RECOVERY_IVL_MSEC;
#endif
        int64v ivl = ivl_;

        _M_setsockopt(opt, ivl);
        return *this;
    }

    socket&
    socket::send_buffer(int size_)
    {
        uint64v size = size_;

        _M_setsockopt(ZMQ_SNDBUF, size);
        return *this;
    }

    socket&
    socket::recv_buffer(int size_)
    {
        uint64v size = size_;

        _M_setsockopt(ZMQ_RCVBUF, size);
        return *this;
    }

    socket&
    socket::linger(int linger_)
    {
        _M_setsockopt(ZMQ_LINGER, linger_);
        return *this;
    }

    socket&
    socket::reconnect_ivl(int ivl_, int max_)
    {
        _M_setsockopt(ZMQ_RECONNECT_IVL, ivl_);
        _M_setsockopt(ZMQ_RECONNECT_IVL_MAX, max_);
        return *this;
    }

    socket&
    socket::backlog(int backlog_)
    {
        _M_setsockopt(ZMQ_BACKLOG, backlog_);
        return *this;
    }

    socket&
    socket::max_msg_size(int64_t max_size_)
    {
#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_MAXMSGSIZE, max_size_);
#endif
        return *this;
    }

    socket&
    socket::hwm(int hwm_)
    {
#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_SNDHWM, hwm_);
        _M_setsockopt(ZMQ_RCVHWM, hwm_);
#elif ZMQ_VERSION_MAJOR == 2
        uint64v hwm = hwm_;

        _M_setsockopt(ZMQ_HWM, hwm);
#endif
        return *this;
    }

    socket&
    socket::send_hwm(int hwm_)
    {
#if ZMQ_VERSION_MAJOR == 3
        int hwm_type = ZMQ_SNDHWM;
#elif ZMQ_VERSION_MAJOR == 2
        int hwm_type = ZMQ_HWM;
#endif
        uint64v hwm = hwm_;

        _M_setsockopt(hwm_type, hwm);
        return *this;
    }

    socket&
    socket::recv_hwm(int hwm_)
    {
#if ZMQ_VERSION_MAJOR == 3
        int hwm_type = ZMQ_RCVHWM;
#elif ZMQ_VERSION_MAJOR == 2
        int hwm_type = ZMQ_HWM;
#endif
        uint64v hwm = hwm_;

        _M_setsockopt(hwm_type, hwm);
        return *this;
    }

    socket&
    socket::multicast_hops(int hops_)
    {
#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_MULTICAST_HOPS, hops_);
#endif
        return *this;
    }

    socket&
    socket::send_timeout(int timeout_)
    {
        _M_sendtimeo = timeout_;

#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_SNDTIMEO, _M_sendtimeo);
#endif
        return *this;
    }

    socket&
    socket::recv_timeout(int timeout_)
    {
        _M_recvtimeo = timeout_;

#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_RCVTIMEO, _M_recvtimeo);
#endif
        return *this;
    }

    socket&
    socket::ipv4_only(bool ipv4_only_)
    {
#if ZMQ_VERSION_MAJOR == 3
        int ipv4 = ipv4_only_;

        _M_setsockopt(ZMQ_IPV4ONLY, ipv4);
#endif
        return *this;
    }

    pollitem&
    socket::poll_item() throw()
    {
        return *_M_ip;
    }

    int
    socket::_M_get_events() const
    {
        uint32v event;

        _M_getsockopt(ZMQ_EVENTS, event);
        return event;
    }

} // namespace cloudless
