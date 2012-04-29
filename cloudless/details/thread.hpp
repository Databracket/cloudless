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
 * An abstract wrapper around Boost::Thread.
*/

#ifndef __CLOUDLESS_DETAILS_THREAD_HPP
#define __CLOUDLESS_DETAILS_THREAD_HPP

#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <cloudless/details/export.hpp>
#include <cloudless/details/exception.hpp>
#include <cloudless/details/shared_ptr.hpp>
#include <cloudless/details/shared_array.hpp>
#include <cloudless/details/noncopyable.hpp>

namespace cloudless
{

namespace details
{

    /**
     * An abstraction class of Boost::Thread.
     */

    class LIBCLOUDLESS_EXPORT thread : noncopyable, public boost::enable_shared_from_this<thread>
    {
    public:
        typedef boost::thread::native_handle_type native_handle_type;
        typedef boost::thread::id id;

        /**
         * A default constructor.
         */
        thread();

        /**
         * A destructor.
         */
        virtual ~thread();

        /**
         * Start this thread either in detach or join mode.
         *
         * @param detach whether to laucnh the thread in detach mode.
         * @param time if detach was false; a time period in milliseconds
         * of which after joining, the thread will be detached. Value 0 means
         * join till the thread is finished.
         * @return whether launching the thread was successful.
         */
        bool start(bool detach = true, unsigned int time = 0);

        /**
         * Send a request to a detached thread to stop.
         */
        void stop() throw();

        /**
         * Get this thread's ID.
         *
         * @return thread's id.
         */
        id get_id() const throw();

        /**
         * Get the native system handle for the underlying thread.
         *
         * @return a native handle for this thread.
         */
        native_handle_type native_handle() const throw();

        /**
         * Get the number of hardware threads available on the current system.
         * Note that a value of 0 means that this information is not available.
         *
         * @return number of hardware threads available.
         */
        static unsigned int hardware_concurrency() throw();

        /**
         * A static helper function to instruct the calling thread
         * to sleep for a specific period of time expressed in milliseconds.
         *
         * @param time number of milliseconds for the calling thread to sleep.
         */
        static void sleep(unsigned int time);

        /**
         * Equality comparison between two threads.
         *
         * @param rhs an instance of thread.
         * @return true or false.
         */
        bool operator ==(const thread& rhs) const;

    protected:

        /**
         * A pure virtual function to be overrided by a child of this class.
         * This function represents the body of instructions and expressions
         * to be ran inside the thread.
         *
         * Note: This function will be called within an indefinite while-loop,
         * if you wish to conclude the operation of this thread, you must call
         * stop() from within this function.
         */
        virtual void body() = 0;

        /**
         * A virtual function to be optionally overrided by a child of this class.
         * This function will be executed in the event body() throws an exception.
         *
         * @param ex any exception inherited from std::exception or
         * even std::exception itself.
         */
        virtual void on_error(const std::exception& ex)
        {
            // No default error reporting mechanism configured.
            // Feel free to override this function to provide error
            // reporting in the case body() throws an exception.
        }

    private:
        shared_ptr<boost::thread> _Mp_thread;
        boost::mutex _M_mutex;
        boost::barrier _M_barrier;
        volatile bool _M_stop;
        volatile bool _M_detached;

    private:
        void _M_wait();
        void _M_run();

    };

} // namespace details

} // namespace cloudless

#endif // __CLOUDLESS_DETAILS_THREAD_HPP
