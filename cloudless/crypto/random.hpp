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
 * A secure random number generation facility.
*/

#ifndef CLOUDLESS_CRYPTO_RANDOM_HPP
#define CLOUDLESS_CRYPTO_RANDOM_HPP

#include <string>

#include <cryptopp/osrng.h>

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/noncopyable.hpp>
#include <cloudless/detail/shared_array.hpp>

namespace cloudless
{

namespace crypto
{

    using namespace CryptoPP;

    /**
     * A class to generate secure random numbers.
     *
     * @tparam Size the size of the random block to be generated.
     */

    template <int Size>
    class LIBCLOUDLESS_EXPORT random : detail::noncopyable
    {
    public:

        /**
         * A function to generate random numbers securely.
         *
         * @return a random block.
         */
        static std::string
        generate()
        {
            AutoSeededRandomPool asrp;
            detail::shared_array<byte> rndblck(new byte[Size]);

            asrp.GenerateBlock(rndblck.get(), Size);
            return std::string((const char*)rndblck.get(), Size);
        }
    };

} // namespace crypto

} // namespace cloudless

#endif // CLOUDLESS_CRYPTO_RANDOM_HPP
