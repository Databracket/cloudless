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

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/context.hpp>
#include <cloudless/message.hpp>
#include <cloudless/socket.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RNT REQUIRE_NOTHROW

TC ("cloudless/socket/req-rep", "Testing REQ/REP socket.")
{
    cloudless::context c;
    cloudless::socket s1(c, cloudless::socket_type::REQ);
    cloudless::socket s2(c, cloudless::socket_type::REP);

    RNT ( s1.bind("inproc://req-rep_test") );
    RNT ( s2.connect("inproc://req-rep_test") );

    cloudless::message msg("testREQ-REP");

    R ( s1.send(msg) == true );
    RNT ( msg.clear() );
    R ( s2.recv(msg) == true );
    R ( msg.pop_head()->toString() == "testREQ-REP" );
    RNT ( msg.push_head("testREQ-REP1") );
    R ( s2.send(msg) == true );
    RNT ( msg.clear() );
    R ( s1.recv(msg) == true );
    R ( msg.pop_tail()->toString() == "testREQ-REP1" );
    R ( msg.size() == 0 );

    RNT ( s1.close() );
    RNT ( s2.close() );
}
