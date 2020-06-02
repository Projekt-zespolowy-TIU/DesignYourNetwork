#include "Host.h"

namespace core {
    Host::Host(std::unique_ptr<IPaddress> ip, const QString& name, const cpp_int& id):
            _Ip{std::move(ip)},
            _Name{name},
            _Id{id}
        {}

    Host::Host(const Host& rhs)
        {
            if(rhs._Ip)
                this->_Ip.reset(rhs._Ip->clone().release());
            else
                this->_Ip.reset();

            this->_Name = rhs._Name;
            this->_Id = rhs._Id;
    }

    Host& Host::operator=(const Host& rhs)
    {
        if(rhs._Ip)
            this->_Ip.reset(rhs._Ip->clone().release());
        else
            this->_Ip.reset();

        this->_Name = rhs._Name;
        this->_Id = rhs._Id;
        return *this;
    }

    const IPaddress& Host::Ip() const
    {
        return *_Ip;
    }

    QString Host::Name() const
    {
        return _Name;
    }

    boost::multiprecision::cpp_int Host::Id() const
    {
        return _Id;
    }

    void Host::Ip(std::unique_ptr<IPaddress> ip)
    {
        _Ip.reset(ip.release());
    }

    void Host::Name(const QString& name)
    {
        _Name = name;
    }
}
