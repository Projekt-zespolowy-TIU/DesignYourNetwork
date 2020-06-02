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
    class Networkv4 final : public INetwork<Subnetv4>
    {
    public:
        Networkv4(const IPv4address& ip, const IPv4mask& mask);
        Networkv4(const Networkv4& rhs);
        Networkv4& operator=(const Networkv4& rhs);

        const IPaddress& Ip() const override;
        const IPaddress& Mask() const override;
        const std::vector<Subnetv4>& Subnets() const override;
        std::vector<Subnetv4>& Subnets() override;

        void Subnets(std::vector<Subnetv4> subnets) override;

        void addSubnet(const cpp_int& hostNumber,
                       const QString& name = "blank") override;

        bool isSubnet(const IPaddress& hostIP) const override;
    private:
        std::unique_ptr<IPaddress> _Ip;
        std::unique_ptr<IPaddress> _NetMask;
        std::vector<Subnetv4> _Subnets;
    };
}

#endif // NETWORKV4_H
