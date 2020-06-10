#include "Host.h"

namespace core {
    Host::Host(std::unique_ptr<IPaddress> ip, const QString& name, const cpp_int& id) noexcept:
            _Ip{std::move(ip)},
            _Name{name},
            _Id{id}
    {}

    const IPaddress& Host::Ip() const noexcept
    {
        return *_Ip;
    }

    QString Host::Name() const noexcept
    {
        return _Name;
    }

    boost::multiprecision::cpp_int Host::Id() const noexcept
    {
        return _Id;
    }

    void Host::Ip(std::unique_ptr<IPaddress> ip) noexcept
    {
        _Ip = std::move(ip);
    }

    void Host::Name(const QString& name) noexcept
    {
        _Name = name;
    }
}
