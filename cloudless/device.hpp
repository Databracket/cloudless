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
 * An event-driven communication device.
*/

#ifndef CLOUDLESS_DEVICE_HPP
#define CLOUDLESS_DEVICE_HPP

#include <string>

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/thread.hpp>
#include <cloudless/poller.hpp>
#include <cloudless/edges.hpp>

namespace cloudless
{

    // device

    class LIBCLOUDLESS_EXPORT device : public detail::thread
    {
    public:
        device(const edges& edges);
        virtual ~device() {}

    protected:

        /**
         * A virtual function to be optionally overrided by a child of this class.
         * This function will be executed only once before starting to handle
         * any events.
         */
        virtual void on_init()
        {
            // No default initialization function configured.
            // Feel free to override this function to execute
            // something once before entering on_recv().
        }

        /**
         * A pure virtual function to be overrided by a child of this class.
         * This function will be called on the event one of the edge points
         * received a message.
         *
         * @param edge_id an edge ID.
         * @param edgepoint_id a edgepoint ID.
         */
        virtual void on_recv(const std::string& edge_id, const std::string& edgepoint_id) = 0;

        /**
         * A virtual function to be optionally overrided by a child of this class.
         * This function will be executed only once before the device thread terminates.
         */
        virtual void on_shutdown()
        {
            // No default shutdown function configured.
            // Feel free to override this function to execute
            // right before the destruction.
        }

        /**
         * Get a reference to the edges container.
         *
         * @return a reference to the edges container.
         */
        edges& get_edges() const;

    private:
        void prologue();
        void body();
        void epilogue();

    private:
        edges _M_edges;
        poller _M_poller;
    };

} // namespace cloudless

#endif // CLOUDLESS_DEVICE_HPP
