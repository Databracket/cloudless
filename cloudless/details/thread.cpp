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

#include <boost/bind.hpp>

#include <cloudless/details/thread.hpp>

namespace cloudless
{

namespace details
{

    // thread

    thread::thread() :
        _M_barrier(2),
        _M_stop(false),
        _M_detached(false)
    {}

    thread::~thread()
    {
        // Must stop any threads running before destroying this instance
        // otherwise nasty things shall ensue.
        stop();

        _M_wait();
    }

    bool
    thread::start(bool detach, unsigned int time)
    {
        if (_Mp_thread)
            return false;

        _Mp_thread.reset(new boost::thread(
                    boost::bind(&thread::_M_run,
                        shared_from_this())));

        if (detach) {
            _Mp_thread->detach();
            return _M_detached = true;
        }

        if (time == 0) {
            _Mp_thread->join();
            return true;
        }

        return _Mp_thread->timed_join(boost::posix_time::milliseconds(time));
    }

    void
    thread::stop() throw()
    {
        _M_stop = true;
    }

    thread::id
    thread::get_id() const throw()
    {
        return _Mp_thread->get_id();
    }

    unsigned int
    thread::hardware_concurrency() throw()
    {
        return boost::thread::hardware_concurrency();
    }

    void
    thread::sleep(unsigned int time)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(time));
    }

    thread::native_handle_type
    thread::native_handle() const throw()
    {
        return _Mp_thread->native_handle();
    }

    bool
    thread::operator ==(const thread& rhs) const
    {
        return get_id() == rhs.get_id();
    }

    void
    thread::_M_wait()
    {
        // Here we make sure that the thread will not deadlock on itself
        // by waiting on a barrier that will never be reached by the parent
        // thread, in the case that it was joined.
        if (_M_detached)
            _M_barrier.wait();
    }

    void
    thread::_M_run()
    {
        // This mutex is only used as a memory fence
        boost::mutex::scoped_lock lck(_M_mutex);

        try {
            while (!_M_stop) { body(); }
        } catch (const std::exception& ex) {
            try { on_error(ex); }
            catch (...) { /* We're sorry for your loss. */ }
        } catch (...) { /* Not much to be done ... */ }

        _M_wait();
    }

} // namespace details

} // namespace cloudless
