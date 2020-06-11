#pragma once
#ifndef NETWORKV6_H
#define NETWORKV6_H

#include <memory>
#include <vector>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "INetwork.h"
#include "Subnetv6.h"
#include "IPv6address.h"
#include "IPv6mask.h"

namespace core {
    class Networkv6 final : public INetwork
    {
    public:
        Networkv6(const IPv6address& ip, const IPv6mask& mask);
        Networkv6(const Networkv6& rhs);
        Networkv6& operator=(const Networkv6& rhs);

        const IPaddress& Ip() const noexcept override;
        const IPaddress& Mask() const noexcept override;
        const std::vector<std::shared_ptr<ISubnet>>& Subnets() const noexcept override;

        void Subnets(const std::vector<std::shared_ptr<ISubnet>>& subnets) noexcept override;

        void addSubnet(const cpp_int& hostNumber,
                       const QString& name = "blank") override;

        cpp_int hostsCapacity() const override;
        bool isSubnet(const IPaddress& hostIP) const noexcept override;
    private:
        std::unique_ptr<IPaddress> _Ip;
        std::unique_ptr<IPaddress> _NetMask;
        std::vector<std::shared_ptr<ISubnet>> _Subnets;
    };
}

#endif // NETWORKV6_H
