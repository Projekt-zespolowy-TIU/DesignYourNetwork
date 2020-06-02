#include "Host.h"

namespace core {
    Host::Host(std::unique_ptr<IPaddress> ip, const QString& name, const cpp_int& id):
            _Ip{std::move(ip)},
            _Name{name},
            _Id{id}
    {}

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
        _Ip = std::move(ip);
    }

    void Host::Name(const QString& name)
    {
        _Name = name;
    }
}
