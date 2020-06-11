#pragma once
#ifndef IPPROTOCOLALGORITHM_H
#define IPPROTOCOLALGORITHM_H

#include <vector>
#include <memory>
#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace core {
    using boost::multiprecision::cpp_int;

    class IPaddress; //forward declaration
    class ISubnet; //forward declaration

    class IPprotocolAlgorithm final
    {
    public:
        boost::dynamic_bitset<> chooseMask(const cpp_int& desiredHostsNumber,
                                                  const unsigned short maskLength) const noexcept;
        boost::dynamic_bitset<> chooseIP(const IPaddress& mainNetIP,
                                                const IPaddress& Mask,
                                                const std::vector<std::shared_ptr<ISubnet>>& usedIPsPool
                                                ) const;
    };
}

#endif // IPPROTOCOLALGORITHM_H
