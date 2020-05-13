#include "IPv4parser.h"

#include <QString>
#include <memory>
#include <stdexcept>
#include <boost/dynamic_bitset.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <string>

#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    std::shared_ptr<IPaddressBase> IPv4parser::ipFromString(const QString& IP) const
    {
        return std::make_shared<IPv4address>(_getBitset(IP.toStdString()));
    }

    std::shared_ptr<IPmaskBase> IPv4parser::ipMaskFromString(const QString & mask) const
    {
        return std::make_shared<IPv4mask>(_getBitset(mask.toStdString()));
    }

    boost::dynamic_bitset<> IPv4parser::_getBitset(const std::string& addressString) const
    {
        try {
            auto v4address = boost::asio::ip::make_address_v4(addressString);
            return boost::dynamic_bitset<> (32, v4address.to_ulong());
        } catch (const boost::system::system_error&) {
            std::throw_with_nested(std::runtime_error("Wrong input IP address"));
        };
    };
};
