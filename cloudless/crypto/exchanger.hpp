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

#ifndef __CLOUDLESS_CRYPTO_EXCHANGER_HPP
#define __CLOUDLESS_CRYPTO_EXCHANGER_HPP

#include <string>

#include <cryptopp/secblock.h>
#include <cryptopp/osrng.h>
#include <cryptopp/dh.h>
#include <cryptopp/dh2.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/singleton.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

namespace crypto
{

    using std::string;
    using CryptoPP::SecByteBlock;
    using CryptoPP::DH;
    using CryptoPP::DH2;
    using CryptoPP::AutoSeededRandomPool;

    template <typename M>
    class LIBCLOUDLESS_EXPORT exchanger : public details::singleton<exchanger<M> >
    {
    public:
        exchanger()
        {
            _M_dh.reset(new DH());
            _M_dh->AccessGroupParameters().Initialize(M::p, M::q, M::g);
            _M_dh2.reset(new DH2(*_M_dh));

            _M_spriv.reset(new SecByteBlock(_M_dh2->StaticPrivateKeyLength()));
            _M_spub.reset(new SecByteBlock(_M_dh2->StaticPublicKeyLength()));

            _M_epriv.reset(new SecByteBlock(_M_dh2->EphemeralPrivateKeyLength()));
            _M_epub.reset(new SecByteBlock(_M_dh2->EphemeralPublicKeyLength()));
        }

        bool
        agree(const string& spub_, const string& epub_)
        {
            SecByteBlock Ss((byte*)spub_.data(), spub_.size());
            SecByteBlock Se((byte*)epub_.data(), epub_.size());

            _M_sharedS.reset(new SecByteBlock(_M_dh2->AgreedValueLength()));

            return _M_dh2->Agree(*_M_sharedS, *_M_spriv, *_M_epriv, Ss, Se);
        }

        exchanger<M>&
        generate_static_private()
        {
            AutoSeededRandomPool rnd;

            _M_dh2->GenerateStaticPrivateKey(rnd, _M_spriv->BytePtr());
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        generate_static_public()
        {
            AutoSeededRandomPool rnd;

            _M_dh2->GenerateStaticPublicKey(rnd, _M_spriv->BytePtr(),
                    _M_spub->BytePtr());
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        generate_ephemeral_private()
        {
            AutoSeededRandomPool rnd;

            _M_dh2->GenerateEphemeralPrivateKey(rnd, _M_epriv->BytePtr());
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        generate_ephemeral_public()
        {
            AutoSeededRandomPool rnd;

            _M_dh2->GenerateEphemeralPublicKey(rnd, _M_epriv->BytePtr(),
                    _M_epub->BytePtr());
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        static_private(const string& val_)
        {
            if (val_.size() != _M_dh2->StaticPrivateKeyLength())
                throw size_mismatch();

            _M_spriv.reset(new SecByteBlock((byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        static_public(const string& val_)
        {
            if (val_.size() != _M_dh2->StaticPublicKeyLength())
                throw size_mismatch();

            _M_spub.reset(new SecByteBlock((byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        ephemeral_private(const string& val_)
        {
            if (val_.size() != _M_dh2->EphemeralPrivateKeyLength())
                throw size_mismatch();

            _M_epriv.reset(new SecByteBlock((byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<M>*>(this);
        }

        exchanger<M>&
        ephemeral_public(const string& val_)
        {
            if (val_.size() != _M_dh2->EphemeralPublicKeyLength())
                throw size_mismatch();

            _M_epub.reset(new SecByteBlock((byte*)val_.data(), val_.size()));
            return *const_cast<exchanger<M>*>(this);
        }

        string
        static_private() const
        {
            return string((char*)_M_spriv->BytePtr(),
                    _M_spriv->SizeInBytes());
        }

        string
        static_public() const
        {
            return string((char*)_M_spub->BytePtr(),
                    _M_spriv->SizeInBytes());
        }

        string
        ephemeral_private() const
        {
            return string((char*)_M_epriv->BytePtr(),
                    _M_epriv->SizeInBytes());
        }

        string
        ephemeral_public() const
        {
            return string((char*)_M_epub->BytePtr(),
                    _M_epub->SizeInBytes());
        }

        string
        shared_secret() const
        {
            if (!_M_sharedS)
                throw null_pointer();

            return string((char*)_M_sharedS->BytePtr(),
                    _M_sharedS->SizeInBytes());
        }

    private:
        typedef details::shared_ptr<DH> DH_ptr;
        typedef details::shared_ptr<DH2> DH2_ptr;
        typedef details::shared_ptr<SecByteBlock> sbb_ptr;

    private:
        DH_ptr _M_dh;
        DH2_ptr _M_dh2;
        sbb_ptr _M_spriv;
        sbb_ptr _M_epriv;
        sbb_ptr _M_spub;
        sbb_ptr _M_epub;
        sbb_ptr _M_sharedS;
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_EXCHANGER_HPP
