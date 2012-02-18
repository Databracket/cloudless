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

#include <iostream>
#include <sstream>
#include <string>

#include <cloudless/crypto/dh_modp.hpp>
#include <cloudless/crypto/exchanger.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RNT REQUIRE_NOTHROW

using namespace std;

TC ("cloudless/crypto/dh", "Testing Exchanger interface.")
{
    using namespace cloudless;
    using namespace crypto;

    exchanger<MODP_14> inst;
    exchanger<MODP_14>* instp = exchanger<MODP_14>::instance();

    RNT ( inst.generate_static_private()
            .generate_static_public()
            .generate_ephemeral_private()
            .generate_ephemeral_public() );

    RNT ( instp->generate_static_private()
            .generate_static_public()
            .generate_ephemeral_private()
            .generate_ephemeral_public() );

    R ( inst.agree(instp->static_public(), instp->ephemeral_public()) == true );
    R ( instp->agree(inst.static_public(), inst.ephemeral_public()) == true );
    R ( inst.shared_secret() == instp->shared_secret() );
}
