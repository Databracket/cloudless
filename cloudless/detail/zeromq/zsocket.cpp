/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket LLC.
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
 * A wrapper around 0MQ low level socket interface.
*/

#include <cloudless/detail/zeromq/zeromq.hpp>
#include <cloudless/detail/zeromq/zsocket.hpp>
#include <cloudless/exceptions.hpp>

#define _M_getsockopt(opt_, optval_) \
    size_t optvallen_ = sizeof(optval_); \
    getsockopt(opt_, (void*)&optval_, &optvallen_);

#define _M_setsockopt(opt_, optval_) \
    setsockopt(opt_, (void*)&optval_, sizeof(optval_));

namespace cloudless
{

namespace detail
{

    // zsocket

    zsocket::zsocket(zcontext& context, int type) :
        _M_recvtimeo(-1), _M_sendtimeo(-1)
    {
        _Mp_ptr = zmq_socket(context, type);

        if (_Mp_ptr == NULL)
            raise(zexception);
    }

    zsocket::~zsocket()
    {
        if (_Mp_ptr == NULL)
            return;

        zmq_close(_Mp_ptr);

        _Mp_ptr = NULL;
    }

    void
    zsocket::close()
    {
        if (_Mp_ptr == NULL)
            return;

        int rc = zmq_close(_Mp_ptr);

        if (rc == -1)
            raise(zexception);

        _Mp_ptr = NULL;
    }

    void
    zsocket::setsockopt(int option, const void* optval,
            size_t optvallen)
    {
        int rc = zmq_setsockopt(_Mp_ptr, option, optval, optvallen);

        if (rc == -1)
            raise(zexception);
    }

    void
    zsocket::getsockopt(int option, void* optval,
            size_t* optvallen) const
    {
        int rc = zmq_getsockopt(_Mp_ptr, option, optval, optvallen);

        if (rc == -1)
            raise(zexception);
    }

    void
    zsocket::bind(const char* addr)
    {
        int rc = zmq_bind(_Mp_ptr, addr);

        if (rc == -1)
            raise(zexception);
    }

    void
    zsocket::connect(const char* addr)
    {
        int rc = zmq_connect(_Mp_ptr, addr);

        if (rc == -1)
            raise(zexception);
    }

    bool
    zsocket::sendmsg(zmessage& msg, int flags)
    {
        int rc = zmq_sendmsg(_Mp_ptr, msg, flags);

#if ZMQ_VERSION_MAJOR == 3
        if (rc > 0) // 0MQ 3.x returns the number of bytes sent
            return true;
#elif ZMQ_VERSION_MAJOR == 2
        if (rc == 0)
            return true;
#endif

        if (rc == -1 && zmq_errno() == EAGAIN)
            return false;

        raise(zexception);
    }

    bool
    zsocket::recvmsg(zmessage& msg, int flags)
    {
        int rc = zmq_recvmsg(_Mp_ptr, msg, flags);

#if ZMQ_VERSION_MAJOR == 3
        if (rc > 0) // 0MQ 3.x returns the number of bytes received
            return true;
#elif ZMQ_VERSION_MAJOR == 2
        if (rc == 0)
            return true;
#endif

        if (rc == -1 && zmq_errno() == EAGAIN)
            return false;

        raise(zexception);
    }

    uint64_t
    zsocket::affinity() const
    {
        uint64_t affinity;

        _M_getsockopt(ZMQ_AFFINITY, affinity);
        return affinity;
    }

    std::string
    zsocket::identity() const
    {
        char id[256];

        _M_getsockopt(ZMQ_IDENTITY, id);
        return std::string(id, optvallen_);
    }

    int
    zsocket::rate() const
    {
        int64v rate;

        _M_getsockopt(ZMQ_RATE, rate);
        return rate;
    }

    int
    zsocket::recovery_ivl() const
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
    zsocket::send_buffer() const
    {
        uint64v buffer;

        _M_getsockopt(ZMQ_SNDBUF, buffer);
        return buffer;
    }

    int
    zsocket::recv_buffer() const
    {
        uint64v buffer;

        _M_getsockopt(ZMQ_RCVBUF, buffer);
        return buffer;
    }

    bool
    zsocket::recv_more() const
    {
        int64v more;

        _M_getsockopt(ZMQ_RCVMORE, more);
        return more;
    }

    socket_t
    zsocket::fd() const
    {
        socket_t fd;

        _M_getsockopt(ZMQ_FD, fd);
        return fd;
    }

    bool
    zsocket::can_send() const
    {
        return _M_get_events() & ZMQ_POLLOUT;
    }

    bool
    zsocket::can_recv() const
    {
        return _M_get_events() & ZMQ_POLLIN;
    }

    int
    zsocket::type() const
    {
        int type;

        _M_getsockopt(ZMQ_TYPE, type);
        return type;
    }

    int
    zsocket::linger() const
    {
        int linger;

        _M_getsockopt(ZMQ_LINGER, linger);
        return linger;
    }

    int
    zsocket::reconnect_ivl() const
    {
        int ivl;

        _M_getsockopt(ZMQ_RECONNECT_IVL, ivl);
        return ivl;
    }

    int
    zsocket::reconnect_ivl_max() const
    {
        int ivl_max;

        _M_getsockopt(ZMQ_RECONNECT_IVL_MAX, ivl_max);
        return ivl_max;
    }

    int
    zsocket::backlog() const
    {
        int backlog;

        _M_getsockopt(ZMQ_BACKLOG, backlog);
        return backlog;
    }

