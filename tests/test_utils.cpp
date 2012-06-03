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
 * Unit tests for miscellaneous utilities interfaces.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cstring>

#include <cloudless/detail/shared_array.hpp>
#include <cloudless/address.hpp>
#include <cloudless/misc.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

using namespace std;

TC ("cloudless/utils", "Testing utility functions.")
{
    S ("cloudless/address", "Testing address interface.")
    {
        cloudless::address addr(cloudless::protocol::TCP, "cloudless.test", 880);

        R ( (const string&)addr == "tcp://cloudless.test:880" );
        R ( strcmp((const char*)addr, "tcp://cloudless.test:880") == 0 );

        cloudless::address addr1(cloudless::protocol::UDP, cloudless::path::ANY);

        R ( (const string&)addr1 == "udp://*" );
    }

    S ("cloudless/detail/shared_array", "Testing shared_array interface.")
    {
        cloudless::detail::shared_array<char> str(new char[100]);

        for (int i = 0; i < 100; ++i)
            str.get()[i] = (char)i;

        str.reset();

        R ( str.get() == NULL );
    }

    S ("cloudless/misc", "Testing miscellaneous utilities.")
    {
        string teststr("\x41\x42\x43\x43\xff");

        R ( cloudless::from_hex(cloudless::to_hex(teststr)) == teststr );
        R ( cloudless::to_hex(teststr) == "41424343ff" );
        R ( cloudless::from_string<int>(cloudless::to_string(255)) == 255 );
    }
}
