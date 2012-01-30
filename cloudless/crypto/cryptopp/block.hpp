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

#ifndef __CLOUDLESS_CRYPTO_CRYPTOPP_BLOCK_HPP
#define __CLOUDLESS_CRYPTO_CRYPTOPP_BLOCK_HPP

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

// Utilities
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/shared_ptr.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    template<typename Algo>
    class LIBCLOUDLESS_EXPORT block
    {
    public:
        block(const std::string& key_, const std::string& iv_) :
            _M_key((byte*)key_.data(), key_.size()),
            _M_iv((byte*)iv_.data(), iv_.size())
        {
            _M_algo.SetKeyWithIV(_M_key.BytePtr(), _M_key.SizeInBytes(),
                    _M_iv.BytePtr());
        }

        block(const std::string& key_) :
            _M_key((byte*)key_.data(), key_.size())
        {
            _M_algo.SetKey(_M_key.BytePtr(), _M_key.SizeInBytes());
        }

        void
        process(const std::string& value_)
        {
            if (!_Mp_stf)
                _Mp_stf.reset(new StreamTransformationFilter(_M_algo,
                            new StringSink(_M_ciphertext),
                            StreamTransformationFilter::PKCS_PADDING));

            _Mp_stf->Put((const byte*)value_.data(), value_.size());
        }

        std::string
        final()
        {
            if (_Mp_stf)
                _Mp_stf->MessageEnd();

            return _M_ciphertext;
        }

        std::string
        key() const
        {
            return std::string((const char*)_M_key.BytePtr(),
                    _M_key.SizeInBytes());
        }

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
        std::string _M_ciphertext;
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_CRYPTOPP_BLOCK_HPP
