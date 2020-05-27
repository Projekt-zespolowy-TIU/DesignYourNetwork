#include "IPv4parser.h"

#include <boost/asio/ip/address_v4.hpp>

#include "coreUtils.h"

namespace core {
    boost::dynamic_bitset<> IPv4parser::ipFromString(const QString& IP) const
    {
        return _getBitset(IP.toStdString());
    }

    boost::dynamic_bitset<> IPv4parser::_getBitset(const std::string& addressString) const
    {
        try {
            auto v4address = boost::asio::ip::make_address_v4(addressString);
            return boost::dynamic_bitset<> (32, v4address.to_ulong());
        } catch (const boost::system::system_error&) {
            throw IPFormatExcept{"Passed string cannot be converted into valid IP version 4"};
        };
    };
};
