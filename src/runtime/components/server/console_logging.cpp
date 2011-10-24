//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <iostream>

#include <hpx/hpx_fwd.hpp>

#include <hpx/util/ini.hpp>
#include <hpx/util/static.hpp>
#include <hpx/util/spinlock.hpp>
#include <hpx/util/serialize_sequence.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/runtime/components/server/console_logging.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include <boost/logging/format/named_write_fwd.hpp>
#include <boost/logging/format_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// definitions related to console logging

namespace boost { namespace serialization
{
    template <typename Archive>
    void serialize(Archive& ar, hpx::components::message_type& r,
        const unsigned int version)
    {
        hpx::util::serialize_sequence(ar, r);
    }
}}

///////////////////////////////////////////////////////////////////////////////
// This must be in global namespace
HPX_REGISTER_PLAIN_ACTION_EX2(
    hpx::components::server::console_logging_action<>,
    console_logging_action, true);

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components { namespace server
{
    struct log_lock_tag {};

    util::spinlock& get_log_lock()
    {
        util::static_<util::spinlock, log_lock_tag> lock;
        return lock.get();
    }

    ///////////////////////////////////////////////////////////////////////////
    // implementation of console based logging
    void console_logging(messages_type const& msgs)
    {
        util::spinlock::scoped_lock l(get_log_lock());

        using boost::fusion::at_c;

        BOOST_FOREACH(message_type const& msg, msgs)
        {
            const logging_destination dest = at_c<0>(msg);
            const std::size_t level = at_c<1>(msg);
            std::string const& s = at_c<2>(msg);

            switch (dest) {
            case destination_hpx:
                LHPX_CONSOLE_(level) << s;
                break;

            case destination_timing:
                LTIM_CONSOLE_(level) << s;
                break;

            case destination_agas:
                LAGAS_CONSOLE_(level) << s;
                break;

            case destination_app:
                LAPP_CONSOLE_(level) << s;
                break;

            default:
                break;
            }
        }
    }
}}}

