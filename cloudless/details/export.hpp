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

#ifndef __CLOUDLESS_DETAILS_EXPORT_HPP
#define __CLOUDLESS_DETAILS_EXPORT_HPP

#include <cloudless/details/platform.hpp>

#ifdef LIBCLOUDLESS_STATIC_LIB
#  define LIBCLOUDLESS_EXPORT
#else
#  ifdef _WIN32
#    ifdef _MSC_VER
#      define LIBCLOUDLESS_EXPORT __declspec(dllexport)
#    else
#      ifdef DLL_EXPORT
#        define LIBCLOUDLESS_EXPORT __declspec(dllexport)
#      else
#        define LIBCLOUDLESS_EXPORT
#      endif
#    endif
#  else
#    define LIBCLOUDLESS_EXPORT __attribute__ ((visibility("default")))
#  endif
#endif

#endif // __CLOUDLESS_DETAILS_EXPORT_HPP
