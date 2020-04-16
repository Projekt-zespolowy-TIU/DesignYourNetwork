#ifndef SUBNETSCALCULATOR_H
#define SUBNETSCALCULATOR_H

#include <vector>
#include <memory>

#include "IPstructs.h"

namespace core {
    class SubnetsCalculatorV4
    {
    public:
        int calcSubnets(const std::shared_ptr<NetworkBase>& mainNet, const std::vector<std::shared_ptr<Subnet>>& subNets);
    private:
        IPmaskBase _chooseSubnetMask(const long long& desiredHostsNumber);
        IPaddressBase _chooseSubnetIP(const IPaddressBase& mainNetIP, const IPmaskBase& pretentMask, const std::vector<std::shared_ptr<Subnet>>& alreadyAssignedIPs);
    };
}

#endif // SUBNETSCALCULATOR_H
