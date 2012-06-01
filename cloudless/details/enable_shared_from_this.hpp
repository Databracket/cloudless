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
 * A wrapper around boost::enable_shared_from_this to make the transition
 * to std::enable_shared_from_this transparent.
*/

#ifndef CLOUDLESS_DETAILS_ENABLE_SHARED_FROM_THIS_HPP
#define CLOUDLESS_DETAILS_ENABLE_SHARED_FROM_THIS_HPP

#include <boost/enable_shared_from_this.hpp>

namespace cloudless
{

namespace details
{

    using boost::enable_shared_from_this;

} // namespace details

} // namespace cloudless

#endif // CLOUDLESS_DETAILS_ENABLE_SHARED_FROM_THIS_HPP
