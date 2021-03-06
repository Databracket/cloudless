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
 * A singleton pattern implementation.
*/

#ifndef CLOUDLESS_DETAIL_SINGLETON_HPP
#define CLOUDLESS_DETAIL_SINGLETON_HPP

#include <cassert>

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/shared_ptr.hpp>

namespace cloudless
{

namespace detail
{

    /**
     * A singleton pattern implementation that can be inherited.
     *
     * @tparam T the type of which a singleton instance will be created for.
     */

    template <typename T>
    class LIBCLOUDLESS_EXPORT singleton
    {
    public:

        /**
         * A static function to return a newly created instance of type T,
         * or return the one already created if it exists.
         *
         * @return a shared pointer of type T.
         */
        static shared_ptr<T> instance()
        {
            if (!_Sp_instance)
                _Sp_instance = shared_ptr<T>(new T);

            assert(_Sp_instance.get() != NULL);
            return _Sp_instance;
        }

    private:
        static shared_ptr<T> _Sp_instance;
    };

    template <typename T> shared_ptr<T> singleton<T>::_Sp_instance;

} // namespace detail

} // namespace cloudless

#endif // CLOUDLESS_DETAIL_SINGLETON_HPP
