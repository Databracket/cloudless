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
 * Example #2
*/

#include <iostream>
#include <string>

#include <cloudless/context.hpp>
#include <cloudless/socket.hpp>
#include <cloudless/message.hpp>
#include <cloudless/edges.hpp>
#include <cloudless/device.hpp>
#include <cloudless/detail/shared_ptr.hpp>

using namespace std;

using cloudless::detail::shared_ptr;
using cloudless::detail::ipod;
using cloudless::device;
using cloudless::edges;
using cloudless::edgepoint;
using cloudless::message;
using cloudless::socket;
using cloudless::context;

struct echo : device
{
    echo(const edges& edges) :
        device(edges)
    {}

    virtual ~echo()
    {
        // Here we wait on the thread to finish before destroying
        // the object to make sure the thread is not using members
        // of an object that no longer exist.
        wait();
    }

    // This function is called only once upon device start.
    void on_init()
    {
        // Connect point loopback::echo (edge::point) to the socket
        // listening on the INPROC address "inproc://echo".
        get_edges()["loopback"]["echo"].psocket->connect("inproc://echo");
    }

    // This function is called for every message
    // that become available on the socket.
    void on_recv(const string& edge_id, const string& edgepoint_id)
    {
        // Get a reference to the point addressed as edge_id::edgepoint_id.
        edgepoint::point& point = get_edges()[edge_id][edgepoint_id];
        message msg;

        // Block on the socket till a message arrives.
        if (point.psocket->recv(msg))
        {
            cout << "Received a message: "
                << (string)msg.head() << endl;
        }
    }

    // This function is called only once upon device shutdown.
    void on_shutdown()
    {
        // This step is unnecessary and only here for illustration.
        // All sockets in Cloudless will close before they are
        // destructed.
        get_edges()["loopback"]["echo"].psocket->close();
    }
};

int main()
{
    // It is a must to use the same 0MQ context
    // between INPROC sockets and therefore we use the
    // default global 0MQ context instead of creating a new one.
    socket echo_socket(context::instance(), cloudless::socket_type::PAIR);
    echo_socket.bind("inproc://echo");

    edgepoint loopback;

    // We only specify the socket type here,
    // it will be initialized in the device. The point will assume
    // the usage of the default global 0MQ context.
    edgepoint::point echo_point = { cloudless::socket_type::PAIR };
    loopback.add("echo", echo_point);

    edges eds;
    eds.add("loopback", loopback);

    shared_ptr<echo> echo_device(new echo(eds));
    echo_device->start();
    // Instruct the main thread to sleep for 10ms
    // to make sure echo_device connected to a socket.
    // sleep() is a static function that only affects
    // the calling thread.
    echo_device->sleep(10);

    message msg("Echo!");
    echo_socket.send(msg);
    echo_device->sleep(10);

    // This is an asynchronous request to stop the device's thread.
    // The device's destructor however will block until the thread actually stops.
    echo_device->stop();

    return 0;
}
