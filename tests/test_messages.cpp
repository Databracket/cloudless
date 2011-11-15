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

#include <string>
#include <cstring>

#include <cloudless/details/zeromq/zmessage.hpp>
#include <cloudless/element.hpp>
#include <cloudless/messages.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

using namespace std;

TC ("cloudless/details/zmessage", "Testing zmessage interface.")
{
    string test_buffer = "test buffer";

    cloudless::details::zmessage zmsg(test_buffer.size());
    cloudless::details::zmessage zmsg_cpy;

    memcpy(zmsg.data(), test_buffer.c_str(), test_buffer.size());

    R ( zmsg.size() == test_buffer.size() );
    R ( bcmp(zmsg.data(), test_buffer.c_str(), zmsg.size()) == 0 );
    R ( zmsg.toString() == test_buffer );

    zmsg_cpy = zmsg;

    R ( zmsg_cpy.size() == zmsg.size() );
    R ( bcmp(zmsg.data(), zmsg_cpy.data(), zmsg.size()) == 0 );
}

TC ("cloudless/element", "Testing element interface.")
{
    string test_buffer = "test buffer";

    {
        cloudless::element e(test_buffer);
        R ( e->toString() == test_buffer );
    }

    {
        cloudless::element e(test_buffer.c_str(), test_buffer.size());
        R ( e->toString() == test_buffer );
    }
}

TC ("cloudless/messages", "Testing messages interface.")
{
    string test_buffer = "test buffer";

    {
        cloudless::messages msgs(test_buffer);
        R ( msgs.head()->toString() == test_buffer );
        R ( msgs.size() == 1 );
    }

    {
        cloudless::messages msgs;
        msgs.push_tail(test_buffer)
            .push_tail(test_buffer + "1")
            .push_head(test_buffer + "2");

        R ( msgs.size() == 3 );
        R ( msgs.pop_tail()->toString() == (test_buffer + "1") );
        R ( msgs.pop_head()->toString() == (test_buffer + "2") );
        R ( msgs.pop_head()->toString() == test_buffer );
        R ( msgs.size() == 0 );
    }

    {
        cloudless::element e(test_buffer);
        cloudless::messages msgs(e);

        msgs.push_head(test_buffer);

        R ( msgs.size() == 2 );
        R ( msgs.tail()->toString() == msgs.head()->toString() );
        R ( msgs.size() == 2 );
    }
}
