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
 * Unit tests for DEALER/ROUTER socket interfaces.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/dealer.hpp>
#include <cloudless/router.hpp>
#include <cloudless/req.hpp>
#include <cloudless/rep.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RTA REQUIRE_THROWS_AS
#define RNT REQUIRE_NOTHROW

TC ("cloudless/socket/dealer-router", "Testing DEALER/ROUTER socket.")
{
    cloudless::context c;
    cloudless::dealer xreq(c);
    cloudless::router xrep(c);
    cloudless::req req(c);
    cloudless::rep rep(c);

    // REQ <-> XREP <- DEVICE -> XREQ <-> REP
    RNT ( xreq.bind("inproc://xreq_test") );
    RNT ( xrep.bind("inproc://xrep_test") );
    RNT ( req.connect("inproc://xrep_test") );
    RNT ( rep.connect("inproc://xreq_test") );

    cloudless::message msg;

    // Send message down the device
    R ( req.send(msg.push_head("testXREP-XREQ")) == true );
    R ( xrep.recv(msg) == true );
    R ( xreq.send(msg) == true );
    R ( rep.recv(msg) == true );

    // Keep the address of REQ received and discard the message
    R ( msg.pop_tail() == "testXREP-XREQ" );

    // Send reply back through the device
    R ( rep.send(msg.push_tail("testXREQ-XREP")) == true );
    R ( xreq.recv(msg) == true );
    R ( xrep.send(msg) == true );
    R ( req.recv(msg) == true );

    R ( msg.head() == "testXREQ-XREP" );
    R ( msg.size() == 1 );

    RNT ( req.close() );
    RNT ( rep.close() );
    RNT ( xreq.close() );
    RNT ( xrep.close() );
}
