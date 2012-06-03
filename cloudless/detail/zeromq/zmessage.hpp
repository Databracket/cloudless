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
 * A wrapper around 0MQ low level messages.
*/

#ifndef CLOUDLESS_DETAIL_ZEROMQ_ZMESSAGE_HPP
#define CLOUDLESS_DETAIL_ZEROMQ_ZMESSAGE_HPP

#include <string>
#include <utility>

#include <cloudless/detail/zeromq/zeromq.hpp>
#include <cloudless/detail/export.hpp>

namespace cloudless
{

namespace detail
{

    using namespace std::rel_ops;

    /**
     * A wrapper structure around 0MQ low level messages.
     */

    struct LIBCLOUDLESS_EXPORT zmessage : private zmq_msg_t
    {

        /**
         * A default constructor to initialize an empty 0MQ message.
         */
        zmessage();

        /**
         * A constructor to initialize a 0MQ message with a specific size.
         *
         * @param size size of message to be initialized.
         */
        zmessage(size_t size);

        /**
         * A copy constructor.
         *
         * @param msg a constant referance to an instance of zmessage.
         */
        zmessage(const zmessage& msg);

        /**
         * A destructor to free the allocated 0MQ message.
         */
        ~zmessage();

        /**
         * Get a pointer to the underlying data in the message.
         *
         * @return a void pointer to the underlying data.
         */
        void* data() const throw();

        /**
         * Get the size of the data in the message.
         *
         * @return the size of the underlying data.
         */
        size_t size() const throw();

        /**
         * Cast a message to a std::string.
         *
         * @return std::string of the data inside this message.
         */
        operator std::string() const throw();

        /**
         * Cast a message to the low level 0MQ message type.
         *
         * @return 0MQ message type.
         */
        operator zmq_msg_t*() throw();

        /**
         * A generic equality comparison against this zmessage.
         *
         * @tparam T a generic type that this zmessage is casted against.
         * @param rhs a constant reference to T.
         * @return true or false.
         */
        template <typename T>
        inline bool operator ==(const T& rhs) const
        {
            return (T)*this == rhs;
        }

        /*
         * A special case of the equality comparison.
         */
        bool operator ==(const char* rhs) const;

        /**
         * A generic less-than comparison against this zmessage.
         *
         * @tparam T a generic type that this zmessage is casted against.
         * @param rhs a constant reference to T.
         * @return true or false.
         */
        template <typename T>
        inline bool operator <(const T& rhs) const
        {
            return (T)*this < rhs;
        }

        /*
         * A special case of the less-than comparison.
         */
        bool operator <(const char* rhs) const;

    };

} // namespace detail

} // namespace cloudless

#endif // CLOUDLESS_DETAIL_ZEROMQ_ZMESSAGE_HPP
