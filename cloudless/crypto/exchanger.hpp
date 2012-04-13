/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2011 Databracket, LLC.
 * Copyright (c) 2011 Other contributors as noted in the AUTHORS file
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
 * A collection of utilities that helps exchanging a shared secret securely.
*/

#ifndef __CLOUDLESS_CRYPTO_EXCHANGER_HPP
#define __CLOUDLESS_CRYPTO_EXCHANGER_HPP

#include <string>

#include <cryptopp/secblock.h>
#include <cryptopp/osrng.h>
#include <cryptopp/oids.h>
#include <cryptopp/asn.h>

#include <cloudless/crypto/cryptopp/eccrypto.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/singleton.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/crypto/hash.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

namespace crypto
{

    using CryptoPP::ECP;
    using CryptoPP::FHMQV;
    using CryptoPP::DL_GroupParameters_EC;

    /**
     * A class to help exchange a shared secret securely using FHMQV algorithm.
     *
     * @tparam Hash a hashing algorithm to be used with FHMQV. Defaults to SHA256.
     * @tparam Client specify if FHMQV should act as a client or a server. Defaults to true.
     */

    template <typename Hash = SHA256, bool Client = true>
    class LIBCLOUDLESS_EXPORT exchanger : public details::singleton<exchanger<Hash, Client> >
    {
    public:
        exchanger()
        {
            CryptoPP::OID curve = CryptoPP::ASN1::secp256r1();

            _M_fhmqv.reset(new FHMQV_D(curve, Client));

            _M_spriv.reset(
                    new CryptoPP::SecByteBlock(
                        _M_fhmqv->StaticPrivateKeyLength()));
            _M_spub.reset(
                    new CryptoPP::SecByteBlock(
                        _M_fhmqv->StaticPublicKeyLength()));

            _M_epriv.reset(
                    new CryptoPP::SecByteBlock(
                        _M_fhmqv->EphemeralPrivateKeyLength()));
            _M_epub.reset(
                    new CryptoPP::SecByteBlock(
                        _M_fhmqv->EphemeralPublicKeyLength()));
        }

        /**
         * Agree on a shared secret.
         *
         * @param spub_ the static public key of the other party.
         * @param epub_ the ephemeral public key of the other party.
         * @return whether agreement was successful.
         */
        bool
        agree(const std::string& spub_, const std::string& epub_)
        {
            if (spub_.size() != _M_fhmqv->StaticPublicKeyLength() ||
                    epub_.size() != _M_fhmqv->EphemeralPublicKeyLength())
                throw size_mismatch();

            CryptoPP::SecByteBlock spub((byte*)spub_.data(), spub_.size());
            CryptoPP::SecByteBlock epub((byte*)epub_.data(), epub_.size());

            _M_sharedS.reset(
                    new CryptoPP::SecByteBlock(_M_fhmqv->AgreedValueLength()));

            return _M_fhmqv->Agree(*_M_sharedS, *_M_spriv, *_M_epriv, spub, epub);
        }

