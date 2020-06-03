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

        if(cpp_int{_subNets.size()} > ( cpp_int{1} << (Net.Ip().getAddressLength() - 2) -
                                                     Net.Mask().getPrefix() ) )
            throw SubnetExcept{"Too many subnets passed into calculator within main network"};

        for(auto& _subNet : _subNets)
        {
            IPv4mask Mask = _chooseSubnetMask(_subNet->HostNumber(), Net.Ip().getAddressLength());
            if(Net.Mask().getPrefix() > Mask.getPrefix())
                throw SubnetExcept{"IP mask pool has run out during subnetworks calculations"};

            IPv4address Address = _chooseSubnetIP(Net.Ip(), Mask, _subNets);
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

    boost::dynamic_bitset<> SubnetsCalculatorV4::_chooseSubnetMask(const cpp_int& desiredHostsNumber,
                                                                   const unsigned short maskLength) const
    {
        unsigned short numberOfHostBits = 1;
        cpp_int countHosts = 0;

        while( !((countHosts -2) >= desiredHostsNumber) )
        {
            countHosts = (cpp_int{1} << numberOfHostBits);
            numberOfHostBits++;
        };

        return boost::dynamic_bitset<>(maskLength, 4294967295 - (countHosts.convert_to<unsigned long long>() - 1));
    };

    boost::dynamic_bitset<> SubnetsCalculatorV4::_chooseSubnetIP(const IPaddress& mainNetIP,
                                                                 const IPaddress& Mask,
                                                                 const std::vector<std::shared_ptr<ISubnet>>& usedIPsPool) const
    {
        auto pretenderAddress = mainNetIP.raw();
        auto len = static_cast<unsigned short>(pretenderAddress.size());

        cpp_int netBits{1};

        while(std::any_of(usedIPsPool.begin(), usedIPsPool.end(), [&](const auto& subnet) {
                          return subnet->isHost(pretenderAddress) ||
                          subnet->Ip().raw() == pretenderAddress; }))
        {
            auto create = boost::dynamic_bitset<>(len, ( netBits << (len - Mask.getPrefix()))
                                                        .convert_to<unsigned long long>() );

            pretenderAddress = (mainNetIP | create);
            netBits++;
        };
        return pretenderAddress;
    }
};
