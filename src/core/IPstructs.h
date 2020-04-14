#ifndef IPSTRUCTS_H
#define IPSTRUCTS_H

#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    struct NetworkBase
    {
        std::unique_ptr<IPaddressBase> Ip;
        std::unique_ptr<IPaddressBase> NetMask;
    };

    struct Subnet: public NetworkBase
    {
        int HostNumber = -1;
    };

    struct Networkv4: NetworkBase
    {
        Networkv4() { Ip = std::make_unique<IPv4address>(); NetMask = std::make_unique<IPv4mask>(); };
    };

    struct Subnetv4: public Subnet
    {
        Subnetv4() { Ip = std::make_unique<IPv4address>(); NetMask = std::make_unique<IPv4mask>(); };
    };
}

#endif // IPSTRUCTS_H
