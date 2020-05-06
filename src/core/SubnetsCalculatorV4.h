#pragma once
#ifndef SUBNETSCALCULATORV4_H
#define SUBNETSCALCULATORV4_H

#include <vector>
#include <memory>

#include "IPstructs.h"

namespace core {
    class IIPmask; //forward declaration

    class SubnetsCalculatorV4
    {
    public:
        int calcSubnets(const NetworkBase& mainNet, const std::vector<std::shared_ptr<Subnet>>& subNets);
    private:
        std::shared_ptr<IPmaskBase> _chooseSubnetMask(const long long& desiredHostsNumber);
        std::shared_ptr<IPaddressBase> _chooseSubnetIP(const IPaddressBase& mainNetIP, const IIPmask& Mask, const std::vector<std::shared_ptr<Subnet>>& alreadyAssignedIPs);
    };
};

#endif // SUBNETSCALCULATORV4_H
