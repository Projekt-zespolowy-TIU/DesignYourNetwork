#include "SubnetsCalculatorV4.h"

#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <memory>
#include <cmath>

#include "coreUtils.h"
#include "IIPmask.h"

namespace core {
    int SubnetsCalculatorV4::calcSubnets(const NetworkBase& mainNet, const std::vector<std::shared_ptr<Subnet>>& subNets)
    {
        auto _subNets = subNets;

        std::sort(_subNets.begin(), _subNets.end(),[](const auto& a, const auto& b){
            return a->HostNumber > b->HostNumber;
        });

        //start specific v4 implementation; later should be universaly refactored
        if(_subNets.size() > std::pow(2, 30 - mainNet.NetMask->getPrefix()) )
            throw NotImplemented{"too much subnets"};

        //before enter below loop should check sum of all max_hosts from passed subnets and return error when exceed max
        for(const auto& _subNet : _subNets)
        {
            auto Mask = _chooseSubnetMask(_subNet->HostNumber); //TODO: error handling when choosen mask exceeds main mask, check if such situation's even possible
            auto Address = _chooseSubnetIP(*mainNet.Ip, *Mask, _subNets); //TODO: error handling
            _subNet->Ip = Address;
            _subNet->NetMask = Mask;
        };
        //end of specific v4 implementation
        return 0;
    };

    std::shared_ptr<IPmaskBase> SubnetsCalculatorV4::_chooseSubnetMask(const long long& desiredHostsNumber)
    {
        unsigned short numberOfHostBits = 1;
        long long int countHosts = 0;

        while( !((countHosts -2) >= desiredHostsNumber) )
        {
            countHosts = std::pow(2, numberOfHostBits);
            numberOfHostBits++;
        };

        return std::make_shared<IPv4mask>(boost::dynamic_bitset<>(32, 4294967295 - (countHosts - 1)));
    };

    std::shared_ptr<IPaddressBase> SubnetsCalculatorV4::_chooseSubnetIP(const IPaddressBase& mainNetIP, const IIPmask& Mask, const std::vector<std::shared_ptr<Subnet>>& alreadyAssignedIPs)
    {
        auto pretenderAddress{*dynamic_cast<const IPv4address*>(&mainNetIP)};

        unsigned long long int netBits = 1;

        while(std::any_of(alreadyAssignedIPs.begin(), alreadyAssignedIPs.end(), [&](const auto& x){
                       return *x->Ip == pretenderAddress;}))
        {
            auto create = boost::dynamic_bitset<>(32, netBits << (32 - Mask.getPrefix()));

            IPv4address NetWildCard{create};
            pretenderAddress = *dynamic_cast<const IPv4address*>(&mainNetIP) | NetWildCard;
            netBits++;
        };
        return std::make_shared<IPv4address>(pretenderAddress);
    };
};
