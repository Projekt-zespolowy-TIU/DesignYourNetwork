#pragma once
#ifndef IPSTRUCTS_H
#define IPSTRUCTS_H

#include <memory>

#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    struct NetworkBase
    {
        std::shared_ptr<IPaddressBase> Ip;
        std::shared_ptr<IPmaskBase> NetMask;

        bool isHost(const IPaddressBase& hostIP) const{
            if(*Ip == *(hostIP & *NetMask) )
                return true;
            else
                return false;
        };

        virtual ~NetworkBase() = default;
    };

    struct Subnet: public NetworkBase
    {
        long long int HostNumber = -10;
        QString SubName = "blank";
    };

    struct Networkv4: NetworkBase
    {
        Networkv4() { Ip = std::make_shared<IPv4address>(); NetMask = std::make_shared<IPv4mask>(); };
    };

    struct Subnetv4: public Subnet
    {
        Subnetv4() { Ip = std::make_shared<IPv4address>(); NetMask = std::make_shared<IPv4mask>(); };
    };
};

#endif // IPSTRUCTS_H
