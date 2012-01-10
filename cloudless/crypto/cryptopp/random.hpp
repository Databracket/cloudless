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

#ifndef __CLOUDLESS_CRYPTO_CRYPTOPP_RANDOM_HPP
#define __CLOUDLESS_CRYPTO_CRYPTOPP_RANDOM_HPP

#include <string>

#include <cryptopp/osrng.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/noncopyable.hpp>
#include <cloudless/details/shared_array.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    template <int Size>
    class LIBCLOUDLESS_EXPORT random : details::noncopyable
    {
    public:
        static std::string
        generate()
        {
            AutoSeededRandomPool asrp;
            details::shared_array<byte> rndblck(new byte[Size]);

            asrp.GenerateBlock(rndblck.get(), Size);
            return std::string((const char*)rndblck.get(), Size);
        }
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_CRYPTOPP_RANDOM_HPP
