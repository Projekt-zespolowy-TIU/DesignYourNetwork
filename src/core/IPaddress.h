#pragma once
#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <memory>
#include <QString>
#include <boost/dynamic_bitset.hpp>

#include "IIPaddrPrintable.h"

namespace core {
    class IPaddress: public IIPaddrPrintable
    {
    public:
        IPaddress(boost::dynamic_bitset<> ip = boost::dynamic_bitset<>());
        IPaddress& operator=(const IPaddress&) = delete;

        std::unique_ptr<IPaddress> clone() const;

        short getPrefix() const;
        short getAddressLength() const;
        boost::dynamic_bitset<> raw() const;

        QString asStringBin() const override;
        QString asStringDec() const override;
    protected:
        boost::dynamic_bitset<> _IpAddress;
    private:
        bool isMask() const;
        virtual IPaddress* _cloneImpl() const;

    public:
        virtual ~IPaddress() = default;
    };

    bool operator==(const IPaddress& lhs, const IPaddress& rhs);
    bool operator!=(const IPaddress& lhs, const IPaddress& rhs);
    boost::dynamic_bitset<> operator&(const IPaddress& ip, const IPaddress& mask);
    boost::dynamic_bitset<> operator|(const IPaddress& lhs, const IPaddress& rhs);
}

#endif // IPADDRESS_H
