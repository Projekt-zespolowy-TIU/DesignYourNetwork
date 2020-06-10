#include "IPv6parser.h"

#include <algorithm>
#include <boost/asio/ip/address_v6.hpp>

#include "coreUtils.h"

namespace core {
    boost::dynamic_bitset<> IPv6parser::ipFromString(const QString& IP) const
    {
        return _getBitset(IP.toStdString());
    }

    boost::dynamic_bitset<> IPv6parser::_getBitset(const std::string& addressString) const
    {
        try {
            auto v6address = boost::asio::ip::make_address_v6(addressString);
            return _convertArrayUCharIPv6ToBitsetIPv6(v6address.to_bytes());
        } catch (const boost::system::system_error&) {
            throw IPFormatExcept{"Passed string cannot be converted into valid IP version 4"};
        }
    }

    boost::dynamic_bitset<> IPv6parser::_convertArrayUCharIPv6ToBitsetIPv6(std::array<unsigned char, 16> table) const noexcept
    {
        std::string bitsetBuffer;
        for(const auto& element : table)
        {
            for(short i = 7; i >= 0; i--)
            {
                const unsigned char mask = 0b0000'0001;
                const auto bit = (element >> i) & mask;
                if(bit){
                    bitsetBuffer.push_back('1');
                }else{
                    bitsetBuffer.push_back('0');
                }
            }
        }
        return boost::dynamic_bitset<>(bitsetBuffer);
    }
}
