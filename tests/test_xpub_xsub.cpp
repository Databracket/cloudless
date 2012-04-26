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
 * Unit tests for XPUB/XSUB sockets interfaces.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/pub.hpp>
#include <cloudless/sub.hpp>
#include <cloudless/xpub.hpp>
#include <cloudless/xsub.hpp>
#include <cloudless/exceptions.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RTA REQUIRE_THROWS_AS
#define RNT REQUIRE_NOTHROW

TC ("cloudless/socket/xpub-xsub", "Testing XPUB/XSUB socket.")
{
    cloudless::context c;
    cloudless::xpub p1(c);
    cloudless::xsub s1(c);
    cloudless::pub p2(c);
    cloudless::sub s2(c);

    // SUB <- XPUB <- DEVICE -> XSUB <- PUB
    RNT ( p1.bind("inproc://xpub_test") );
    RNT ( s1.bind("inproc://xsub_test") );
    RNT ( p2.connect("inproc://xsub_test") );
    RNT ( s2.connect("inproc://xpub_test") );

    RNT ( s2.subscribe("test") );

    cloudless::message msg;

    // Pass the subscription upstream
    R ( p1.recv(msg) == true );
    R ( s1.send(msg) == true );

    // If transport is not INPROC a wait is a must
    // to allow the publisher to get the subscription.
    // e.g., sleep(1)

    R ( p2.send(msg.push_head("testXPUB-XSUB")) == true );

    // Pass the message downstream through the device
    R ( s1.recv(msg) == true );
    R ( p1.send(msg) == true );

    R ( s2.recv(msg) == true );
    R ( msg.pop_head()->toString() == "testXPUB-XSUB" );
    R ( msg.size() == 0 );

    RNT ( p2.close() );
    RNT ( s2.close() );
    RNT ( p1.close() );
    RNT ( s1.close() );
}
