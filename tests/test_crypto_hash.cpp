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

#include <cloudless/crypto/hash.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

using namespace std;

TC ("cloudless/crypto/hash", "Testing message digest interface.")
{
    using namespace cloudless;
    using namespace crypto;

    string plaintext("test plain text");

    string digest = hash<SHA>::digest(plaintext);

    hash<SHA> md;

    md.update(plaintext);

    R ( hash<SHA>::verify(md.final(), plaintext) == true );
    R ( hash<SHA>::verify(digest, plaintext) == true );
}
