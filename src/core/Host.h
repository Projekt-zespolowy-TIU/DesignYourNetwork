#pragma once
#ifndef HOST_H
#define HOSTH

#include <memory>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

#include "IPaddress.h"

namespace core {
    using boost::multiprecision::cpp_int;

    class Host final
    {
    public:
        Host(std::unique_ptr<IPaddress> ip, const QString& name, const cpp_int& id);

        const IPaddress& Ip() const;
        QString Name() const;
        cpp_int Id() const;

        void Ip(std::unique_ptr<IPaddress> ip);
        void Name(const QString& name);
    private:
        std::unique_ptr<IPaddress> _Ip;
        QString _Name;
        cpp_int _Id;
    };
};

#endif // HOST_H
