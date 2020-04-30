#pragma once
#ifndef IPV4PARSER_H
#define IPV4PARSER_H

#include <QString>
#include <memory>
#include <exception>
#include <boost/dynamic_bitset.hpp>
#include <boost/asio/ip/address_v4.hpp>

#include "IIPparser.h"

namespace core{
    class IPv4address; //forward declaration

    template <class C = IPv4address>
    class IPv4parser final: public IIPparser<C>
    {
    public:
        C ipFromString(const QString&) const final;
    };

    template <class C>
    C IPv4parser<C>::ipFromString(const QString& IP) const
    {
        boost::asio::ip::address_v4 converted;

        try {
            converted = boost::asio::ip::make_address_v4(IP.toStdString());
        } catch (const boost::system::system_error&) {
            std::throw_with_nested(std::runtime_error("Wrong input IP address"));
        };

        boost::dynamic_bitset<> octetContainer(32, converted.to_ulong());
        return std::move(octetContainer);
    };
};

#endif // IPV4PARSER_H
