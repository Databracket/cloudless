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

#ifndef __CLOUDLESS_CRYPTO_CRYPTOPP_STREAM_HPP
#define __CLOUDLESS_CRYPTO_CRYPTOPP_STREAM_HPP

#include <string>

// Stream ciphers
#include <cryptopp/panama.h>
#include <cryptopp/sosemanuk.h>
#include <cryptopp/salsa.h>
#include <cryptopp/seal.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/shared_array.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    template<typename Algo>
    class LIBCLOUDLESS_EXPORT stream
    {
    public:
        stream(const std::string& key_, const std::string& iv_) :
            _M_key((byte*)key_.data(), key_.size()),
            _M_iv((byte*)iv_.data(), iv_.size())
        {
            _M_algo.SetKeyWithIV(_M_key.BytePtr(), _M_key.SizeInBytes(),
                    _M_iv.BytePtr());
        }

        stream(const std::string& key_) :
            _M_key((byte*)key_.data(), key_.size())
        {
            _M_algo.SetKey(_M_key.BytePtr(), _M_key.SizeInBytes());
        }

        std::string
        process(const std::string& value_)
        {
            details::shared_array<byte> buffer(new byte[value_.size()]);

            _M_algo.ProcessData(buffer.get(), (byte*)value_.data(), value_.size());

            return std::string((const char*)buffer.get(), value_.size());
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
        SecByteBlock _M_key;
        SecByteBlock _M_iv;
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_CRYPTOPP_STREAM_HPP
