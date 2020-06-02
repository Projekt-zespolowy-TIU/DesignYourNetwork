#include "Subnetv4.h"

#include "coreUtils.h"

namespace core {
    Subnetv4::Subnetv4(const cpp_int& hostNumber, const QString& name):
        _SubName{name},
        _HostNumber{hostNumber}
    {
        if(hostNumber < cpp_int{1})
            throw SubnetInvalidExcept{"Can't create subnet with less than one host."};
    }

    Subnetv4::Subnetv4(const Subnetv4& rhs)
    {
        if(rhs._Ip)
            this->_Ip.reset(rhs.Ip().clone().release());
        else
            this->_Ip.reset();

        if(rhs._NetMask)
            this->_NetMask.reset(rhs.Mask().clone().release());
        else
            this->_NetMask.reset();

        this->_SubName = rhs._SubName;
        this->_HostNumber = rhs._HostNumber;
        this->_HostsList = rhs._HostsList;
    }

    Subnetv4& Subnetv4::operator=(const Subnetv4& rhs)
    {
        if(rhs._Ip)
            this->_Ip.reset(rhs.Ip().clone().release());
        else
            this->_Ip.reset();

        if(rhs._NetMask)
            this->_NetMask.reset(rhs.Mask().clone().release());
        else
            this->_NetMask.reset();

        this->_SubName = rhs._SubName;
        this->_HostNumber = rhs._HostNumber;
        this->_HostsList = rhs._HostsList;
        return *this;
    }

    Subnetv4::Subnetv4(Subnetv4&& rhs) noexcept
    {
        if(rhs._Ip)
            this->_Ip.reset(rhs._Ip.release());
        else
            this->_Ip.reset();

        if(rhs._NetMask)
            this->_NetMask.reset(rhs._NetMask.release());
        else
            this->_NetMask.reset();

        this->_SubName = rhs._SubName;
        this->_HostNumber = rhs._HostNumber;
        this->_HostsList = rhs._HostsList;
    }

    Subnetv4& Subnetv4::operator=(Subnetv4&& rhs) noexcept
    {
        if(rhs._Ip)
            this->_Ip.reset(rhs._Ip.release());
        else
            this->_Ip.reset();

        if(rhs._NetMask)
            this->_NetMask.reset(rhs._NetMask.release());
        else
            this->_NetMask.reset();

        this->_SubName = rhs._SubName;
        this->_HostNumber = rhs._HostNumber;
        this->_HostsList = rhs._HostsList;
        return *this;
    }

//    std::unique_ptr<Subnetv4> Subnetv4::clone() const
//    {
//        return std::unique_ptr<Subnetv4>(_cloneImpl());
//    }

    QString Subnetv4::SubName() const
    {
        return _SubName;
    }

    cpp_int Subnetv4::HostNumber() const
    {
        return _HostNumber;
    }

    const IPaddress& Subnetv4::Ip() const
    {
        return *_Ip;
    }

    const IPaddress& Subnetv4::Mask() const
    {
        return *_NetMask;
    }

    const std::vector<Host>& Subnetv4::HostsList() const
    {
        return _HostsList;
    }

    void Subnetv4::Ip(std::unique_ptr<IPaddress> ip)
    {
        _Ip.reset(ip.release());
    }

    void Subnetv4::Mask(std::unique_ptr<IPaddress> mask)
    {
        _NetMask.reset(mask.release());
    }

    void Subnetv4::addHost(std::unique_ptr<IPaddress> ip, const QString& name)
    {
        _HostsList.push_back({std::move(ip), name, _HostsList.size()});
    }

    bool Subnetv4::isHost(const IPaddress& hostIP) const
    {
        return ( ( (Ip() & Mask()) == (hostIP & Mask()) ) && (hostIP != Ip()) ) ? true : false;
    }

    cpp_int Subnetv4::hostsCapacity() const
    {
        cpp_int allAddresses = ( cpp_int{1} << (Mask().getAddressLength() - Mask().getPrefix()) );
        auto withNoNetAddr =  --allAddresses; //without network address
        return --withNoNetAddr; //without broadcast
    }

    std::unique_ptr<IPaddress> Subnetv4::getMinHost() const
    {
        return std::make_unique<IPv4address>(Ip() | IPv4address{boost::dynamic_bitset<>(32, 1)});
    }

    std::unique_ptr<IPaddress> Subnetv4::getMaxHost() const
    {
        auto x = boost::dynamic_bitset<>(32);
        x.set(1, 32 - Mask().getPrefix() - 1, true);
        return std::make_unique<IPv4address>(Ip() | IPv4address{x});
    }

    std::unique_ptr<IPaddress> Subnetv4::getBroadcast() const
    {
        auto x = boost::dynamic_bitset<>(32);
        x.set(0, 32 - Mask().getPrefix(), true);
        return std::make_unique<IPv4address>(Ip() | IPv4address{x});
    }

//    Subnetv4* Subnetv4::_cloneImpl() const
//    {
//        auto ptr = new Subnetv4{this->_HostNumber, this->_SubName};
//        ptr->Ip(this->_Ip->clone());
//        ptr->Mask(this->_NetMask->clone());
//        return ptr;
//    }
}
