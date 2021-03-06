/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket LLC.
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
 * An abstraction for stream ciphers.
*/

#ifndef CLOUDLESS_CRYPTO_STREAM_HPP
#define CLOUDLESS_CRYPTO_STREAM_HPP

#include <string>

// Stream ciphers
#include <cryptopp/panama.h>
#include <cryptopp/sosemanuk.h>
#include <cryptopp/salsa.h>
#include <cryptopp/seal.h>

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/shared_array.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    /**
     * A class to encrypt data with a stream cipher.
     *
     * @tparam Algo an algorithm that represents the combination of a
     * stream cipher algorithm in a specific state. (e.g., Sosemanuk::Decryption)
     */

    template<typename Algo>
    class LIBCLOUDLESS_EXPORT stream
    {
    public:

        /**
         * A constructor that accepts a key and an IV.
         *
         * @param key a cryptographic key.
         * @param iv an initialization vector.
         */
        stream(const std::string& key, const std::string& iv) :
            _M_key((byte*)key.data(), key.size()),
            _M_iv((byte*)iv.data(), iv.size())
        {
            _M_algo.SetKeyWithIV(_M_key.BytePtr(), _M_key.SizeInBytes(),
                    _M_iv.BytePtr());
        }

        /**
         * A constructor that accepts only a key for algorithms that don't require IVs.
         *
         * @param key a cryptographic key.
         */
        stream(const std::string& key) :
            _M_key((byte*)key.data(), key.size())
        {
            _M_algo.SetKey(_M_key.BytePtr(), _M_key.SizeInBytes());
        }

        /**
         * Process a block of plaintext or ciphertext; depends on the state specified.
         *
         * @param value a block of plaintext or ciphertext.
         * @return the result of the operation on the state specified.
         */
        std::string
        process(const std::string& value)
        {
            detail::shared_array<byte> buffer(new byte[value.size()]);

            _M_algo.ProcessData(buffer.get(), (byte*)value.data(), value.size());

            return std::string((const char*)buffer.get(), value.size());
        }

        /**
         * Get the key.
         *
         * @return a string representation for the key.
         */
        std::string
        key() const
        {
            return std::string((const char*)_M_key.BytePtr(),
                    _M_key.SizeInBytes());
        }

        /**
         * Get the IV.
         *
         * @return a string representation for the IV.
         */
        std::string
        iv() const
        {
            return std::string((const char*)_M_iv.BytePtr(),
                    _M_iv.SizeInBytes());
        }

    private:
        Algo _M_algo;
        SecByteBlock _M_key;
        SecByteBlock _M_iv;
    };

} // namespace crypto

} // namespace cloudless

#endif // CLOUDLESS_CRYPTO_STREAM_HPP
