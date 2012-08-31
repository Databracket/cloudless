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
 * A collection of miscellaneous facilities.
*/

#include <cctype>

#include <cloudless/misc.hpp>

namespace cloudless
{

    std::string
    from_hex(const std::string& hex)
    {
        if (hex.size() % 2 != 0)
            raise(invalid_format);

        std::string res(hex.size() / 2, 0);
        std::string::iterator ptr(res.begin());

        for (std::string::const_iterator it = hex.begin();
                it != hex.end(); it += 2) {
            char x = std::tolower(*it);
            char y = std::tolower(*(it + 1));

            if (!std::isxdigit(x) || !std::isxdigit(y))
                raise(invalid_format);

            x = std::isdigit(x) ? x - '0' : x - 'a' + 10;
            x <<= 4;

            y = std::isdigit(y) ? y - '0' : y - 'a' + 10;

            *ptr++ = x | y;
        }

        return res;
    }

    std::string
    to_hex(const std::string& str)
    {
        static const char* digits("0123456789abcdef");
        std::string res(str.size() * 2, 0);
        std::string::iterator ptr(res.begin());

        for (std::string::const_iterator it = str.begin();
                it != str.end(); ++it) {
            *ptr++ = digits[(unsigned char)*it >> 4];
            *ptr++ = digits[(unsigned char)*it & 15];
        }

        return res;
    }

} // namespace cloudless
