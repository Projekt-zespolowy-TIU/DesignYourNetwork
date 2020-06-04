#pragma once
#ifndef SUBNETSCALCULATORV4_H
#define SUBNETSCALCULATORV4_H

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include "Networkv4.h"
#include "IPprotocolAlgorithm.h"

namespace core {
    class SubnetsCalculatorV4
    {
    public:
        void calcSubnets(INetwork& Net) const;
    private:
        void _fillSubnetsIps(Networkv4& Net) const;
        void _fillSubnetWithHosts(Subnetv4& subNet) const;

        IPprotocolAlgorithm alg;
    };
};

#endif // SUBNETSCALCULATORV4_H
