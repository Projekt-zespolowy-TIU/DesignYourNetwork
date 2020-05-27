#pragma once
#ifndef HOST_H
#define HOSTH

#include <memory>
#include <QString>

#include "IPaddress.h"

namespace core {
    class Host final
    {
    public:
        Host(std::unique_ptr<IPaddress> ip, const QString& name);
        Host(const Host& rhs);
        Host& operator=(const Host& rhs);

        const IPaddress& Ip() const;
        QString Name() const;

        void Ip(std::unique_ptr<IPaddress> ip);
        void Name(const QString& name);
    private:
        std::unique_ptr<IPaddress> _Ip;
        QString _Name;
    };
};

#endif // HOST_H
