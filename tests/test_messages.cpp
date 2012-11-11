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
 * Unit tests for messages interface.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>
#include <cstring>

#include <cloudless/detail/zeromq/zmessage.hpp>
#include <cloudless/element.hpp>
#include <cloudless/message.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

using namespace std;

TC ("cloudless/detail/zmessage", "Testing zmessage interface.")
{
    string test_buffer = "test buffer";

    cloudless::detail::zmessage zmsg(test_buffer.size());
    cloudless::detail::zmessage zmsg_cpy;

    memcpy(zmsg.data(), test_buffer.c_str(), test_buffer.size());

    R ( zmsg.size() == test_buffer.size() );
    R ( bcmp(zmsg.data(), test_buffer.c_str(), zmsg.size()) == 0 );
    R ( zmsg == test_buffer );

    zmsg_cpy = zmsg;

    R ( zmsg_cpy.size() == zmsg.size() );
    R ( bcmp(zmsg.data(), zmsg_cpy.data(), zmsg.size()) == 0 );
}

TC ("cloudless/element", "Testing element interface.")
{
    string test_buffer = "test buffer";

    {
        cloudless::element e(test_buffer);
        R ( e == test_buffer );
    }

    {
        cloudless::element e(test_buffer.c_str(), test_buffer.size());
        R ( e == test_buffer );
    }

    {
        cloudless::element e(test_buffer);
        R ( (string)e == test_buffer );
    }
}

TC ("cloudless/message", "Testing message interface.")
{
    string test_buffer = "test buffer";

    {
        cloudless::message msg(test_buffer);
        R ( msg.head() == test_buffer );
        R ( msg.size() == 1 );
    }

    {
        cloudless::message msg;
        msg.push_tail(test_buffer)
            .push_tail(test_buffer + "1")
            .push_head(test_buffer + "2");

        R ( msg.size() == 3 );
        R ( msg.pop_tail() == (test_buffer + "1") );
        R ( msg.pop_head() == (test_buffer + "2") );
        R ( msg.pop_head() == test_buffer );
        R ( msg.size() == 0 );
    }

    {
        cloudless::element e(test_buffer);
        cloudless::message msg(e);

        msg.push_head(test_buffer);

        R ( msg.size() == 2 );
        R ( msg.tail() == (string)*msg.head() );
        R ( msg.size() == 2 );
    }
}
