#pragma once
#ifndef INETWORK_H
#define INETWORK_H

#include <vector>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "IPaddress.h"
#include "ISubnet.h"

namespace core {
    using boost::multiprecision::cpp_int;

    class INetwork
    {
    public:
        virtual const IPaddress& Ip() const = 0;
        virtual const IPaddress& Mask() const = 0;
        virtual const std::vector<std::shared_ptr<ISubnet>>& Subnets() const = 0;

        virtual void Subnets(const std::vector<std::shared_ptr<ISubnet>>& subnets) = 0;

        virtual void addSubnet(const cpp_int& hostNumber, const QString& name) = 0;

        virtual cpp_int hostsCapacity() const = 0;
        virtual bool isSubnet(const IPaddress& hostIP) const = 0;

    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    public:
        virtual ~INetwork() = default;
    protected:
        INetwork() = default;
        INetwork(const INetwork&) = default;
        INetwork& operator=(const INetwork&) = default;
        INetwork(INetwork&&) noexcept = default;
        INetwork& operator=(INetwork&&) noexcept = default;
    };
    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
}

#endif // INETWORK_H
