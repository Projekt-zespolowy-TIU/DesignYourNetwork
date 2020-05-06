#pragma once
#ifndef IPV4PARSER_H
#define IPV4PARSER_H

#include <QString>
#include <memory>
#include <boost/dynamic_bitset.hpp>
#include <string>

#include "IIPparser.h"

namespace core{
    class IPv4parser final: public IIPparser
    {
    public:
        std::shared_ptr<IPaddressBase> ipFromString(const QString &) const final;
        std::shared_ptr<IPmaskBase> ipMaskFromString(const QString &) const final;
    private:
        boost::dynamic_bitset<> _getBitset(const std::string& addressString) const;
    };
};

#endif // IPV4PARSER_H
