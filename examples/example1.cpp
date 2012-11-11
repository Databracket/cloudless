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
 * Example #1
*/

#include <iostream>
#include <string>

#include <cloudless/context.hpp> // A wrapper for 0MQ contexts.
#include <cloudless/message.hpp> // An abstraction for 0MQ messages.
#include <cloudless/address.hpp> // An abstraction for 0MQ address format.
#include <cloudless/pair.hpp> // A 0MQ PAIR socket.

using namespace std;

using cloudless::context;
using cloudless::address;
using cloudless::message;

int main()
{
    context ctx;
    address addr(cloudless::protocol::INPROC, "nightclub");

    // Equivalent to socket(ctx, socket_type::PAIR)
    cloudless::pair alice(ctx);
    alice.bind(addr);

    cloudless::pair bob(ctx);
    bob.connect(addr);

    message msg("Hi Alice!");
    bob.send(msg);

    alice.recv(msg);
    cout << "Bob says: " << (string)msg.head() << endl;

    if (msg.pop_head() == "Hi Alice!")
        alice.send(msg.push_head("Hey Bob!")
                .push_tail("Let's have a drink"));

    bob.recv(msg);
    cout << "Alice says: " << (string)msg.pop_head() << endl;

    // Once the socket object is out of
    // scope close() is called.
    bob.close();
    alice.close();

    return 0;
}
