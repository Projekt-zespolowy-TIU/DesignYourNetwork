#pragma once
#ifndef IPV6MASK_H
#define IPV6MASK_H

#include <istream>
#include <string>
#include <QString>
#include <boost/dynamic_bitset.hpp>

#include "IPv6address.h"

namespace core {
    class IPv6mask final: public IPv6address
    {
    public:
        IPv6mask(const boost::dynamic_bitset<>& maskAddress =
                boost::dynamic_bitset<>(
                    std::string{"11111111111111111111111111111111"
                                "11111111111111111111111111111111"
                                "11111111111111111111111111111111"
                                "11111111111111111111111111111111"}));
        IPv6mask(const QString& ipAddress);
    private:
        IPv6mask* _cloneImpl() const noexcept override;
        friend std::istream& operator>>(std::istream&, IPv6mask&);
       };
};

#endif // IPV6MASK_H
