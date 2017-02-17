/**
 *  boost::asio backends
 *  ====================
 *
 *  Print boost::asio backend info.
 *
 *  Note: Compile with argument -lboost_system.
 */

#include <iostream>
#include <string>
#include <boost/asio.hpp>

int
main(int argc, const char *argv[])
{
    std::string api;

#if defined(BOOST_ASIO_HAS_IOCP)
    api = "iocp";
#elif defined(BOOST_ASIO_HAS_EPOLL)
    api = "epoll";
#elif defined(BOOST_ASIO_HAS_KQUEUE)
    api = "kqueue";
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
    api = "/dev/poll";
#else
    api = "select";
#endif

    std::cout << api << std::endl;
    return 0;
}
