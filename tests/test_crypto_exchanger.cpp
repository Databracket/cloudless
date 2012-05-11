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
 * Unit tests for the authenticated key exchange interface; Exchanger.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <cloudless/crypto/dh_modp.hpp>
#include <cloudless/crypto/exchanger.hpp>
#include <cloudless/crypto/hash.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RNT REQUIRE_NOTHROW

using namespace std;

TC ("cloudless/crypto/dh", "Testing Exchanger interface.")
{
    using namespace cloudless;
    using namespace crypto;

    exchanger<SHA256> client; // client == true
    exchanger<SHA256> server(false);

    RNT ( client.generate_keys() );
    RNT ( server.generate_keys() );

    R ( client.agree(server.static_public(), server.ephemeral_public()) == true );
    R ( server.agree(client.static_public(), client.ephemeral_public()) == true );
    R ( client.shared_secret() == server.shared_secret() );
}
