#pragma once
#ifndef SUBNETSCALCULATORV4_H
#define SUBNETSCALCULATORV4_H

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include "Networkv4.h"

namespace core {
    class SubnetsCalculatorV4
    {
    public:
        void calcSubnets(Networkv4& Net) const;
    private:
        void _fillSubnetsIps(Networkv4& Net) const;
        void _fillSubnetWithHosts(Subnetv4& subNet) const;
        boost::dynamic_bitset<> _chooseSubnetMask(const cpp_int& desiredHostsNumber,
                                                  const unsigned short maskLength) const;
        boost::dynamic_bitset<> _chooseSubnetIP(const IPaddress& mainNetIP,
                                                const IPaddress& Mask,
                                                const std::vector<Subnetv4>& usedIPsPool
                                                ) const;
    };
};

#endif // SUBNETSCALCULATORV4_H
