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
        IPaddress(const boost::dynamic_bitset<> &ip = boost::dynamic_bitset<>());
        IPaddress& operator=(const IPaddress&) = delete;

        std::unique_ptr<IPaddress> clone() const noexcept;

        short getPrefix() const;
        short getAddressLength() const noexcept;
        boost::dynamic_bitset<> raw() const noexcept;

        QString asStringBin() const noexcept override;
        QString asStringDec() const noexcept override;
    protected:
        boost::dynamic_bitset<> _IpAddress;
    private:
        bool isMask() const noexcept;
        virtual IPaddress* _cloneImpl() const noexcept;

    public:
        virtual ~IPaddress() = default;
    };

    bool operator==(const IPaddress& lhs, const IPaddress& rhs) noexcept;
    bool operator!=(const IPaddress& lhs, const IPaddress& rhs) noexcept;
    boost::dynamic_bitset<> operator&(const IPaddress& lhs, const IPaddress& rhs) noexcept;
    boost::dynamic_bitset<> operator|(const IPaddress& lhs, const IPaddress& rhs) noexcept;
}

#endif // IPADDRESS_H
