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
 * Unit tests for basic communication facilities.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/version.hpp>
#include <cloudless/pollitem.hpp>
#include <cloudless/poller.hpp>
#include <cloudless/socket.hpp>
#include <cloudless/exceptions.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RTA REQUIRE_THROWS_AS
#define RNT REQUIRE_NOTHROW

using namespace std;

TC ("cloudless/pollitem", "Testing pollitem interface.")
{
    cloudless::pollitem pi;

    RNT ( pi.register_event(cloudless::poll_events::IN_EVENT) );
    RNT ( pi.unregister_event(cloudless::poll_events::IN_EVENT) );
    R ( pi.in() == false );
    RNT ( pi.register_event(cloudless::poll_events::OUT_EVENT) );
    RNT ( pi.unregister_event(cloudless::poll_events::OUT_EVENT) );
    R ( pi.out() == false );
    RNT ( pi.register_event(cloudless::poll_events::ERROR_EVENT) );
    RNT ( pi.unregister_event(cloudless::poll_events::ERROR_EVENT) );
    R ( pi.error() == false );
}

TC ("cloudless/poller", "Testing poller interface.")
{
    cloudless::poller p;
    cloudless::pollitem pi;

    RNT ( p.add("test_item", pi) );
    RNT ( p["test_item"] == pi );
    RTA ( p["ghost_item"], cloudless::poll_not_found );
    R ( p.get_triggered() == "" );
}

TC ("cloudless/socket", "Testing socket interface.")
{
    cloudless::context c;
    cloudless::socket s(c, cloudless::socket_type::PAIR);

    RNT ( s.affinity(0) );
    RNT ( s.identity("\x41\x42\x43\x44") );
    RNT ( s.rate(100) );
    RNT ( s.recovery_ivl(10000) );
    RNT ( s.send_buffer(0) );
    RNT ( s.recv_buffer(0) );
    RNT ( s.linger(-1) );
    RNT ( s.reconnect_ivl(100, 500) );
    RNT ( s.backlog(100) );
    RNT ( s.max_msg_size(10) );

    if (cloudless::zversion::major() == 3) {
        RNT ( s.send_hwm(1000) );
        RNT ( s.recv_hwm(2000) );
    } else if (cloudless::zversion::major() == 2)
        RNT ( s.hwm(2000) );

    RNT ( s.multicast_hops(1) );
    RNT ( s.send_timeout(-1) );
    RNT ( s.recv_timeout(-1) );
    RNT ( s.ipv4_only(true) );

    R ( s.affinity() == 0 );
    R ( s.identity() == "\x41\x42\x43\x44");
    R ( s.rate() == 100 );
    R ( s.recovery_ivl() == 10000 );
    R ( s.send_buffer() == 0 );
    R ( s.recv_buffer() == 0 );
    R ( s.linger() == -1 );
    R ( s.reconnect_ivl() == 100 );
    R ( s.reconnect_ivl_max() == 500 );
    R ( s.backlog() == 100 );

    if (cloudless::zversion::major() == 3) {
        R ( s.max_msg_size() == 10 );
        R ( s.send_hwm() == 1000 );
        R ( s.recv_hwm() == 2000 );
        R ( s.multicast_hops() == 1 );
    } else if (cloudless::zversion::major() == 2) {
        R ( s.max_msg_size() == -1 );
        R ( s.send_hwm() == 2000 );
        R ( s.recv_hwm() == 2000 );
        R ( s.multicast_hops() == -1 );
    }

    R ( s.send_timeout() == -1 );
    R ( s.recv_timeout() == -1 );
    R ( s.ipv4_only() == true );
}
