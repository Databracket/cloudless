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
 * A Message Digest abstraction.
*/

#ifndef CLOUDLESS_CRYPTO_HASH_HPP
#define CLOUDLESS_CRYPTO_HASH_HPP

#include <string>

// Hash ciphers
#include <cryptopp/sha.h>
#include <cryptopp/tiger.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/ripemd.h>

#include <cloudless/detail/export.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    /**
     * A class that abstract Message Digest generation facility.
     *
     * @tparam Hash the hash algorithm that should be used. (e.g., SHA256)
     */

    template<typename Hash>
    class LIBCLOUDLESS_EXPORT hash
    {
    public:

        /**
         * A function to update the context of the underlying Hash algorithm
         * with a block of data.
         *
         * @param value a block of data.
         */
        hash<Hash>&
        update(const std::string& value)
        {
            _M_hd.Update((const byte*)value.data(), value.size());
            return *const_cast<hash<Hash>*>(this);
        }

        /**
         * A function to return the final digest for all the data blocks
         * in the Hash algorithm context.
         *
         * @return the raw message digest.
         */
        std::string
        final()
        {
            byte digest[Hash::DIGESTSIZE];

            _M_hd.Final(digest);
            return std::string((const char*)digest, Hash::DIGESTSIZE);
        }

        /**
         * A static function for offline message digest generation.
         *
         * @param value a block of data.
         * @return a raw message digest.
         */
        static std::string
        digest(const std::string& value)
        {
            Hash hd;
            byte dig[Hash::DIGESTSIZE];

            hd.CalculateDigest(dig, (const byte*)value.data(), value.size());
            return std::string((const char*)dig, Hash::DIGESTSIZE);
        }

        /**
         * A static function for offline verification of data and its digest.
         *
         * @param digest the digest against the data given to verify.
         * @param input the data corresponding to the digest provided.
         * @return true or false.
         */
        static bool
        verify(const std::string& digest, const std::string& input)
        {
            Hash hd;

            return hd.VerifyDigest((const byte*)digest.data(),
                    (const byte*)input.data(), input.size());
        }

    private:
        Hash _M_hd;
    };

} // namespace crypto

} // namespace cloudless

#endif // CLOUDLESS_CRYPTO_HASH_HPP
