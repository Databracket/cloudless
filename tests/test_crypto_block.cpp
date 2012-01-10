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

#include <cloudless/crypto/random.hpp>
#include <cloudless/crypto/block.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE

using namespace std;

TC ("cloudless/crypto/block", "Testing block cipher interface.")
{
    using namespace cloudless;
    using namespace crypto;

    string key(crypto::random<16>::generate());
    string iv(crypto::random<16>::generate());

    block<CBC_Mode<AES>::Encryption> enc(key, iv);

    R ( enc.key() == key );
    R ( enc.iv() == iv );

    string plaintext("test plain text");
    enc.process(plaintext);

    string ciphertext = enc.final();

    block<CBC_Mode<AES>::Decryption> dec(key, iv);

    R ( dec.key() == key );
    R ( dec.iv() == iv );

    dec.process(ciphertext);

    R ( dec.final() == plaintext );
}
