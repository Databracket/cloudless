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
 * An abstraction of 0MQ messages.
*/

#ifndef CLOUDLESS_MESSAGE_HPP
#define CLOUDLESS_MESSAGE_HPP

#include <string>
#include <deque>

#include <cloudless/detail/export.hpp>
#include <cloudless/detail/zeromq/zeromq.hpp>
#include <cloudless/element.hpp>

namespace cloudless
{

    /**
     * A message container for elements which 0MQ messages.
     */

    struct LIBCLOUDLESS_EXPORT message
    {

        /**
         * A default constructor.
         */
        message() {}

        /**
         * A constructor that takes a std::string.
         *
         * @param data a std::string for data to be put as a message in a container.
         */
        message(const std::string& data);

        /**
         * A constructor that takes a char array and its size.
         *
         * @param p a pointer to a char array.
         * @param size the size of the char array.
         */
        message(const void* p, size_t size);

        /**
         * A constructor that takes an element.
         *
         * @param elem an element that wraps a 0MQ message.
         */
        message(const element& elem);

        /**
         * Get the message at the bottom of the stack.
         *
         * @return an element.
         */
        element tail();

        /**
         * Push an element at the buttom of the stack.
         *
         * @param elem an element that wraps a 0MQ message.
         */
        message& push_tail(const element& elem);

        /**
         * Push a std::string at the bottom of the stack.
         *
         * @param data a std::string data that will be wrapped as an element internally.
         */
        message& push_tail(const std::string& data);

        /**
         * Push a char array at the bottom of the stack.
         *
         * @param p a pointer to a char array.
         * @param size the size of the char array.
         */
        message& push_tail(const void* p, size_t size);

        /**
         * Pop the message at the bottom of the stack.
         *
         * @return an element.
         */
        element pop_tail();

        /**
         * Get the message at the bottom of the stack.
         *
         * @return an element.
         */
        element head();

        /**
         * Push an element at the top of the stack.
         *
         * @param elem an element that wraps a 0MQ message.
         */
        message& push_head(const element& elem);

        /**
         * Push a std::string at the bottom of the stack.
         *
         * @param data a std::string data that will be wrapped as an element internally.
         */
        message& push_head(const std::string& data);

        /**
         * Push a char array at the bottom of the stack.
         *
         * @param p a pointer to a char array.
         * @param size the size of the char array.
         */
        message& push_head(const void* p, size_t size);

        /**
         * Pop the message at the bottom of the stack.
         *
         * @return an element.
         */
        element pop_head();

        /**
         * Get the size of the messages container.
         *
         * @return the size of the container.
         */
        size_t size() const throw();

        /**
         * Empty the messages container.
         */
        void clear() throw();

        /**
         * Access elements in the container by index.
         *
         * @param idx the index of the element.
         * @return an element.
         */
        element operator [](size_t idx) const;

        std::deque<element>* operator ->();

    private:
        element _M_element;
        std::deque<element> _M_elements;
    };

} // namespace cloudless

#endif // CLOUDLESS_MESSAGE_HPP
