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
 * Unit tests for device.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>

#include <cloudless/detail/shared_ptr.hpp>
#include <cloudless/detail/thread.hpp>
#include <cloudless/detail/ipod.hpp>
#include <cloudless/device.hpp>
#include <cloudless/socket.hpp>
#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/edges.hpp>

#define TC TEST_CASE
#define R REQUIRE
#define RNT REQUIRE_NOTHROW

using namespace std;

using cloudless::detail::shared_ptr;
using cloudless::detail::thread;
using cloudless::detail::ipod;
using cloudless::device;
using cloudless::edges;
using cloudless::edgepoint;
using cloudless::message;
using cloudless::socket;
using cloudless::context;

struct test_device : public device
{
    test_device(const edges& edges) :
        device(edges)
    {}

    void on_init()
    {
        did_init = true;
        get_edges()["main"]["echo"].psocket->connect("inproc://echo");
    }

    void on_recv(const string& edge_id, const string& edgepoint_id)
    {
        message msg;
        shared_ptr<socket> psocket = get_edges()[edge_id][edgepoint_id].psocket;

        if (psocket->recv(msg))
            ++recv_count;

        if (recv_count >= 1 && (msg.head() == "stop"))
            stop();
        else
        {
            message rep((string)*msg.head() + " pong");
            psocket->send(rep);
        }
    }

    void on_shutdown()
    {
        did_shutdown = true;
        get_edges()["main"]["echo"].psocket->close();
    }

    ipod<bool> did_init;
    ipod<int> recv_count;
    ipod<bool> did_shutdown;
};

TC ("cloudless/device", "Testing device interface.")
{
    socket ps(*context::instance(), cloudless::socket_type::PAIR);
    ps.bind("inproc://echo");

    edgepoint ep;
    edgepoint::point p = { cloudless::socket_type::PAIR };
    ep.add("echo", p);

    edges eds;
    eds.add("main", ep);

    shared_ptr<test_device> td(new test_device(eds));
    RNT ( td->start() );

    thread::sleep(10); // Allow for test_device to actually start
    R ( td->did_init == true );

    message msg("ping");
    R ( ps.send(msg) == true );
    R ( ps.recv(msg) == true );
    R ( msg.head() == "ping pong" );
    R ( td->recv_count == 1 );

    R ( ps.send(msg) == true );
    R ( ps.recv(msg) == true );
    R ( msg.head() == "ping pong pong" );
    R ( td->recv_count == 2 );

    message fmsg("stop");
    R ( ps.send(fmsg) == true);
    thread::sleep(10); // Allow for processing of the stop message
    R ( td->recv_count == 3 );
    R ( td->did_shutdown == true );
    ps.close();
}
