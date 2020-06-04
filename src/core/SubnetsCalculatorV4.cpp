#include "SubnetsCalculatorV4.h"

#include <algorithm>
#include <memory>

#include "coreUtils.h"
#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    void SubnetsCalculatorV4::calcSubnets(INetwork& Net) const
    {
        _fillSubnetsIps(dynamic_cast<Networkv4&>(Net));

        for(auto& subnet : Net.Subnets())
            _fillSubnetWithHosts(dynamic_cast<Subnetv4&>(*subnet));
    }

    void SubnetsCalculatorV4::_fillSubnetsIps(Networkv4& Net) const
    {
        std::vector<std::shared_ptr<ISubnet>> _subNets;
        for(const auto& sub : Net.Subnets())
            _subNets.emplace_back(sub->clone());
//        auto _subNets = Net.Subnets();

        std::sort(_subNets.begin(), _subNets.end(),[](const auto& lhs, const auto& rhs){
            return lhs->HostNumber() > rhs->HostNumber();
        });

        if(cpp_int{_subNets.size()} > Net.hostsCapacity() )
            throw SubnetExcept{"Too many subnets passed into calculator within main network"};

        for(const auto& _subNet : _subNets)
        {
            IPv4mask Mask = alg.chooseMask(_subNet->HostNumber(), Net.Ip().getAddressLength());
            if(Net.Mask().getPrefix() > Mask.getPrefix())
                throw SubnetExcept{"IP mask pool has run out during subnetworks calculations"};

            IPv4address Address = alg.chooseIP(Net.Ip(), Mask, _subNets);
            if(!Net.isSubnet(Address))
                throw SubnetExcept{"IP address pool has run out during subnetworks calculations"};

            _subNet->Ip(std::make_unique<IPv4address>(Address));
            _subNet->Mask(std::make_unique<IPv4mask>(Mask));
        };

        Net.Subnets(_subNets);
    };

    void SubnetsCalculatorV4::_fillSubnetWithHosts(Subnetv4& subnet) const
    {
        for(cpp_int i{1}; i <= subnet.HostNumber(); i++)
        {
            IPv4address host_ip = subnet.Ip() |
                    IPv4address{boost::dynamic_bitset<>(32, i.convert_to<unsigned long long>())};
            subnet.addHost(std::make_unique<IPv4address>(host_ip),
                           QString{"Host nr "} + (i.str().c_str()));
        }
    };
};
