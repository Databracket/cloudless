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
 * A helper to prevent children from having the ability to construct.
*/

#ifndef CLOUDLESS_DETAIL_NONCONSTRUCTIVE_HPP
#define CLOUDLESS_DETAIL_NONCONSTRUCTIVE_HPP

namespace cloudless
{

namespace detail
{

    /**
     * A helper to prevent children from having the ability to construct.
     */

    class nonconstructive
    {
        nonconstructive();
        ~nonconstructive();
    };

} // namespace detail

} // namespace cloudless

#endif // CLOUDLESS_DETAIL_NONCONSTRUCTIVE_HPP
