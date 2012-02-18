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

#ifndef __CLOUDLESS_CRYPTO_DH_MODP_HPP
#define __CLOUDLESS_CRYPTO_DH_MODP_HPP

// Big Integer
#include <cryptopp/integer.h>

#include <cloudless/details/export.hpp>
#include <cloudless/details/nonconstructive.hpp>

namespace cloudless
{

namespace crypto
{

    /*
     * RFC 3526
     * 1536-bit MODP Group
     * ID: 5
     */
    struct LIBCLOUDLESS_EXPORT MODP_5 : details::nonconstructive
    {
        static const CryptoPP::Integer p;
        static const CryptoPP::Integer q;
        static const CryptoPP::Integer g;
    };

    /*
     * RFC 3526
     * 2048-bit MODP Group
     * ID: 14
     */
    struct LIBCLOUDLESS_EXPORT MODP_14 : details::nonconstructive
    {
        static const CryptoPP::Integer p;
        static const CryptoPP::Integer q;
        static const CryptoPP::Integer g;
    };

    /*
     * RFC 3526
     * 3072-bit MODP Group
     * ID: 15
     */
    struct LIBCLOUDLESS_EXPORT MODP_15 : details::nonconstructive
    {
        static const CryptoPP::Integer p;
        static const CryptoPP::Integer q;
        static const CryptoPP::Integer g;
    };

    /*
     * RFC 3526
     * 4096-bit MODP Group
     * ID: 16
     */
    struct LIBCLOUDLESS_EXPORT MODP_16 : details::nonconstructive
    {
        static const CryptoPP::Integer p;
        static const CryptoPP::Integer q;
        static const CryptoPP::Integer g;
    };

    /*
     * RFC 3526
     * 6144-bit MODP Group
     * ID: 17
     */
    struct LIBCLOUDLESS_EXPORT MODP_17 : details::nonconstructive
    {
        static const CryptoPP::Integer p;
        static const CryptoPP::Integer q;
        static const CryptoPP::Integer g;
    };

    /*
     * RFC 3526
     * 8192-bit MODP Group
     * ID: 18
     */
    struct LIBCLOUDLESS_EXPORT MODP_18 : details::nonconstructive
    {
        static const CryptoPP::Integer p;
        static const CryptoPP::Integer q;
        static const CryptoPP::Integer g;
    };

} // namespace crypto

} // namespace cloudless

#endif // __CLOUDLESS_CRYPTO_DH_MODP_HPP
