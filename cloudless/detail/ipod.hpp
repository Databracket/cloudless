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
 * A wrapper around POD to auto-initialize upon declaration in class.
*/

#ifndef CLOUDLESS_DETAIL_IPOD_HPP
#define CLOUDLESS_DETAIL_IPOD_HPP

#include <cloudless/detail/export.hpp>

namespace cloudless
{

namespace detail
{

    /**
     * A wrapper around POD types to auto-initialize upon declaration in class.
     *
     * @tparam Tp the POD type template parameter.
     */

    template <typename Tp>
    struct LIBCLOUDLESS_EXPORT ipod
    {

        /**
         * A constructor.
         *
         * @param value an optional value of type POD to be given at initialization.
         */
        ipod(Tp value = Tp()) :
            _M_value(value)
        {}

        /**
         * A casting operator.
         */
        operator Tp()
        {
            return _M_value;
        }

        /**
         * An assignment operator.
         */
        ipod<Tp>&
        operator =(const Tp& rhs)
        {
            _M_value = rhs;
            return *this;
        }

        /**
         * A prefix increment operator.
         */
        ipod<Tp>&
        operator ++()
        {
            ++_M_value;
            return *this;
        }

        /**
         * A postfix increment operator.
         */
        ipod<Tp>
        operator ++(int)
        {
            ipod<Tp> res(_M_value);

            ++(*this);
            return res;
        }

        /**
         * A prefix decrement operator.
         */
        ipod<Tp>&
        operator --()
        {
            --_M_value;
            return *this;
        }

        /**
         * A postfix decrement operator.
         */
        ipod<Tp>
        operator --(int)
        {
            ipod<Tp> res(_M_value);

            --(*this);
            return res;
        }

    private:
        Tp _M_value;
    };

} // namespace detail

} // namespace cloudless

#endif // CLOUDLESS_DETAIL_IPOD_HPP
