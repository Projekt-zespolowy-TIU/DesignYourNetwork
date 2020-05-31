#include "SubnetsCalculatorV4.h"

#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <memory>
#include <cmath>

#include "coreUtils.h"
#include "IIPmask.h"

namespace core {
    void SubnetsCalculatorV4::calcSubnets(const NetworkBase& mainNet, std::vector<std::shared_ptr<Subnet>>& subNets) const
    {
        _fillSubnetsIps(mainNet, subNets);

        for(auto subnet : subNets)
            _fillSubnetWithHosts(*subnet);
    }

    void SubnetsCalculatorV4::_fillSubnetsIps(const NetworkBase &mainNet, std::vector<std::shared_ptr<Subnet> > &subNets) const
    {
        std::vector<std::shared_ptr<Subnet>> _subNets;
        for(const auto& sub : subNets)
            _subNets.emplace_back(sub->clone());

        std::sort(_subNets.begin(), _subNets.end(),[](const auto& a, const auto& b){
            return a->HostNumber > b->HostNumber;
        });

        if(_subNets.size() > std::pow(2, 30 - mainNet.NetMask->getPrefix()) )
            throw IPSubnetworkExcept{"Too many subnets passed into calculator within main network"};

//        unsigned long long HostSum = 0;
        for(const auto& _subNet : _subNets)
        {
            auto Mask = _chooseSubnetMask(_subNet->HostNumber);
            if(mainNet.NetMask->getPrefix() > Mask->getPrefix())
                throw IPSubnetworkExcept{"IP mask pool has run out during subnetworks calculations"};

            auto Address = _chooseSubnetIP(*mainNet.Ip, *Mask, _subNets);
            if( (!mainNet.isHost(*Address)) && (*Address != *mainNet.Ip) )
                throw IPSubnetworkExcept{"IP address pool has run out during subnetworks calculations"};

            _subNet->Ip = Address;
            _subNet->NetMask = Mask;

//            HostSum += _subNet->hostsCapacity() + 2; //sum of all hosts should take all addresses into account both net address and broadcast
//            if(HostSum > std::pow(2, mainNet.NetMask->getPrefix())) //I think that this will never catch with above exceptions
//                throw IPException{"TODO"};
        };

        subNets = _subNets;
    };

    void SubnetsCalculatorV4::_fillSubnetWithHosts(Subnet &subnet) const
    {
        for(auto i = 1; i <= subnet.HostNumber; i++)
        {
            auto host_ip = dynamic_cast<IPv4address&>(*subnet.Ip) | IPv4address{boost::dynamic_bitset<>(32,i)};
            subnet.HostsList.emplace_back(Subnet::Host{i, QString{"Host nr "} + QString::number(i), std::make_shared<IPv4address>(host_ip)});
        }
    };

    std::shared_ptr<IPmaskBase> SubnetsCalculatorV4::_chooseSubnetMask(const long long desiredHostsNumber) const
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

    std::shared_ptr<IPaddressBase> SubnetsCalculatorV4::_chooseSubnetIP(const IPaddressBase& mainNetIP, const IIPmask& Mask, const std::vector<std::shared_ptr<Subnet>>& alreadyAssignedIPs) const
    {
        auto pretenderAddress{dynamic_cast<const IPv4address&>(mainNetIP)};

        unsigned long long int netBits = 1;

        while(std::any_of(alreadyAssignedIPs.begin(), alreadyAssignedIPs.end(), [&](const auto& subnet){
                          return subnet->isHost(pretenderAddress) || *subnet->Ip == pretenderAddress; }))
        {
            auto create = boost::dynamic_bitset<>(32, netBits << (32 - Mask.getPrefix()));

            IPv4address NetWildCard{create};
            pretenderAddress = dynamic_cast<const IPv4address&>(mainNetIP) | NetWildCard;
            netBits++;
        };
        return std::make_shared<IPv4address>(pretenderAddress);
    }
};
