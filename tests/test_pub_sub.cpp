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
 * Unit tests for PUB/SUB sockets interfaces.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/pub.hpp>
#include <cloudless/sub.hpp>
#include <cloudless/exceptions.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RTA REQUIRE_THROWS_AS
#define RNT REQUIRE_NOTHROW

TC ("cloudless/socket/pub-sub", "Testing PUB/SUB socket.")
{
    cloudless::context c;
    cloudless::pub s1(c);
    cloudless::sub s2(c);

    RNT ( s1.bind("inproc://pub-sub_test") );
    RNT ( s2.connect("inproc://pub-sub_test") );
    RNT ( s2.subscribe("test") );

    cloudless::message msg("testPUB-SUB");

    R ( s1.send(msg) == true );
    RTA ( s1.recv(msg), cloudless::feature_not_supported );
    RNT ( msg.clear() );
    R ( s2.recv(msg) == true );
    RTA ( s2.send(msg), cloudless::feature_not_supported );
    R ( msg.pop_head() == "testPUB-SUB" );
    R ( msg.size() == 0 );

    RNT ( s1.close() );
    RNT ( s2.close() );
}
