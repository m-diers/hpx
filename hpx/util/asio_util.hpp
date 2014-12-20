//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_UTIL_ASIOUTIL_MAY_16_2008_1212PM)
#define HPX_UTIL_ASIOUTIL_MAY_16_2008_1212PM

#include <hpx/config.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace hpx { namespace util
{
    ///////////////////////////////////////////////////////////////////////////
    HPX_API_EXPORT bool get_endpoint(std::string const& addr,
        boost::uint16_t port, boost::asio::ip::tcp::endpoint& ep);

    HPX_API_EXPORT std::string get_endpoint_name(
        boost::asio::ip::tcp::endpoint const& ep);

    ///////////////////////////////////////////////////////////////////////////
    // properly resolve a give host name to the corresponding IP address
    HPX_API_EXPORT boost::asio::ip::tcp::endpoint
    resolve_hostname(std::string const& hostname, boost::uint16_t port,
        boost::asio::io_service& io_service);

    ///////////////////////////////////////////////////////////////////////
    // Addresses are supposed to have the format <hostname>[:port]
    HPX_API_EXPORT bool split_ip_address(std::string const& v, std::string& host,
        boost::uint16_t& port);

    typedef boost::asio::ip::tcp::resolver::iterator endpoint_iterator_type;

    endpoint_iterator_type connect_begin(std::string const & address, boost::uint16_t port,
        boost::asio::io_service& io_service);

    /// \brief Returns an iterator which when dereferenced will give an
    ///        endpoint suitable for a call to connect() related to this
    ///        locality
    template <typename Locality>
    endpoint_iterator_type connect_begin(Locality const& loc,
        boost::asio::io_service& io_service)
    {
        return connect_begin(loc.address(), loc.port(), io_service);
    }

    inline endpoint_iterator_type connect_end()
    {
        return endpoint_iterator_type();
    }

    endpoint_iterator_type accept_begin(std::string const & address, boost::uint16_t port,
        boost::asio::io_service& io_service);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Returns an iterator which when dereferenced will give an
    ///        endpoint suitable for a call to accept() related to this
    ///        locality
    template <typename Locality>
    endpoint_iterator_type accept_begin(Locality const& loc,
        boost::asio::io_service& io_service)
    {
        return accept_begin(loc.address(), loc.port(), io_service);
    }

    inline endpoint_iterator_type accept_end() //-V524
    {
        return endpoint_iterator_type();
    }

}}

#endif

