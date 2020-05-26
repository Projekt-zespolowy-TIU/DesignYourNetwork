#include "IPstructs.h"

namespace core {

bool NetworkBase::isHost(const IPaddressBase &hostIP) const
{
    return ( (*(*Ip & *NetMask) == *(hostIP & *NetMask)) && (hostIP != *Ip) ) ? true : false;
}

unsigned long long NetworkBase::hostsCapacity() const
{
    auto allAddresses = 1ull << (NetMask->getLength() - NetMask->getPrefix());
    return allAddresses - 1; //without network address
}

void NetworkBase::fix()
{
    Ip = *Ip & *NetMask;
}

unsigned long long Networkv4::hostsCapacity() const
{
    return NetworkBase::hostsCapacity() - 1; //without broadcast
}

Networkv4 *Networkv4::_cloneImpl() const
{
    auto ptr = new Networkv4;
    *ptr->Ip = *this->Ip;
    *ptr->NetMask = *this->NetMask;
    return ptr;
}

unsigned long long Subnetv4::hostsCapacity() const
{
    return NetworkBase::hostsCapacity() - 1; //without broadcast
}

std::unique_ptr<IPaddressBase> Subnetv4::getMinHost()
{
    auto x = boost::dynamic_bitset<>(32, 1);
    return std::make_unique<IPv4address>(dynamic_cast<IPv4address&>(*Ip) | IPv4address{x});
}

std::unique_ptr<IPaddressBase> Subnetv4::getMaxHost()
{
    auto x = boost::dynamic_bitset<>(32);
    x.set(1, 32 - NetMask->getPrefix() - 1, true);
    return std::make_unique<IPv4address>(dynamic_cast<IPv4address&>(*Ip) | IPv4address{x});
}

std::unique_ptr<IPaddressBase> Subnetv4::getBroadcast()
{
    auto x = boost::dynamic_bitset<>(32);
    x.set(0, 32 - NetMask->getPrefix(), true);
    return std::make_unique<IPv4address>(dynamic_cast<IPv4address&>(*Ip) | IPv4address{x});
}

Subnetv4 *Subnetv4::_cloneImpl() const
{
    auto ptr = new Subnetv4;
    *ptr->Ip = *this->Ip;
    *ptr->NetMask = *this->NetMask;
    ptr->HostNumber = this->HostNumber;
    ptr->SubName = this->SubName;
    return ptr;
}

}
