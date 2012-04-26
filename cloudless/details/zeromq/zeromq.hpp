/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket LLC.
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
 * Helpers to wrap the differences between 0MQ 2.1.x and 3.1.x.
*/

#ifndef __CLOUDLESS_DETAILS_ZEROMQ_ZEROMQ_HPP
#define __CLOUDLESS_DETAILS_ZEROMQ_ZEROMQ_HPP

#include <zmq.h>
#include <stdint.h>

#ifndef ZMQ_DONTWAIT
#	define ZMQ_DONTWAIT		ZMQ_NOBLOCK
#endif

#if ZMQ_VERSION_MAJOR == 2
#	define zmq_sendmsg		zmq_send
#	define zmq_recvmsg		zmq_recv
#	define ZMQ_POLL_MSEC	1000		// zmq_poll takes usec
#	define int64v			int64_t
#	define uint32v			uint32_t
#	define uint64v			uint64_t
#elif ZMQ_VERSION_MAJOR == 3
#	define ZMQ_POLL_MSEC	1			// zmq_poll takes msec
#	define int64v			int
#	define uint32v			int
#	define uint64v			int
#endif

namespace cloudless
{

#ifdef _WIN32
    typedef SOCKET socket_t;
#else
    typedef int socket_t;
#endif

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_ZEROMQ_ZEROMQ_HPP
