#pragma once
#ifndef SUBNETV4_H
#define SUBNETV4_H

#include <memory>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "ISubnet.h"
#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    using boost::multiprecision::cpp_int;

    class Subnetv4 final: public ISubnet
    {
    public:
        Subnetv4(const cpp_int& hostNumber, const QString& name);
//        Subnetv4(const Subnetv4& rhs);
//        Subnetv4& operator=(const Subnetv4& rhs);
//        Subnetv4(Subnetv4&& rhs) noexcept;
//        Subnetv4& operator=(Subnetv4&& rhs) noexcept;

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
        std::unique_ptr<IPaddress> getBroadcast() const;
    private:
        Subnetv4* _cloneImpl() const noexcept override;

        std::unique_ptr<IPaddress> _Ip = std::make_unique<IPv4address>();
        std::unique_ptr<IPaddress> _NetMask = std::make_unique<IPv4mask>();

        QString _SubName;
        cpp_int _HostNumber;
        std::vector<std::shared_ptr<Host>> _HostsList;
    };
}

#endif // SUBNETV4_H
