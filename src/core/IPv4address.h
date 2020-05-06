#pragma once
#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <boost/dynamic_bitset.hpp>
#include <QString>

#include "IPaddressBase.h"

namespace core{
    class IPv4address: public virtual IPaddressBase
    {
    public:
        IPv4address(): IPaddressBase(boost::dynamic_bitset<>(32)) {};
        IPv4address(const boost::dynamic_bitset<>& ipaddress): IPaddressBase(ipaddress) {};

        QString asStringDec() const override;
        QString asStringBin() const override;

        IPv4address operator| (const IPv4address& var) const;

    protected:
        std::shared_ptr<IPaddressBase> _applyMask(const boost::dynamic_bitset<>& maskBitset) const override;
    };
};

#endif // IPV4ADDRESS_H
