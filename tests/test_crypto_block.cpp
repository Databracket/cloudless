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
 * Unit tests for authenticated and unauthenticated block ciphers interfaces.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>

#include <cloudless/crypto/random.hpp>
#include <cloudless/crypto/block.hpp>

#define TC TEST_CASE
#define S SECTION
#define R REQUIRE
#define RNT REQUIRE_NOTHROW

using namespace std;

TC ("cloudless/crypto/block", "Testing block cipher interface.")
{
    using namespace cloudless;
    using namespace crypto;

    S ("cloudless/crypto/block/unauthenticated", "Testing unauthenticated modes interface.")
    {
        string key(crypto::random<16>::generate());
        string iv(crypto::random<16>::generate());
        string plaintext("test plain text");

        // Encrypt

        block<CBC_Mode<AES>::Encryption> enc(key, iv);

        R ( enc.key() == key );
        R ( enc.iv() == iv );

        enc.process(plaintext);

        string ciphertext = enc.final();

        // Decrypt

        block<CBC_Mode<AES>::Decryption> dec(key, iv);

        R ( dec.key() == key );
        R ( dec.iv() == iv );

        dec.process(ciphertext);

        R ( dec.final() == plaintext );
    }

    S ("cloudless/crypto/block/authenticated", "Testing authenticated modes interface.")
    {
        string key(crypto::random<32>::generate());
        string iv(crypto::random<16>::generate());
        string pdata_b1("test plain text block #01");
        string pdata_b2("test plain text block #02");
        string adata("ADDITIONAL DATA");

        // Encrypt

        block_auth<GCM<Serpent, GCM_64K_Tables>::Encryption> enc(key, iv, 16 /* i.e., 128-bits TAG */);

        R ( enc.key() == key );
        R ( enc.iv() == iv );

        RNT ( enc.process_encryption(pdata_b1, adata)
                .process_encryption(pdata_b2)
                .final_encryption() );

        string cdata = enc.data();
        string mac = enc.mac();

        R ( mac.size() == 16 );

        // Decrypt

        block_auth<GCM<Serpent, GCM_2K_Tables>::Decryption> dec(key, iv);

        R ( dec.key() == key );
        R ( dec.iv() == iv );

        RNT ( dec.process_decryption(cdata, mac, adata)
                .final_decryption() );

        R ( dec.data() == (pdata_b1 + pdata_b2) );
    }
}
