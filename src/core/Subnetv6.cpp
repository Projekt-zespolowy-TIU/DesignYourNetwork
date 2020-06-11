#include "Subnetv6.h"

#include "coreUtils.h"
#include <memory>

namespace core {
    Subnetv6::Subnetv6(const cpp_int& hostNumber, const QString& name):
        _SubName{name},
        _HostNumber{hostNumber}
    {
        if(hostNumber < cpp_int{1})
            throw SubnetInvalidExcept{"Can't create subnet with less than one host."};
    }

    QString Subnetv6::SubName() const noexcept
    {
        return _SubName;
    }

    cpp_int Subnetv6::HostNumber() const noexcept
    {
        return _HostNumber;
    }

    const IPaddress& Subnetv6::Ip() const noexcept
    {
        return *_Ip;
    }

    const IPaddress& Subnetv6::Mask() const noexcept
    {
        return *_NetMask;
    }

    const std::vector<std::shared_ptr<Host>>& Subnetv6::HostsList() const noexcept
    {
        return _HostsList;
    }

    void Subnetv6::Ip(std::unique_ptr<IPaddress> ip) noexcept
    {
        _Ip = std::move(ip);
    }

    void Subnetv6::Mask(std::unique_ptr<IPaddress> mask) noexcept
    {
        _NetMask = std::move(mask);
    }

    void Subnetv6::SubName(const QString& newName) noexcept
    {
        _SubName = newName;
    }

    void Subnetv6::addHost(std::unique_ptr<IPaddress> ip, const QString& name) noexcept
    {
        _HostsList.push_back(std::make_shared<Host>(
                                 Host{std::move(ip), name, _HostsList.size()}));
    }

    bool Subnetv6::isHost(const IPaddress& hostIP) const noexcept
    {
        return ( (Ip() & Mask()) == (hostIP & Mask()) ) && (hostIP != Ip());
    }

    cpp_int Subnetv6::hostsCapacity() const
    {
        cpp_int allAddresses = ( cpp_int{1} << (Mask().getAddressLength() - Mask().getPrefix()) );
        auto withNoNetAddr =  --allAddresses; //without network address
        return withNoNetAddr;
    }

    std::unique_ptr<IPaddress> Subnetv6::getMinHost() const
    {
        return std::make_unique<IPv6address>(*_Ip | IPv6address{boost::dynamic_bitset<>(128, 1)});
    }

    std::unique_ptr<IPaddress> Subnetv6::getMaxHost() const
    {
        auto x = boost::dynamic_bitset<>(128);
        x.set(1, 128 - Mask().getPrefix() - 1, true);
        return std::make_unique<IPv6address>(*_Ip | IPv6address{x});
    }

    Subnetv6* Subnetv6::_cloneImpl() const noexcept
    {
        auto ptr = new Subnetv6{this->_HostNumber, this->_SubName};
        ptr->Ip(this->_Ip->clone());
        ptr->Mask(this->_NetMask->clone());
        return ptr;
    }
}

