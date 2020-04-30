#pragma once
#ifndef IIPADDRESS_H
#define IIPADDRESS_H

#include <QString>
#include <iostream>

namespace core{
    class IIPaddress
    {
    public:
        virtual QString asStringDec() const = 0;
        virtual QString asStringBin() const = 0;

    protected:
        IIPaddress& operator=(const IIPaddress&) = default;
        virtual ~IIPaddress() = default;
    };
};

#endif // IIPADDRESS_H
