#include "Networkv4.h"

namespace core {
    Networkv4::Networkv4(const IPv4address& ip, const IPv4mask& mask):
        _Ip{std::make_unique<IPv4address>(ip)},
        _NetMask{std::make_unique<IPv4mask>(mask)}
    {
        _Ip = std::make_unique<IPv4address>(*_Ip & *_NetMask);
    }

    const IPaddress& Networkv4::Ip() const
    {
        return *_Ip;
    }

    const IPaddress& Networkv4::Mask() const
    {
        return *_NetMask;
    }

    const std::vector<Subnetv4>& Networkv4::Subnets() const
    {
        return _Subnets;
    }

    std::vector<Subnetv4>& Networkv4::Subnets()
    {
        return _Subnets;
    }

    void Networkv4::Subnets(std::vector<Subnetv4> subnets)
    {
        _Subnets = subnets;
    }

    void Networkv4::addSubnet(const cpp_int& hostNumber, const QString& name)
    {
        _Subnets.push_back({hostNumber, name});
    }

    bool Networkv4::isSubnet(const IPaddress& hostIP) const
    {
        return ((*_Ip & *_NetMask) == (hostIP & *_NetMask)) ? true : false;
    }
}
