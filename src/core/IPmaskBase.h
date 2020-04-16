#ifndef IPMASK_H
#define IPMASK_H

#include "IPaddressBase.h"

namespace core {
    class IPmaskBase : public IPaddressBase
    {
    public:
        IPmaskBase(const boost::dynamic_bitset<>& maskAddress): IPaddressBase{maskAddress} {};
        short getPrefix() const;
    };
}
#endif // IPMASK_H
