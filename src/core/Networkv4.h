#pragma once
#ifndef NETWORKV4_H
#define NETWORKV4_H

#include <memory>
#include <vector>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "INetwork.h"
#include "Subnetv4.h"
#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    class Networkv4 final : public INetwork
    {
    public:
        Networkv4(const IPv4address& ip, const IPv4mask& mask);
        Networkv4(const Networkv4& rhs);
        Networkv4& operator=(const Networkv4& rhs);

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

#endif // NETWORKV4_H
