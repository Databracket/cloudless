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
 * A collection of utilities that helps encrypting plaintext.
*/

#ifndef CLOUDLESS_CRYPTO_BLOCK_HPP
#define CLOUDLESS_CRYPTO_BLOCK_HPP

#include <string>

// Block ciphers
#include <cryptopp/aes.h>
#include <cryptopp/serpent.h>
#include <cryptopp/blowfish.h>
#include <cryptopp/camellia.h>
#include <cryptopp/cast.h>
#include <cryptopp/des.h>
#include <cryptopp/gost.h>
#include <cryptopp/idea.h>
#include <cryptopp/mars.h>
#include <cryptopp/rc2.h>
#include <cryptopp/rc5.h>
#include <cryptopp/rc6.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/safer.h>
#include <cryptopp/shacal2.h>
#include <cryptopp/shark.h>
#include <cryptopp/skipjack.h>
#include <cryptopp/twofish.h>
#include <cryptopp/3way.h>
#include <cryptopp/tea.h>

// Encryption modes
#include <cryptopp/modes.h>
#include <cryptopp/gcm.h>
#include <cryptopp/ccm.h>
#include <cryptopp/eax.h>

// Utilities
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;
    using CryptoPP::GCM_TablesOption;

    /**
     * A class to help encrypt plaintext using block ciphers.
     *
     * @tparam Algo an algorithm that represents the combination of a mode and
     * an underlying blockcipher in a specific state. (e.g., CBC_Mode<AES>::Encryption)
     */

    template<typename Algo>
    class LIBCLOUDLESS_EXPORT block
    {
    public:

        /**
         * A constructor that accepts a key and an IV.
         *
         * @param key a cryptographic key.
         * @param iv an initialization vector.
         */
        block(const std::string& key, const std::string& iv) :
            _M_key((byte*)key.data(), key.size()),
            _M_iv((byte*)iv.data(), iv.size())
        {
            _M_algo.SetKeyWithIV(_M_key.BytePtr(), _M_key.SizeInBytes(),
                    _M_iv.BytePtr());
        }

        /**
         * A constructor that accepts only a key for algorithms that don't deal with IVs.
         *
         * @param key a cryptographic key.
         */
        block(const std::string& key) :
            _M_key((byte*)key.data(), key.size())
        {
            _M_algo.SetKey(_M_key.BytePtr(), _M_key.SizeInBytes());
        }

        /**
         * Process a block of plaintext or ciphertext; depends on the state specified.
         * Note: PKCS5 Padding is automatically added or removed if needed.
         *
         * @param value a block of plaintext or ciphertext.
         */
        block<Algo>&
        process(const std::string& value)
        {
            if (!_Mp_stf)
                _Mp_stf.reset(new StreamTransformationFilter(_M_algo,
                            new StringSink(_M_data),
                            StreamTransformationFilter::PKCS_PADDING));

            _Mp_stf->Put((const byte*)value.data(), value.size());
            return *const_cast<block<Algo>*>(this);
        }

        /**
         * Signal the end for processing plaintext or ciphertext blocks
         * and return the final result.
         *
         * @return a string representation of the final plaintext or ciphertext.
         */
        std::string
        final()
        {
            if (_Mp_stf)
                _Mp_stf->MessageEnd();

            return _M_data;
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
        details::shared_ptr<StreamTransformationFilter> _Mp_stf;
        SecByteBlock _M_key;
        SecByteBlock _M_iv;
        std::string _M_data;
    };

    /**
     * A class to help encrypt plaintext using authenticated block ciphers.
     *
     * @tparam Algo an algorithm that represents the combination of a mode and
     * an underlying blockcipher in a specific state. (e.g., GCM<AES>::Decryption)
     */

    template <typename Algo>
    class LIBCLOUDLESS_EXPORT block_auth
    {
    public:

        /**
         * A constrcutor that accepts a key, an IV, and a TAG size.
         *
         * @param key a cryptographic key.
         * @param iv an initialization vector.
         * @param tagsize the TAG size for the MAC used. Defaults to 16. (optional)
         */
        block_auth(const std::string& key, const std::string& iv, int tagsize = 16) :
            _M_key((byte*)key.data(), key.size()),
            _M_iv((byte*)iv.data(), iv.size()), _M_tagsize(tagsize)
        {
            _M_algo.SetKeyWithIV(_M_key.BytePtr(), _M_key.SizeInBytes(),
                    _M_iv.BytePtr(), _M_iv.SizeInBytes());
        }

        /**
         * Encrypt a plaintext block with optional aditional data (ADATA).
         * Note: The first call to this function MUST provide ALL ADATA if any,
         * and all subsequent calls MUST not provide any ADATA.
         *
         * @param value a plaintext block.
         * @param adata additional data or ADATA. Defaults to "". (optional)
         */
        block_auth<Algo>&
        process_encryption(const std::string& value, const std::string& adata = "")
        {
            if (!_Mp_aef)
                _Mp_aef.reset(new AuthenticatedEncryptionFilter(_M_algo,
                            new StringSink(_M_data), false, _M_tagsize));

            // The order of the following ChannelPut() calls are important
            if (adata.size()) {
                _M_adata = true;
                _Mp_aef->ChannelPut(AAD_CHANNEL, (byte*)adata.data(), adata.size());
            }

            _Mp_aef->ChannelPut(DEFAULT_CHANNEL, (byte*)value.data(), value.size());
            return *const_cast<block_auth<Algo>*>(this);
        }

        /**
         * Signal the end of processing plaintext blocks and set the final
         * ciphertext and MAC to be retrieved later.
         */
        block_auth<Algo>&
        final_encryption()
        {
            // The order of the following ChannelMessageEnd() calls are important
            if (_M_adata == true)
                _Mp_aef->ChannelMessageEnd(AAD_CHANNEL);

            _Mp_aef->ChannelMessageEnd(DEFAULT_CHANNEL);

            // Extract the MAC from the end of ciphertext
            _M_mac = _M_data.substr(_M_data.size() - _M_tagsize);
            _M_data = _M_data.substr(0, _M_data.size() - _M_tagsize);

            return *const_cast<block_auth<Algo>*>(this);
        }

        /**
         * Decrypt a ciphertext block with optional additional data (ADATA).
         * Note: The first call to this function MUST provide the MAC and
         * ALL ADATA if any. All subsequent calls MUST not provide either
         * ADATA or the MAC.
         *
         * @param ctext a ciphertext block.
         * @param mac the Message Authentication Code. Defaults to "". (optional)
         * @param adata additional data or ADATA. Defaults to "". (optional)
         */
        block_auth<Algo>&
        process_decryption(const std::string& ctext,
                const std::string& mac = "", const std::string& adata = "")
        {
            if (!_Mp_adf)
                _Mp_adf.reset(new AuthenticatedDecryptionFilter(_M_algo, NULL,
                            AuthenticatedDecryptionFilter::MAC_AT_BEGIN |
                            AuthenticatedDecryptionFilter::THROW_EXCEPTION, _M_tagsize));

            // The order of the following ChannelPut() calls are important
            if (mac.size())
                _Mp_adf->ChannelPut(DEFAULT_CHANNEL, (byte*)mac.data(), mac.size());

            if (adata.size()) {
                _M_adata = true;
                _Mp_adf->ChannelPut(AAD_CHANNEL, (byte*)adata.data(), adata.size());
            }

            _Mp_adf->ChannelPut(DEFAULT_CHANNEL, (byte*)ctext.data(), ctext.size());
            return *const_cast<block_auth<Algo>*>(this);
        }

        /**
         * Signal the end of processing ciphertext blocks and set the final
         * plaintext to be retrieved later.
         */
        block_auth<Algo>&
        final_decryption()
        {
            try {
                // The order of the following ChannelMessageEnd() calls are important
                if (_M_adata == true)
                    _Mp_adf->ChannelMessageEnd(AAD_CHANNEL);

                _Mp_adf->ChannelMessageEnd(DEFAULT_CHANNEL);
            } catch (HashVerificationFilter::HashVerificationFailed&) {
                raise(mac_verification_failed);
            }

            _Mp_adf->SetRetrievalChannel(DEFAULT_CHANNEL);

            size_t n = (size_t)_Mp_adf->MaxRetrievable();

            // Flush data from channel and recover the plaintext
            if (n > 0) {
                _M_data.resize(n);
                _Mp_adf->Get((byte*)_M_data.data(), n);
            }

            return *const_cast<block_auth<Algo>*>(this);
        }

        /**
         * Retrieve the final plaintext or ciphertext.
         *
         * @return a const reference of a string.
         */
        const std::string&
        data() const
        {
            return _M_data;
        }

        /**
         * Retrieve the MAC after finalizing encryption.
         *
         * @return a const reference of a string.
         */
        const std::string&
        mac() const
        {
            return _M_mac;
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
        details::shared_ptr<AuthenticatedEncryptionFilter> _Mp_aef;
        details::shared_ptr<AuthenticatedDecryptionFilter> _Mp_adf;
        SecByteBlock _M_key;
        SecByteBlock _M_iv;
        std::string _M_data;
        std::string _M_mac;
        int _M_tagsize;
        bool _M_adata;
    };

} // namespace crypto

} // namespace cloudless

#endif // CLOUDLESS_CRYPTO_BLOCK_HPP
