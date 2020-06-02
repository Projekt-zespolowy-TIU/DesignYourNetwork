#include "Networkv4.h"

namespace core {
    Networkv4::Networkv4(const IPv4address& ip, const IPv4mask& mask):
        _Ip{std::make_unique<IPv4address>(ip)},
        _NetMask{std::make_unique<IPv4mask>(mask)}
    {
        _Ip = std::make_unique<IPv4address>(*_Ip & *_NetMask);
    }

    Networkv4::Networkv4(const Networkv4& rhs)
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

    Networkv4& Networkv4::operator=(const Networkv4& rhs)
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

    const IPaddress& Networkv4::Ip() const
    {
        return *_Ip;
    }

    const IPaddress& Networkv4::Mask() const
    {
        return *_NetMask;
    }

    const std::vector<std::shared_ptr<ISubnet>>& Networkv4::Subnets() const
    {
        return _Subnets;
    }

    void Networkv4::Subnets(const std::vector<std::shared_ptr<ISubnet>>& subnets)
    {
        _Subnets = subnets;
    }

    void Networkv4::addSubnet(const cpp_int& hostNumber, const QString& name)
    {
        _Subnets.push_back(std::make_shared<Subnetv4>(hostNumber, name));
    }

    cpp_int Networkv4::hostsCapacity() const
    {
        cpp_int allAddresses = ( cpp_int{1} << (Mask().getAddressLength() - Mask().getPrefix()) );
        auto withNoNetAddr =  --allAddresses; //without network address
        return --withNoNetAddr; //without broadcast
    }

    bool Networkv4::isSubnet(const IPaddress& hostIP) const
    {
        return (*_Ip & *_NetMask) == (hostIP & *_NetMask);
    }
}
