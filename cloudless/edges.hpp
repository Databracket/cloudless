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

#ifndef CLOUDLESS_EDGES_HPP
#define CLOUDLESS_EDGES_HPP

#include <string>
#include <map>

#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/details/export.hpp>
#include <cloudless/details/ipod.hpp>
#include <cloudless/context.hpp>
#include <cloudless/socket.hpp>

namespace cloudless
{

    // Forward declaration
    struct edgepoint;

    /**
     * A named container structure for edge points.
     */

    struct LIBCLOUDLESS_EXPORT edges
    {

        /**
         * An iterator for the map of ID's and edgepoints.
         */
        typedef std::map<std::string, edgepoint>::iterator iterator;

        /**
         * A const iterator for the map of ID's and edgepoints.
         */
        typedef std::map<std::string, edgepoint>::const_iterator const_iterator;

        /**
         * A function to add edgepoints to the container.
         *
         * @param id a string that represents an ID to be associated with an edgepoint.
         * @param edgepoint an instance of edgepoint.
         */
        edges& add(const std::string& id, const edgepoint& edgepoint);

        /**
         * A function to remove an edgepoint from the container.
         *
         * @param id a string of the ID associated with the edgepoint to be removed.
         */
        edges& remove(const std::string& id);

        /**
         * Return iterator to the beginning.
         *
         * @return an iterator referring to the first element in the container.
         */
        iterator begin();

        /**
         * A const version of the begin() function.
         */
        const_iterator begin() const;

        /**
         * Return iterator to the end.
         *
         * @return an iterator referring to the last element in the container.
         */
        iterator end();

        /**
         * A const version of the end() function.
         */
        const_iterator end() const;

        /**
         * An operator to access the different edgepoints added earlier via add().
         * If no edgepoint found associated with the given ID an edgepoint_not_found()
         * exception will be thrown.
         *
         * @param rhs the ID associated with the edgepoint in question.
         * @return a reference of the edgepoint if found.
         */
        edgepoint& operator [](const std::string& rhs) const;

    private:
        std::map<std::string, edgepoint> _M_edgepoints;
    };

    /**
     * Edge point structure that stores all information about sockets (aka. points)
     * to be used or initialized at a later time.
     */

    struct LIBCLOUDLESS_EXPORT edgepoint
    {

        /**
         * A structure to group all about a single point (group of 0MQ sockets).
         */

        struct point
        {
            /**
             * A 0MG socket type value (e.g., cloudless::socket_type::XREQ)
             */
            details::ipod<int> socket_type;

            /**
             * A shared_ptr of a 0MQ context.
             */
            details::shared_ptr<context> pcontext;

            /**
             * A shared_ptr of a 0MQ socket.
             */
            details::shared_ptr<socket> psocket;
        };

        /**
         * An iterator for the map of ID's and points.
         */
        typedef std::map<std::string, point>::iterator iterator;

        /**
         * A const iterator for the map of ID's and points.
         */
        typedef std::map<std::string, point>::const_iterator const_iterator;

        /**
         * A function to add a point to the container.
         *
         * @param id a string of the ID to be associated with the point.
         * @param point a group of information about a single point.
         */
        edgepoint& add(const std::string& id, const point& point);

        /**
         * A function to remove a point from the container.
         *
         * @param id a string of the ID associated with the point to be removed.
         */
        edgepoint& remove(const std::string& id);

        /**
         * Return iterator to the beginning.
         *
         * @return an iterator referring to the first element in the container.
         */
        iterator begin();

        /**
         * A const version of the begin() function.
         */
        const_iterator begin() const;

        /**
         * Return iterator to the end.
         *
         * @return an iterator referring to the last element in the container.
         */
        iterator end();

        /**
         * A const version of the end() function.
         */
        const_iterator end() const;

        /**
         * An operator to access the different points added earlier via add().
         * If no point found associated with the given ID a point_not_found()
         * exception will be thrown.
         *
         * @param rhs the ID associated with the point in question.
         * @return a reference to the point associated with the given ID.
         */
        point& operator [](const std::string& rhs) const;

    private:
        std::map<std::string, point> _M_points;
    };

} // namespace cloudless

#endif // CLOUDLESS_EDGES_HPP
