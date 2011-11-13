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

using namespace std;

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

TC ("cloudless/details/zmessage", "Testing all aspects of zmessage interface.")
{
    using namespace cloudless;

    string test_buffer = "test buffer";

    details::zmessage zmsg(test_buffer.size());

    memcpy(zmsg.data(), test_buffer.c_str(), test_buffer.size());

    R ( zmsg.size() == test_buffer.size() );
    R ( bcmp(zmsg.data(), test_buffer.c_str(), zmsg.size()) == 0 );
}
