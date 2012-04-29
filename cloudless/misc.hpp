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
 * A collection of miscellaneous facilities.
*/

#ifndef __CLOUDLESS_MISC_HPP
#define __CLOUDLESS_MISC_HPP

#include <string>
#include <sstream>

#include <cloudless/details/export.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    /**
     * Convert a hexadecimal string to a string of bytes.
     *
     * @param hex_ a hexadecimal string.
     * @return a string of bytes.
     */
    std::string LIBCLOUDLESS_EXPORT from_hex(const std::string& hex_);

    /**
     * Convert a string of bytes to a hexadecimal string.
     *
     * @param str_ a string of bytes.
     * @return a hexadecimal string.
     */
    std::string LIBCLOUDLESS_EXPORT to_hex(const std::string& str_);

    /**
     * Convert to a type T from a string.
     *
     * @tparam T the generic type the string will be converted to.
     * @param str_ a std::string.
     * @param fully_ whether to throw an exception if the string isn't fully parsed.
     * @param exceptions_ whether exceptions should be thrown on a format error.
     * @return an instance of T.
     */
    template <typename T>
    T
    LIBCLOUDLESS_EXPORT from_string(const std::string& str_, bool fully_ = true,
            bool exceptions_ = true)
    {
        std::istringstream iss(str_);
        T res;

        iss >> std::boolalpha >> res;

        if (fully_ && !iss.eof())
            raise(not_fully_parsed);
        else if (exceptions_ && !iss) // operator! checks (failbit|badbit)
            raise(invalid_format);

        return res;
    }

    /**
     * Convert a generic type T to a string.
     *
     * @tparam T the generic type that will be converted to a string.
     * @param t_ an instance of type T.
     * @return a std::string of converted value from t_.
     */
    template <typename T>
    std::string
    LIBCLOUDLESS_EXPORT to_string(const T& t_)
    {
        std::ostringstream oss;

        oss << std::boolalpha << t_;
        return oss.str();
    }

} // namespace cloudless

#endif // __CLOUDLESS_MISC_HPP
