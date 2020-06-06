#pragma once
#ifndef IPV4PARSER_H
#define IPV4PARSER_H

#include <string>
#include <QString>
#include <boost/dynamic_bitset.hpp>

#include "IIPparser.h"

namespace core{
    class IPv4parser final: public IIPparser
    {
    public:
        boost::dynamic_bitset<> ipFromString(const QString &) const override;
    private:
        boost::dynamic_bitset<> _getBitset(const std::string& addressString) const;
    };
};

#endif // IPV4PARSER_H
