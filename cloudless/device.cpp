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
 * An event-driven communication device.
*/

#include <cloudless/detail/shared_ptr.hpp>
#include <cloudless/device.hpp>
#include <cloudless/pollitem.hpp>

namespace cloudless
{

    // device

    device::device(const edges& edges) :
        detail::thread(), _M_edges(edges)
    {}

    edges&
    device::get_edges() const
    {
        return const_cast<edges&>(_M_edges);
    }

    void
    device::prologue()
    {
        edges::iterator edges_it;

        // Loop over all edges
        for (edges_it = _M_edges.begin();
                edges_it != _M_edges.end(); ++edges_it)
        {
            edgepoint::iterator point_it;

            // Loop over all edge points
            for (point_it = edges_it->second.begin();
                    point_it != edges_it->second.end(); ++point_it)
            {
                // Check if a 0MQ context is specified, if not use a global one
                if (!point_it->second.pcontext)
                    point_it->second.pcontext =
                        detail::shared_ptr<context>(context::instance());

                // Initialize a 0MQ socket for each point
                point_it->second.psocket = detail::shared_ptr<socket>(
                        new socket(*point_it->second.pcontext,
                            point_it->second.socket_type));

                // Add pollitem for each socket to a poller
                _M_poller.add(edges_it->first + point_it->first,
                        point_it->second.psocket->poll_item()
                            .register_event(poll_events::IN)
                            );
            }
        }

        on_init();
    }

    void
    device::body()
    {
        if (_M_poller.poll(-1))
        {
            edges::iterator edges_it;
            std::string pollitem_name = _M_poller.get_triggered();

            // Loop over all edges
            for (edges_it = _M_edges.begin();
                    edges_it != _M_edges.end(); ++edges_it)
            {
                // Get the first part of a pollitem_name; edge ID
                std::string edge_id(pollitem_name.c_str(), edges_it->first.size());

                // Move early to the next edge if this one doesn't match
                if (edge_id != edges_it->first)
                    continue;

                edgepoint::iterator point_it;

                // Loop over all edge points
                for (point_it = edges_it->second.begin();
                        point_it != edges_it->second.end(); ++point_it)
                {
                    // Move to the next edge point if this one doesn't match
                    if (pollitem_name != (edges_it->first + point_it->first))
                        continue;

                    // Pass edge's ID and point's ID to on_recv()
                    on_recv(edges_it->first, point_it->first);
                    return;
                }
            }
        }
    }

    void
    device::epilogue()
    {
        on_shutdown();
    }

} // namespace cloudless
