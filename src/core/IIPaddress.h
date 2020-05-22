#pragma once
#ifndef IIPADDRESS_H
#define IIPADDRESS_H

#include <QString>

namespace core{
    class IIPaddress
    {
    public:
        virtual QString asStringDec() const = 0;
        virtual QString asStringBin() const = 0;

        virtual ~IIPaddress() = default;
    protected:
        IIPaddress() = default;
        IIPaddress(const IIPaddress&) = default;
        IIPaddress& operator=(const IIPaddress&) = default;
        IIPaddress(IIPaddress&&) noexcept = default;
        IIPaddress& operator=(IIPaddress&&) noexcept = default;
    };
};

#endif // IIPADDRESS_H
