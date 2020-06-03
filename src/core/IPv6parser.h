#ifndef IPV6PARSER_H
#define IPV6PARSER_H

#include <array>

#include "IIPparser.h"

namespace core {
    class IPv6parser : public IIPparser
    {
    public:
        boost::dynamic_bitset<> ipFromString(const QString& ip) const override;
    private:
        boost::dynamic_bitset<> _getBitset(const std::string& addressString) const;
        boost::dynamic_bitset<> _convertArrayUCharIPv6ToBitsetIPv6(std::array<unsigned char, 16> table) const;
    };
}

#endif // IPV6PARSER_H
