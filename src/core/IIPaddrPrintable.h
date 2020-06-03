#pragma once
#ifndef IIPADDRPRINTABLE_H
#define IIPADDRPRINTABLE_H

#include <QString>

namespace core{
    class IIPaddrPrintable
    {
    public:
        virtual QString asStringDec() const = 0;
        virtual QString asStringBin() const = 0;

    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    public:
        virtual ~IIPaddrPrintable() = default;
    protected:
        IIPaddrPrintable() = default;
        IIPaddrPrintable(const IIPaddrPrintable&) = default;
        IIPaddrPrintable& operator=(const IIPaddrPrintable&) = default;
        IIPaddrPrintable(IIPaddrPrintable&&) noexcept = default;
        IIPaddrPrintable& operator=(IIPaddrPrintable&&) noexcept = default;
    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    };
};

#endif // IIPADDRPRINTABLE_H
