#pragma once
#ifndef ISUBNET_H
#define ISUBNET_H

#include <vector>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "Host.h"

namespace core {
    using boost::multiprecision::cpp_int;

    class IPaddress; //forward declaration

    class ISubnet
    {
    public:
        virtual QString SubName() const = 0;
        virtual cpp_int HostNumber() const = 0;
        virtual const IPaddress& Ip() const = 0;
        virtual const IPaddress& Mask() const = 0;
        virtual const std::vector<std::shared_ptr<Host>>& HostsList() const = 0;

        virtual void Ip(std::unique_ptr<IPaddress> ip) = 0;
        virtual void Mask(std::unique_ptr<IPaddress> mask) = 0;

        virtual void addHost(std::unique_ptr<IPaddress> ip,
                             const QString& name) = 0;
        virtual bool isHost(const IPaddress& hostIP) const = 0;
        virtual cpp_int hostsCapacity() const = 0;
        virtual std::unique_ptr<IPaddress> getMinHost() const = 0;
        virtual std::unique_ptr<IPaddress> getMaxHost() const = 0;

    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    public:
        virtual ~ISubnet() = default;
    protected:
        ISubnet() = default;
        ISubnet(const ISubnet&) = default;
        ISubnet& operator=(const ISubnet&) = default;
        ISubnet(ISubnet&&) noexcept = default;
        ISubnet& operator=(ISubnet&&) noexcept = default;
    };
        //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
}

#endif // ISUBNET_H
