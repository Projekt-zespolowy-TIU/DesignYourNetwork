#pragma once
#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <istream>
#include <memory>
#include <QString>
#include <boost/dynamic_bitset.hpp>

#include "IPaddress.h"
#include "IPv4parser.h"

namespace core{
    class IPv4address: public IPaddress
    {
    public:
        IPv4address(const boost::dynamic_bitset<>& ip = boost::dynamic_bitset<>(32));
        IPv4address(const QString& ipAddress);
        IPv4address(const IPv4address& rhs);
        IPv4address& operator=(const IPv4address& rhs); //if inheritance evolve more, it should be deleted

        QString asStringDec() const override;
        QString asStringBin() const override;

        friend std::istream& operator>>(std::istream&, IPv4address&);
    protected:
        std::shared_ptr<IIPparser> _Parser = std::make_shared<IPv4parser>();
    private:
        IPv4address* _cloneImpl() const override;
    };
};

#endif // IPV4ADDRESS_H