    int64_t
    zsocket::max_msg_size() const
    {
        int64_t mms = -1;

#if ZMQ_VERSION_MAJOR == 3
        _M_getsockopt(ZMQ_MAXMSGSIZE, mms);
#endif
        return mms;
    }

    int
    zsocket::send_hwm() const
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
    zsocket::recv_hwm() const
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
    zsocket::multicast_hops() const
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
    zsocket::send_timeout() const
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
    zsocket::recv_timeout() const
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
    zsocket::ipv4_only() const
    {
#if ZMQ_VERSION_MAJOR == 3
        int ipv4;

        _M_getsockopt(ZMQ_IPV4ONLY, ipv4);
        return ipv4;
#elif ZMQ_VERSION_MAJOR == 2
        return true;
#endif
    }

    zsocket&
    zsocket::affinity(uint64_t affinity)
    {
        _M_setsockopt(ZMQ_AFFINITY, affinity);
        return *this;
    }

    zsocket&
    zsocket::identity(const std::string& identity)
    {
        setsockopt(ZMQ_IDENTITY, identity.c_str(), identity.size());
        return *this;
    }

    zsocket&
    zsocket::rate(int rate)
    {
        int64v rate_ = rate;

        _M_setsockopt(ZMQ_RATE, rate_);
        return *this;
    }

    zsocket&
    zsocket::recovery_ivl(int ivl)
    {
#if ZMQ_VERSION_MAJOR == 3
        int opt = ZMQ_RECOVERY_IVL;
#elif ZMQ_VERSION_MAJOR == 2
        int opt = ZMQ_RECOVERY_IVL_MSEC;
#endif
        int64v ivl_ = ivl;

        _M_setsockopt(opt, ivl_);
        return *this;
    }

    zsocket&
    zsocket::send_buffer(int size)
    {
        uint64v size_ = size;

        _M_setsockopt(ZMQ_SNDBUF, size_);
        return *this;
    }

    zsocket&
    zsocket::recv_buffer(int size)
    {
        uint64v size_ = size;

        _M_setsockopt(ZMQ_RCVBUF, size_);
        return *this;
    }

    zsocket&
    zsocket::linger(int linger)
    {
        _M_setsockopt(ZMQ_LINGER, linger);
        return *this;
    }

    zsocket&
    zsocket::reconnect_ivl(int ivl, int max)
    {
        _M_setsockopt(ZMQ_RECONNECT_IVL, ivl);
        _M_setsockopt(ZMQ_RECONNECT_IVL_MAX, max);
        return *this;
    }

    zsocket&
    zsocket::backlog(int backlog)
    {
        _M_setsockopt(ZMQ_BACKLOG, backlog);
        return *this;
    }

    zsocket&
    zsocket::max_msg_size(int64_t max_size)
    {
#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_MAXMSGSIZE, max_size);
#endif
        return *this;
    }

    zsocket&
    zsocket::hwm(int hwm)
    {
#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_SNDHWM, hwm);
        _M_setsockopt(ZMQ_RCVHWM, hwm);
#elif ZMQ_VERSION_MAJOR == 2
        uint64v hwm_ = hwm;

        _M_setsockopt(ZMQ_HWM, hwm_);
#endif
        return *this;
    }

    zsocket&
    zsocket::send_hwm(int hwm)
    {
#if ZMQ_VERSION_MAJOR == 3
        int hwm_type = ZMQ_SNDHWM;
#elif ZMQ_VERSION_MAJOR == 2
        int hwm_type = ZMQ_HWM;
#endif
        uint64v hwm_ = hwm;

        _M_setsockopt(hwm_type, hwm_);
        return *this;
    }

    zsocket&
    zsocket::recv_hwm(int hwm)
    {
#if ZMQ_VERSION_MAJOR == 3
        int hwm_type = ZMQ_RCVHWM;
#elif ZMQ_VERSION_MAJOR == 2
        int hwm_type = ZMQ_HWM;
#endif
        uint64v hwm_ = hwm;

        _M_setsockopt(hwm_type, hwm_);
        return *this;
    }

    zsocket&
    zsocket::multicast_hops(int hops)
    {
#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_MULTICAST_HOPS, hops);
#endif
        return *this;
    }

    zsocket&
    zsocket::send_timeout(int timeout)
    {
        _M_sendtimeo = timeout;

#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_SNDTIMEO, _M_sendtimeo);
#endif
        return *this;
    }

    zsocket&
    zsocket::recv_timeout(int timeout)
    {
        _M_recvtimeo = timeout;

#if ZMQ_VERSION_MAJOR == 3
        _M_setsockopt(ZMQ_RCVTIMEO, _M_recvtimeo);
#endif
        return *this;
    }

    zsocket&
    zsocket::ipv4_only(bool ipv4_only)
    {
#if ZMQ_VERSION_MAJOR == 3
        int ipv4 = ipv4_only;

        _M_setsockopt(ZMQ_IPV4ONLY, ipv4);
#endif
        return *this;
    }

    zsocket&
    zsocket::subscribe(const std::string& topic)
    {
        if (type() != socket_type::SUB)
            raise(feature_not_supported);

        setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
        return *this;
    }

    zsocket&
    zsocket::unsubscribe(const std::string& topic)
    {
        if (type() != socket_type::SUB)
            raise(feature_not_supported);

        setsockopt(ZMQ_UNSUBSCRIBE, topic.c_str(), topic.size());
        return *this;
    }

    zsocket::operator void*() const throw()
    {
        return _Mp_ptr;
    }

    int
    zsocket::_M_get_events() const
    {
        uint32v event;

        _M_getsockopt(ZMQ_EVENTS, event);
        return event;
    }

} // namespace detail

} // namespace cloudless
