#include "Networkv6.h"

namespace core {
    Networkv6::Networkv6(const IPv6address& ip, const IPv6mask& mask):
        _Ip{std::make_unique<IPv6address>(ip)},
        _NetMask{std::make_unique<IPv6mask>(mask)}
    {
        _Ip = std::make_unique<IPv6address>(*_Ip & *_NetMask);
    }

    Networkv6::Networkv6(const Networkv6& rhs)
    {
        if(rhs._Ip)
            this->_Ip = rhs.Ip().clone();
        else
            this->_Ip.reset();

        if(rhs._NetMask)
            this->_NetMask = rhs.Mask().clone();
        else
            this->_NetMask.reset();

        this->_Subnets = rhs._Subnets;
    }

    Networkv6& Networkv6::operator=(const Networkv6& rhs)
    {
        if(rhs._Ip)
            this->_Ip = rhs.Ip().clone();
        else
            this->_Ip.reset();

        if(rhs._NetMask)
            this->_NetMask = rhs.Mask().clone();
        else
            this->_NetMask.reset();

        this->_Subnets = rhs._Subnets;
        return *this;
    }

    const IPaddress& Networkv6::Ip() const noexcept
    {
        return *_Ip;
    }

    const IPaddress& Networkv6::Mask() const noexcept
    {
        return *_NetMask;
    }

    const std::vector<std::shared_ptr<ISubnet>>& Networkv6::Subnets() const noexcept
    {
        return _Subnets;
    }

    void Networkv6::Subnets(const std::vector<std::shared_ptr<ISubnet>>& subnets) noexcept
    {
        _Subnets = subnets;
    }

    void Networkv6::addSubnet(const cpp_int& hostNumber, const QString& name)
    {
        _Subnets.push_back(std::make_shared<Subnetv6>(hostNumber, name));
    }

    cpp_int Networkv6::hostsCapacity() const
    {
        cpp_int allAddresses = ( cpp_int{1} << (Mask().getAddressLength() - Mask().getPrefix()) );
        auto withNoNetAddr =  --allAddresses; //without network address
        return withNoNetAddr;
    }

    bool Networkv6::isSubnet(const IPaddress& hostIP) const noexcept
    {
        return (*_Ip & *_NetMask) == (hostIP & *_NetMask);
    }
}
