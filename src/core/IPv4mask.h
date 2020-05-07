#pragma once
#ifndef IPv4MASK_H
#define IPv4MASK_H

#include <boost/dynamic_bitset.hpp>

#include "IPv4address.h"
#include "IPmaskBase.h"

namespace core {
    class IPv4mask final: public IPv4address, public IPmaskBase
    {
    public:
        IPv4mask() : IPaddressBase(boost::dynamic_bitset<>(32)), IPmaskBase(boost::dynamic_bitset<>(32)) {};
        IPv4mask(const boost::dynamic_bitset<>& maskAddress);

        QString asStringBin() const override { return IPv4address::asStringBin(); };
        QString asStringDec() const override { return IPv4address::asStringDec(); };

    private:
        std::shared_ptr<IPaddressBase> _applyMask(const boost::dynamic_bitset<>& maskBitset) const override { return IPv4address::_applyMask(maskBitset); };
    };
};

#endif // IPv4MASK_H
