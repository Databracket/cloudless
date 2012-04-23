/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2011 Databracket, LLC.
 * Copyright (c) 2011 Other contributors as noted in the AUTHORS file
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

    // thread

    class LIBCLOUDLESS_EXPORT thread : noncopyable, public boost::enable_shared_from_this<thread>
    {
    public:
        typedef boost::thread::native_handle_type native_handle_type;
        typedef boost::thread::id id;

        thread();
        virtual ~thread();

        bool start(bool detach_ = true, unsigned int time_ = 0);
        void stop() throw();

        id get_id() const throw();
        native_handle_type native_handle() const throw();
        static unsigned int hardware_concurrency() throw();
        static void sleep(unsigned int time_);

        bool operator ==(const thread& rhs) const;

    protected:
        virtual void body() = 0;
        virtual void on_error(const std::exception& ex_);

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
