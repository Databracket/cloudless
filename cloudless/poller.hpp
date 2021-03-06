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
 * A polling mechanism based on 0MQ polling abstraction.
*/

#ifndef CLOUDLESS_POLLER_HPP
#define CLOUDLESS_POLLER_HPP

#include <string>
#include <vector>
#include <map>

#include <cloudless/detail/noncopyable.hpp>
#include <cloudless/detail/export.hpp>
#include <cloudless/detail/ipod.hpp>
#include <cloudless/pollitem.hpp>

namespace cloudless
{

    /**
     * A container for pollitems that polls over all of them.
     */

    class LIBCLOUDLESS_EXPORT poller : detail::noncopyable
    {
    public:

        /**
         * Add a pollitem to the pool to be monitored.
         *
         * @param name a std::string of a name to be associated with the pollitem.
         * @param item a pollitem.
         */
        poller& add(const std::string& name, const pollitem& item);

        /**
         * Poll on all pollitems in the container.
         * Block until an event fires or timeout and return. If timeout was set
         * to -1 then the function will block indefinitely until an event fires.
         *
         * @param timeout a timeout period in milliseconds. If -1 the function
         * will block indefinitely, if 0 the function will return immediately.
         * @return whether any events fired.
         */
        bool poll(long timeout = 300) const;

        /**
         * Get the name associated with the pollitem that has a triggered event.
         * If an empty string was returned then there is no pollitems with
         * registered triggered events.
         *
         * @return the pollitem's name.
         */
        const std::string& get_triggered() const;

        /**
         * Get a pollitem from the container by the name associated with it.
         *
         * @param rhs name string associated with the pollitem.
         * @return a constant reference of the pollitem if found. Otherwise
         * exception poll_not_found() will be raised.
         */
        const pollitem& operator [](const std::string& rhs) const;

    private:
        typedef std::map<std::string, unsigned int> items_indexes;
        items_indexes _M_indexes;
        std::vector<pollitem> _M_items;
        detail::ipod<unsigned int> _M_ctr;
    };

} // namespace cloudless

#endif // CLOUDLESS_POLLER_HPP
