#pragma once
#ifndef IPv4MASK_H
#define IPv4MASK_H

#include <istream>
#include <QString>
#include <boost/dynamic_bitset.hpp>

#include "IPv4address.h"

namespace core {
    class IPv4mask final: public IPv4address
    {
    public:
        IPv4mask(const boost::dynamic_bitset<>& maskAddress = boost::dynamic_bitset<>(32, 4294967295));
        IPv4mask(const QString& ipAddress);
    private:
        IPv4mask* _cloneImpl() const noexcept override;
        friend std::istream& operator>>(std::istream&, IPv4mask&);
       };
};

#endif // IPv4MASK_H
