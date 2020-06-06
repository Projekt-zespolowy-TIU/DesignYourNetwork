 #pragma once
#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H

#include "IPaddress.h"
#include "IPv6parser.h"

namespace core {
    class IPv6address : public IPaddress
    {
    public:
        IPv6address(const boost::dynamic_bitset<>& ip = boost::dynamic_bitset<>(128));
        IPv6address(const QString& ipAddress);
        IPv6address(const IPv6address& rhs);
        IPv6address& operator=(const IPv6address& rhs); //if inheritance evolve more, it should be deleted

        QString asStringDec() const override;
        QString asStringBin() const override;

        friend std::istream& operator>>(std::istream&, IPv6address&);
    protected:
        std::shared_ptr<IIPparser> _Parser = std::make_shared<IPv6parser>();
    private:
        std::array<unsigned char, 16> _convertBitsetIPv6ToArrayUCharIPv6(
                const boost::dynamic_bitset<>& bitset) const;
        IPv6address* _cloneImpl() const override;
    };
}

#endif // IPV6ADDRESS_H
