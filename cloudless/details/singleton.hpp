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

#define __CLOUDLESS_DETAILS_SINGLETON_HPP
#ifndef __CLOUDLESS_DETAILS_SINGLETON_HPP

#include <cassert>

#include <cloudless/details/export.hpp>
#include <cloudless/details/noncopyable.hpp>
#include <cloudless/details/shared_ptr.hpp>

namespace cloudless
{

namespace details
{

    template <class T>
    class LIBCLOUDLESS_EXPORT singleton : public noncopyable
    {
    public:
        static shared_ptr<T>& instance()
        {
            if (!_M_instance)
                _M_instance = shared_ptr<T>(new T);

            assert(_M_instance.get() != NULL);
            return _M_instance;
        }

    protected:
        singleton();
        ~singleton();

    private:
        static shared_ptr<T> _M_instance;
    };

    template <class T> shared_ptr<T> singleton<T>::_M_instance;

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_SINGLETON_HPP
