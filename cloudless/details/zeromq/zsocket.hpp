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
 * A wrapper around 0MQ low level socket interface.
*/

#ifndef __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_HPP
#define __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_HPP

#include <string>

#include <cloudless/details/export.hpp>
#include <cloudless/details/noncopyable.hpp>
#include <cloudless/details/zeromq/zcontext.hpp>
#include <cloudless/details/zeromq/zmessage.hpp>

namespace cloudless
{

namespace socket_type
{

    // Socket types
    static const int PAIR = ZMQ_PAIR;
    static const int PUB = ZMQ_PUB;
    static const int SUB = ZMQ_SUB;
    static const int REQ = ZMQ_REQ;
    static const int REP = ZMQ_REP;
    static const int DEALER = ZMQ_DEALER;
    static const int ROUTER = ZMQ_ROUTER;
    static const int PULL = ZMQ_PULL;
    static const int PUSH = ZMQ_PUSH;
    static const int XPUB = ZMQ_XPUB;
    static const int XSUB = ZMQ_XSUB;

    // Backwards compatibility
    static const int XREQ = DEALER;
    static const int XREP = ROUTER;

} // namespace socket_type

namespace details
{

    /**
     * A wrapper structure around 0MQ low level socket interface.
     */

    struct LIBCLOUDLESS_EXPORT zsocket : noncopyable
    {

        /**
         * A constructor that takes a zcontext and a socket type.
         *
         * @param context_ a zcontext reference.
         * @param type_ a socket type from cloudless::socket_type
         */
        zsocket(zcontext& context_, int type_);

        /**
         * A destructor to close the 0MQ socket.
         * This destructor is essentially the same as close()
         * but does not check for errors from zmq_close() as
         * destructors must not raise exceptions.
         */
        virtual ~zsocket();

        /**
         * A function to close the 0MQ socket.
         */
        void close();

        /**
         * Set 0MQ socket options.
         *
         * @param option_ a 0MQ socket option. See to 0MQ's documentation.
         * @param optval_ a pointer to the value of the option to be assigned.
         * @param optvallen_ the size of the container of the value.
         */
        void setsockopt(int option_, const void* optval_, size_t optvallen_);

        /**
         * Get 0MQ socket options.
         *
         * @param option_ a 0MQ socket option. See to 0MQ's documentation.
         * @param optval_ a pointer to a value container to be assigned to.
         * @param optvallen_ the size of the container of the value.
         */
        void getsockopt(int option_, void* optval_, size_t* optvallen_) const;

        /**
         * Bind a socket to a specific address.
         *
         * @param addr_ a 0MQ address. See to 0MQ's documentation.
         */
        void bind(const char* addr_);

        /**
         * Connect a socket to a specific address.
         *
         * @param addr_ a 0MQ address. See to 0MQ's documentation.
         */
        void connect(const char* addr_);

        /**
         * Send a message.
         *
         * @param msg_ a reference to a zmessage instance.
         * @param flags_ send flags to be passed to 0MQ's interface. See to 0MQ's documentation.
         * @return whether the message was sent successfully.
         */
        bool sendmsg(zmessage& msg_, int flags_ = 0);

        /**
         * Receive a message.
         *
         * @param msg_ a reference to a zmessage instance.
         * @param flags_ receive flags to be passed to 0MQ's interface. See to 0MQ's documentation.
         * @return whether the message was received successfully.
         */
        bool recvmsg(zmessage& msg_, int flags_ = 0);

        /* GETTERS */

        /**
         * Get socket's affinity. See 0MQ's documentation.
         *
         * @return the affinity of this socket.
         */
        uint64_t affinity() const;

        /**
         * Get socket's identity. See 0MQ's documentation.
         *
         * @return the socket identity in a std::string representation.
         */
        std::string identity() const;

        /**
         * Get socket's multicast data rate. See 0MQ's documentation.
         *
         * @return the socket's multicast data rate in kilobits per second.
         */
        int rate() const;

        /**
         * Get multicast recovery interval. See 0MQ's documentation.
         *
         * @return the socket's multicast recovery interval.
         */
        int recovery_ivl() const;

        /**
         * Get kernel transmit buffer size. See 0MQ's documentation.
         *
         * @return the transmit buffer size of the kernel.
         */
        int send_buffer() const;

        /**
         * Get kernel receive buffer size. See 0MQ's documentation.
         *
         * @return the receive buffer size of the kernel.
         */
        int recv_buffer() const;

        /**
         * Check if there are more message parts to
         * follow while receiving a message. See 0MQ's documentation.
         *
         * @return true or false.
         */
        bool recv_more() const;

        /**
         * Get the file descriptor associated with the socket. See 0MQ's documentation.
         *
         * @return socket's FD. Either int on POSIX systems, or SOCKET on Windows.
         */
        socket_t fd() const;

        /**
         * Check if a message can be sent without blocking. See 0MQ's documentation.
         *
         * @return true or false.
         */
        bool can_send() const;

        /**
         * Check if a message can be received without blocking. See 0MQ's documentation.
         *
         * @return true or false.
         */
        bool can_recv() const;

        /**
         * Get this socket's type.
         *
         * @return a value matching one of the types in socket_types.
         */
        int type() const;

        /**
         * Get the linger period for socket shutdown. See 0MQ's documentation.
         *
         * @return the linger period in milliseconds. -1 means infinite.
         */
        int linger() const;

        /**
         * Get reconnection interval. See 0MQ's documentation.
         *
         * @return the reconnection interval in milliseconds.
         */
        int reconnect_ivl() const;

        /**
         * Get the maximum reconnection interval. See 0MQ's documentation.
         *
         * @return the maximum reconnection interval in milliseconds.
         */
        int reconnect_ivl_max() const;

