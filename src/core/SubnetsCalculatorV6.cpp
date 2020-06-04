#include "SubnetsCalculatorV6.h"

#include <algorithm>
#include <memory>

#include "coreUtils.h"
#include "IPv6address.h"
#include "IPv6mask.h"

namespace core {
    void SubnetsCalculatorV6::calcSubnets(INetwork& Net) const
    {
        _fillSubnetsIps(dynamic_cast<Networkv6&>(Net));

        for(auto& subnet : Net.Subnets())
            _fillSubnetWithHosts(dynamic_cast<Subnetv6&>(*subnet));
    }

    void SubnetsCalculatorV6::_fillSubnetsIps(Networkv6& Net) const
    {
        std::vector<std::shared_ptr<ISubnet>> _subNets;
        for(const auto& sub : Net.Subnets())
            _subNets.emplace_back(sub->clone());

        std::sort(_subNets.begin(), _subNets.end(),[](const auto& lhs, const auto& rhs){
            return lhs->HostNumber() > rhs->HostNumber();
        });

        if(cpp_int{_subNets.size()} > Net.hostsCapacity())
            throw SubnetExcept{"Too many subnets passed into calculator within main network"};

        for(const auto& _subNet : _subNets)
        {
            IPv6mask Mask = alg.chooseMask(_subNet->HostNumber(), Net.Ip().getAddressLength());
            if(Net.Mask().getPrefix() > Mask.getPrefix())
                throw SubnetExcept{"IP mask pool has run out during subnetworks calculations"};

            IPv6address Address = alg.chooseIP(Net.Ip(), Mask, _subNets);
            if(!Net.isSubnet(Address))
                throw SubnetExcept{"IP address pool has run out during subnetworks calculations"};

            _subNet->Ip(std::make_unique<IPv6address>(Address));
            _subNet->Mask(std::make_unique<IPv6mask>(Mask));
        };

        Net.Subnets(_subNets);
    };

    void SubnetsCalculatorV6::_fillSubnetWithHosts(Subnetv6& subnet) const
    {
        for(cpp_int i{1}; i <= subnet.HostNumber(); i++)
        {
            auto ipv6Bitset = boost::dynamic_bitset<>{i.str()};
            ipv6Bitset.resize(128, false);

            IPv6address host_ip = subnet.Ip() | ipv6Bitset;
            subnet.addHost( std::make_unique<IPv6address>(host_ip),
                           QString{"Host nr "} + i.str().c_str() );
        }
    };
}
