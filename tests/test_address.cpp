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

#include <cstring>

#include <cloudless/address.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

using namespace std;

TC ("cloudless/address", "Testing address interface.")
{
    cloudless::address addr(cloudless::protocol::TCP, "cloudless.test", 880);

    R ( (const string&)addr == "tcp://cloudless.test:880" );
    R ( strcmp((const char*)addr, "tcp://cloudless.test:880") == 0 );

    cloudless::address addr1(cloudless::protocol::UDP, cloudless::path::ANY);

    R ( (const string&)addr1 == "udp://*" );
}