        /**
         * Get the maximum length of the queue of outstanding
         * connections. See 0MQ's documentation.
         *
         * @return the number of connections.
         */
        int backlog() const;

        /**
         * Get maximum acceptable inbound message size. See 0MQ's documentation.
         *
         * @return maximum acceptable inbound message size in bytes. Value of -1 means no limit.
         */
        int64_t max_msg_size() const;

        /**
         * Get high water mark for outbound messages. See 0MQ's documentation.
         *
         * @return high water mark for outbound messages.
         */
        int send_hwm() const;

        /**
         * Get high water mark for inbound messages. See 0MQ's documentation.
         *
         * @return high water mark for inbound messages.
         */
        int recv_hwm() const;

        /**
         * Get maximum network hops for multicast packets. See 0MQ's documentation.
         *
         * @return maximum network hops.
         */
        int multicast_hops() const;

        /**
         * Get maximum time before a send operation times out. See 0MQ's documentation.
         *
         * @return maximum time before a send operation times out in milliseconds.
         */
        int send_timeout() const;

        /**
         * Get maximum time before a receive operation times out. See 0MQ's documentation.
         *
         * @return maximum time before a receive operation times out in milliseconds.
         */
        int recv_timeout() const;

        /**
         * Check if this socket will operate only on IPv4. See 0MQ's documentation.
         *
         * @return true or false.
         */
        bool ipv4_only() const;

        /* SETTERS */

        /**
         * Set socket's affinity. See 0MQ's documentation.
         *
         * @param affinity_ the affinity of this socket.
         */
        zsocket& affinity(uint64_t affinity_);

        /**
         * Set socket's identity. See 0MQ's documentation.
         *
         * @param identity_ the socket identity in a std::string representation.
         */
        zsocket& identity(const std::string& identity_);

        /**
         * Set socket's multicast data rate. See 0MQ's documentation.
         *
         * @param rate_ the socket's multicast data rate in kilobits per second.
         */
        zsocket& rate(int rate_);

        /**
         * Set multicast recovery interval. See 0MQ's documentation.
         *
         * @param ivl_ the socket's multicast recovery interval.
         */
        zsocket& recovery_ivl(int ivl_);

        /**
         * Set kernel transmit buffer size. See 0MQ's documentation.
         *
         * @param size_ the transmit buffer size of the kernel.
         */
        zsocket& send_buffer(int size_);

        /**
         * Set kernel receive buffer size. See 0MQ's documentation.
         *
         * @param size_ the receive buffer size of the kernel.
         */
        zsocket& recv_buffer(int size_);

        /**
         * Set the linger period for socket shutdown. See 0MQ's documentation.
         *
         * @param linger_ the linger period in milliseconds. -1 means infinite.
         */
        zsocket& linger(int linger_);

        /**
         * Set reconnection interval. See 0MQ's documentation.
         *
         * @param ivl_ the reconnection interval in milliseconds.
         * @param max_ the maximum reconnection interval in milliseconds.
         */
        zsocket& reconnect_ivl(int ivl_, int max_ = 0);

        /**
         * Set the maximum length of the queue of outstanding
         * connections. See 0MQ's documentation.
         *
         * @param backlog_ the number of connections.
         */
        zsocket& backlog(int backlog_);

        /**
         * Set maximum acceptable inbound message size. See 0MQ's documentation.
         *
         * @param max_size_ maximum acceptable inbound message size in bytes.
         * Value of -1 means no limit.
         */
        zsocket& max_msg_size(int64_t max_size_);

        /**
         * Set high water mark for both inbound and outbound messages. See 0MQ's documentation.
         *
         * @param hwm_ high water mark for inbound and outbound messages.
         */
        zsocket& hwm(int hwm_);

        /**
         * Set high water mark for outbound messages. See 0MQ's documentation.
         *
         * @param hwm_ high water mark for outbound messages.
         */
        zsocket& send_hwm(int hwm_);

        /**
         * Set high water mark for inbound messages. See 0MQ's documentation.
         *
         * @param hwm_ high water mark for inbound messages.
         */
        zsocket& recv_hwm(int hwm_);

        /**
         * Set maximum network hops for multicast packets. See 0MQ's documentation.
         *
         * @param hops_ maximum network hops.
         */
        zsocket& multicast_hops(int hops_);

        /**
         * Set maximum time before a send operation times out. See 0MQ's documentation.
         *
         * @param timeout_ maximum time before a send operation times out in milliseconds.
         */
        zsocket& send_timeout(int timeout_);

        /**
         * Set maximum time before a receive operation times out. See 0MQ's documentation.
         *
         * @param timeout_ maximum time before a receive operation times out in milliseconds.
         */
        zsocket& recv_timeout(int timeout_);

        /**
         * Set this socket to operate only on IPv4. See 0MQ's documentation.
         *
         * @param ipv4_only_ true or false.
         */
        zsocket& ipv4_only(bool ipv4_only_);

        /**
         * Subscribe to a topic on a SUB socket. See 0MQ's documentation.
         *
         * @param topic_ a topic to subscribe to.
         */
        zsocket& subscribe(const std::string& topic_);

        /**
         * Unsubscribe from a topic on a SUB socket. See 0MQ's documentation.
         *
         * @param topic_ a topic to unsubscribe from.
         */
        zsocket& unsubscribe(const std::string& topic_);

        /**
         * Expose internal 0MQ's socket pointer.
         *
         * @return 0MQ's socket void pointer.
         */
        operator void*() const throw();

    private:
        int _M_get_events() const;

    private:
        void* _Mp_ptr;
        int _M_recvtimeo;
        int _M_sendtimeo;
    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_ZEROMQ_ZSOCKET_HPP
