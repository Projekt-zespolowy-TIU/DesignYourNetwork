#include "Host.h"

namespace core {
    Host::Host(std::unique_ptr<IPaddress> ip, const QString& name):
            _Ip{std::move(ip)},
            _Name{name}
        {}

    Host::Host(const Host& rhs)
        {
            if(rhs._Ip)
                this->_Ip.reset(rhs._Ip->clone().release());
            else
                this->_Ip.reset();

            this->_Name = rhs._Name;
    }

    const IPaddress& Host::Ip() const
    {
        return *_Ip;
    }

    QString Host::Name() const
    {
        return _Name;
    }

    void Host::Ip(std::unique_ptr<IPaddress> ip)
    {
        _Ip.reset(ip.release());
    }

    void Host::Name(const QString& name)
    {
        _Name = name;
    }

    Host& Host::operator=(const Host& rhs)
        {
            if(rhs._Ip)
                this->_Ip.reset(rhs._Ip->clone().release());
            else
                this->_Ip.reset();

            this->_Name = rhs._Name;
            return *this;
        }
}
