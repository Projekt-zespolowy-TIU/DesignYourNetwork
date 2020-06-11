#pragma once
#ifndef SUBNETV6_H
#define SUBNETV6_H

#include <memory>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "ISubnet.h"
#include "IPv6address.h"
#include "IPv6mask.h"

namespace core {
    using boost::multiprecision::cpp_int;

    class Subnetv6 final: public ISubnet
    {
    public:
        Subnetv6(const cpp_int& hostNumber, const QString& name);

        QString SubName() const noexcept override;
        cpp_int HostNumber() const noexcept override;
        const IPaddress& Ip() const noexcept override;
        const IPaddress& Mask() const noexcept override;
        const std::vector<std::shared_ptr<Host>>& HostsList() const noexcept override;

        void Ip(std::unique_ptr<IPaddress> ip) noexcept override;
        void Mask(std::unique_ptr<IPaddress> mask) noexcept override;
        void SubName(const QString& newName) noexcept override;

        void addHost(std::unique_ptr<IPaddress> ip,
                     const QString& name = "noname") noexcept override;
        bool isHost(const IPaddress& hostIP) const noexcept override;
        cpp_int hostsCapacity() const override;
        std::unique_ptr<IPaddress> getMinHost() const override;
        std::unique_ptr<IPaddress> getMaxHost() const override;
    private:
        Subnetv6* _cloneImpl() const noexcept override;

        std::unique_ptr<IPaddress> _Ip = std::make_unique<IPv6address>();
        std::unique_ptr<IPaddress> _NetMask = std::make_unique<IPv6mask>();

        QString _SubName;
        cpp_int _HostNumber;
        std::vector<std::shared_ptr<Host>> _HostsList;
    };
}

#endif // SUBNETV6_H
