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
 * Unit tests for edges and edgepoints.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <vector>
#include <string>

#include <cloudless/socket.hpp>
#include <cloudless/edges.hpp>
#include <cloudless/exceptions.hpp>

#define TC TEST_CASE
#define R REQUIRE
#define RNT REQUIRE_NOTHROW
#define RTA REQUIRE_THROWS_AS

TC ("cloudless/edges", "Testing edges and edgepoint interface.")
{
    cloudless::edgepoint::point p_int = { cloudless::socket_type::PAIR };
    cloudless::edgepoint::point p_ext = { cloudless::socket_type::PAIR };
    cloudless::edgepoint ep;

    RNT ( ep.add("internal", p_int) );
    RNT ( ep.add("external", p_ext) );

    std::vector<std::string> test_vals;
    test_vals.push_back("external");
    test_vals.push_back("internal");
    std::vector<std::string>::iterator tv_it = test_vals.begin();

    for (cloudless::edgepoint::iterator it = ep.begin(); it != ep.end(); ++it)
    {
        R ( it->first == *tv_it++ );
    }

    RNT ( ep.remove("internal") );
    RNT ( ep.remove("external") );
    RTA ( ep["internal"], cloudless::point_not_found );
    RTA ( ep["external"], cloudless::point_not_found );

    cloudless::edges eds;

    RNT ( eds.add("cloud_edge", ep) );

    for (cloudless::edges::iterator it = eds.begin(); it != eds.end(); ++it)
    {
        R ( it->first == "cloud_edge" );
    }

    RNT ( eds.remove("cloud_edge") );
    RTA ( eds["cloud_edge"], cloudless::edgepoint_not_found );
}
