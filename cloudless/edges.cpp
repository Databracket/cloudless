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
 * A representation for communication edge points and a container for edges.
*/

#include <cloudless/edges.hpp>
#include <cloudless/exceptions.hpp>

namespace cloudless
{

    // edges

    edges&
    edges::add(const std::string& id, const edgepoint& edgepoint)
    {
        _M_edgepoints[id] = edgepoint;

        return *this;
    }

    edges&
    edges::remove(const std::string& id)
    {
        _M_edgepoints.erase(id);

        return *this;
    }

    edges::iterator
    edges::begin()
    {
        return _M_edgepoints.begin();
    }

    edges::const_iterator
    edges::begin() const
    {
        return _M_edgepoints.begin();
    }

    edges::iterator
    edges::end()
    {
        return _M_edgepoints.end();
    }

    edges::const_iterator
    edges::end() const
    {
        return _M_edgepoints.end();
    }

    edgepoint&
    edges::operator [](const std::string& rhs) const
    {
        const_iterator it = _M_edgepoints.find(rhs);

        if (it == _M_edgepoints.end())
            raise(edgepoint_not_found);

        return const_cast<edgepoint&>(it->second);
    }

    // edgepoint

    edgepoint&
    edgepoint::add(const std::string& id, const edgepoint::point& point)
    {
        _M_points[id] = point;

        return *this;
    }

    edgepoint&
    edgepoint::remove(const std::string& id)
    {
        _M_points.erase(id);

        return *this;
    }

    edgepoint::iterator
    edgepoint::begin()
    {
        return _M_points.begin();
    }

    edgepoint::const_iterator
    edgepoint::begin() const
    {
        return _M_points.begin();
    }

    edgepoint::iterator
    edgepoint::end()
    {
        return _M_points.end();
    }

    edgepoint::const_iterator
    edgepoint::end() const
    {
        return _M_points.end();
    }

    edgepoint::point&
    edgepoint::operator [](const std::string& rhs) const
    {
        const_iterator it = _M_points.find(rhs);

        if (it == _M_points.end())
            raise(point_not_found);

        return const_cast<edgepoint::point&>(it->second);
    }

} // namespace cloudless
