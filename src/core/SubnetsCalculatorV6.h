#pragma once
#ifndef SUBNETSCALCULATORV6_H
#define SUBNETSCALCULATORV6_H

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include "Networkv6.h"
#include "IPprotocolAlgorithm.h"

namespace core {
    class SubnetsCalculatorV6
    {
    public:
        void calcSubnets(INetwork& Net) const;
    private:
        void _fillSubnetsIps(Networkv6& Net) const;
        void _fillSubnetWithHosts(Subnetv6& subNet) const;

        IPprotocolAlgorithm alg;
    };
};

#endif // SUBNETSCALCULATORV6_H
