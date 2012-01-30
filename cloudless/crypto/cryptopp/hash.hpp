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

#ifndef __CLOUDLESS_CRYPTO_CRYPTOPP_HASH_HPP
#define __CLOUDLESS_CRYPTO_CRYPTOPP_HASH_HPP

#include <string>

// Hash ciphers
#include <cryptopp/sha.h>
#include <cryptopp/tiger.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/ripemd.h>

#include <cloudless/details/export.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    template<typename Hash>
    class LIBCLOUDLESS_EXPORT hash
    {
    public:
        void
        update(const std::string& value_)
        {
            _M_hd.Update((const byte*)value_.data(), value_.size());
        }

        std::string
        final()
        {
            byte digest[Hash::DIGESTSIZE];

            _M_hd.Final(digest);
            return std::string((const char*)digest, Hash::DIGESTSIZE);
        }

        static std::string
        digest(const std::string& value_)
        {
            Hash hd;
            byte dig[Hash::DIGESTSIZE];

            hd.CalculateDigest(dig, (const byte*)value_.data(), value_.size());
            return std::string((const char*)dig, Hash::DIGESTSIZE);
        }

        static bool
        verify(const std::string& digest_, const std::string& input_)
        {
            Hash hd;

            return hd.VerifyDigest((const byte*)digest_.data(),
                    (const byte*)input_.data(), input_.size());
        }

    private:
        Hash _M_hd;
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_CRYPTOPP_HASH_HPP