        /**
         * Generate a static private key.
         */
        exchanger<Hash, Client>&
        generate_static_private()
        {
            _M_fhmqv->GenerateStaticPrivateKey(_M_rng, _M_spriv->BytePtr());
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Generate a static public key.
         */
        exchanger<Hash, Client>&
        generate_static_public()
        {
            _M_fhmqv->GenerateStaticPublicKey(_M_rng, _M_spriv->BytePtr(),
                    _M_spub->BytePtr());
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Generate a static key pair.
         */
        exchanger<Hash, Client>&
        generate_static_pair()
        {
            _M_fhmqv->GenerateStaticKeyPair(_M_rng, _M_spriv->BytePtr(),
                    _M_spub->BytePtr());
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Generate an ephemeral private key.
         */
        exchanger<Hash, Client>&
        generate_ephemeral_private()
        {
            _M_fhmqv->GenerateEphemeralPrivateKey(_M_rng, _M_epriv->BytePtr());
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Generate an ephemeral public key.
         */
        exchanger<Hash, Client>&
        generate_ephemeral_public()
        {
            _M_fhmqv->GenerateEphemeralPublicKey(_M_rng, _M_epriv->BytePtr(),
                    _M_epub->BytePtr());
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Generate an ephemeral key pair.
         */
        exchanger<Hash, Client>&
        generate_ephemeral_pair()
        {
            _M_fhmqv->GenerateEphemeralKeyPair(_M_rng, _M_epriv->BytePtr(),
                    _M_epub->BytePtr());
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Generate both static and ephemeral key pairs.
         */
        exchanger<Hash, Client>&
        generate_keys()
        {
            return const_cast<exchanger<Hash, Client>*>(this)->
                generate_static_pair().
                generate_ephemeral_pair();
        }

        /**
         * Set a static private key.
         *
         * @param val_ a static private key.
         */
        exchanger<Hash, Client>&
        static_private(const std::string& val_)
        {
            if (val_.size() != _M_fhmqv->StaticPrivateKeyLength())
                throw size_mismatch();

            _M_spriv.reset(
                    new CryptoPP::SecByteBlock(
                        (byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Set a static public key.
         *
         * @param val_ a static public key.
         */
        exchanger<Hash, Client>&
        static_public(const std::string& val_)
        {
            if (val_.size() != _M_fhmqv->StaticPublicKeyLength())
                throw size_mismatch();

            _M_spub.reset(
                    new CryptoPP::SecByteBlock(
                        (byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Set an ephemeral private key.
         *
         * @param val_ an ephemeral private key.
         */
        exchanger<Hash, Client>&
        ephemeral_private(const std::string& val_)
        {
            if (val_.size() != _M_fhmqv->EphemeralPrivateKeyLength())
                throw size_mismatch();

            _M_epriv.reset(
                    new CryptoPP::SecByteBlock(
                        (byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Set an ephemeral public key.
         *
         * @param val_ an ephemeral public key.
         */
        exchanger<Hash, Client>&
        ephemeral_public(const std::string& val_)
        {
            if (val_.size() != _M_fhmqv->EphemeralPublicKeyLength())
                throw size_mismatch();

            _M_epub.reset(
                    new CryptoPP::SecByteBlock(
                        (byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<Hash, Client>*>(this);
        }

        /**
         * Get the static private key.
         *
         * @return the static private key.
         */
        std::string
        static_private() const
        {
            return std::string((char*)_M_spriv->BytePtr(),
                    _M_spriv->SizeInBytes());
        }

        /**
         * Get the static public key.
         *
         * @return the static public key.
         */
        std::string
        static_public() const
        {
            return std::string((char*)_M_spub->BytePtr(),
                    _M_spub->SizeInBytes());
        }

        /**
         * Get the ephemeral private key.
         *
         * @return the ephemeral private key.
         */
        std::string
        ephemeral_private() const
        {
            return std::string((char*)_M_epriv->BytePtr(),
                    _M_epriv->SizeInBytes());
        }

        /**
         * Get the ephemeral public key.
         *
         * @return the ephemeral public key.
         */
        std::string
        ephemeral_public() const
        {
            return std::string((char*)_M_epub->BytePtr(),
                    _M_epub->SizeInBytes());
        }

        /**
         * Get the shared secret both parties agreed on.
         *
         * @return a shared secret.
         */
        std::string
        shared_secret() const
        {
            if (!_M_sharedS)
                throw null_pointer();

            return std::string((char*)_M_sharedS->BytePtr(),
                    _M_sharedS->SizeInBytes());
        }

    private:
        typedef typename FHMQV<ECP, DL_GroupParameters_EC<ECP>::DefaultCofactorOption, Hash>::Domain FHMQV_D;
        typedef details::shared_ptr<FHMQV_D> FHMQV_ptr;
        typedef details::shared_ptr<CryptoPP::SecByteBlock> sbb_ptr;

    private:
        FHMQV_ptr _M_fhmqv;
        sbb_ptr _M_spriv;
        sbb_ptr _M_epriv;
        sbb_ptr _M_spub;
        sbb_ptr _M_epub;
        sbb_ptr _M_sharedS;
        CryptoPP::AutoSeededRandomPool _M_rng;
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_EXCHANGER_HPP
