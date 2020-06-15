#pragma once
#ifndef HOST_H
#define HOST_H

#include <memory>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "IPaddress.h"

namespace core {
    using boost::multiprecision::cpp_int;

    class Host final
    {
    public:
        Host(std::unique_ptr<IPaddress> ip, const QString& name, const cpp_int& id) noexcept;

        const IPaddress& Ip() const noexcept;
        QString Name() const noexcept;
        cpp_int Id() const noexcept;

        void Ip(std::unique_ptr<IPaddress> ip) noexcept;
        void Name(const QString& name) noexcept;
    private:
        std::unique_ptr<IPaddress> _Ip;
        QString _Name;
        cpp_int _Id;
    };
};

#endif // HOST_H
