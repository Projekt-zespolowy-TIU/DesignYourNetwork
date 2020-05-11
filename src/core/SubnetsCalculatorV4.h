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
        void calcSubnets(const NetworkBase& mainNet, std::vector<std::shared_ptr<Subnet>>& subNets) const;
    private:
        std::shared_ptr<IPmaskBase> _chooseSubnetMask(const long long desiredHostsNumber) const;
        std::shared_ptr<IPaddressBase> _chooseSubnetIP(const IPaddressBase& mainNetIP, const IIPmask& Mask, const std::vector<std::shared_ptr<Subnet>>& alreadyAssignedIPs) const;
    };
};

#endif // SUBNETSCALCULATORV4_H
