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
 * Unit tests for threads interface.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/details/thread.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RNT REQUIRE_NOTHROW

using namespace std;

struct test_thread : cloudless::details::thread
{
    test_thread() : val(2) {}

    virtual void body()
    {
        val *= 5;

        stop();
    }

public:
    int val;
};

TC ("cloudless/details/thread", "Testing thread interface.")
{
    using cloudless::details::thread;
    using cloudless::details::shared_ptr;

    shared_ptr<test_thread> tt(new test_thread());

    RNT ( tt.reset(new test_thread()) );
    R ( tt->start(false) == true );
    R ( tt->val == 10 );

    RNT ( tt.reset(new test_thread()) );
    RNT ( tt->start() );
    thread::sleep(10); // Allow val to be updated and sync'ed.
    R ( tt->val == 10 );

}
